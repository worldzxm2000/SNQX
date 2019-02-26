#include "BXS.h"
#include"string"
#include<qstring.h>
#include"qdatetime.h"
#include"qfile.h"
#include"qtextstream.h"
#include"qjsondocument.h"
#include "qdebug.h"
#include "qcoreapplication.h"
#include"qdir.h"

//获取业务号
int GetServiceTypeID()
{
	return 7;
}

//获取业务名称
QString GetServiceTypeName()
{
	QString name = QString::fromLocal8Bit("室内气象站业务");
	return name;
}

//获取版本号
QString GetVersionNo()
{
	QString Version = QString::fromLocal8Bit("1.0");
	return Version;
}

//命令发送窗口事件响应
void  GetControlWidget(QString StationID, uint Socket, QWidget* parent) //<>
{
	if (isActive)
		return;
	w = new ControlUI(parent);
	w->StationID = StationID;
	isActive = true;
	w->Socket = Socket;
	w->isActive = &isActive;
	w->GetSensorStatus();
	w->show();
}

//获取端口号
int GetPort()
{
	return 8018;
}

//矫正时钟
void SetTime(QString StationID, uint Socket)
{
	QDateTime nowtime = QDateTime::currentDateTime();
	QString datetime = nowtime.toString("yyyy-MM-dd hh:mm:ss");
	QString year, month, day, hour, min, sec;
	year = nowtime.toString("yy");
	month = nowtime.toString("MM");
	day = nowtime.toString("dd");
	hour = nowtime.toString("hh");
	min = nowtime.toString("mm");
	sec = nowtime.toString("ss");

	int chk = 0;
	int SrcAdrr = StationID.toInt();
	BYTE bytes[1024] = { 0 };
	bytes[0] = 0xaa;
	bytes[1] = 0x0d;//帧长度
	bytes[2] = 0x00;//帧长度
	bytes[3] = 0x8F;//帧命令
	chk += bytes[3];
	bytes[4] = 0x01;//帧命令
	chk += bytes[4];
	bytes[5] = SrcAdrr & 0xff;//源地址
	chk += bytes[5];
	bytes[6] = (SrcAdrr >> 8) & 0xff;
	chk += bytes[6];
	bytes[7] = 0;//源地址
	chk += bytes[7];
	bytes[8] = 0;
	chk += bytes[8];
	bytes[9] = 0x14;//20
	chk += bytes[9];
	bytes[10] = year.toInt();
	chk += bytes[10];
	bytes[11] = month.toInt();
	chk += bytes[11];
	bytes[12] = day.toInt();
	chk += bytes[12];
	bytes[13] = hour.toInt();
	chk += bytes[13];
	bytes[14] = min.toInt();
	chk += bytes[14];
	bytes[15] = sec.toInt();
	chk += bytes[15];
	bytes[16] = chk & 0xff;//校验位 低八位
	bytes[17] = (chk >> 8) & 0xff;//高八位
	bytes[18] = 0xdd;
	::send(Socket, (char *)bytes, 19, 0);
}

//返回值反馈
void SetValueToControlWidget(QStringList list)
{
	if (w == nullptr)
		return;
	if (isActive)
		w->setValue(list);
}

//解析数据
LRESULT Char2Json(QString &buff, QJsonObject &json)
{
	int Count = 0;//数据个数
	int Current_P = buff.length();//当前数据指

								  //遍历查找数据
	for (int i = 0; i < buff.length(); i++)
	{
		//帧头  aa
		if (buff[i] == 0xaa)
		{
			Current_P = i;//指针指向帧头
			for (int j = i + 1; j < buff.length(); j++)
			{
				if (buff[j] == 0xdd)
				{
					Current_P = j + 1;//指针移动到帧尾下一个字符

					QString strBuff = buff.mid(i, j - i + 1);
					QJsonObject SubJson;
					SubJson.insert("ServiceTypeID", BXS);
					
					Frame frame = { 0,NULL,NULL };
					//获取帧长度
					frame.len = ((strBuff[1]).unicode() & 0xFF + strBuff[2].unicode() * 256) - 6;
					//判断帧长度 12为数据 0为心跳
					if (strBuff.length() - frame.len != 12 || strBuff.length() - frame.len == 0)
						continue;
					//获取帧命令
					frame.Command = strBuff[3].unicode() + strBuff[4].unicode() * 256;
					//获取源地址
					frame.SrcAddr = strBuff[5].unicode() + strBuff[6].unicode() * 256;
					//获取目的地址
					frame.DesAddr = strBuff[7].unicode() + strBuff[8].unicode() * 256;
					//区站号
					SubJson.insert("StationID", QString::number(frame.SrcAddr));
					//设备号
					SubJson.insert("DeviceID","NULL" );
					//数据类型
					SubJson.insert("DataSourceID",1);
					SubJson.insert("typeid",1);
					frame.data = strBuff.mid(9, frame.len);
					//判断接收命令类型
					switch (frame.Command)
					{
						//读取采集时钟发送命令 0x020f
					case 527:
						Transform2Time(frame.data, SubJson);
						break;
						//读取采集地址命令 0x040F
					case 1039:
						Transform2Addr(frame.data, SubJson);
						break;

						//10分钟上传数据 0x200f、实时数据0x068f和补抄数据 0x250f
					case 8207: case 1551:case 9487:
						Transform2FeatureData(frame.data, SubJson);
						break;
						//IP和端口
					case 3343:
						Transform2IPPort(frame.data, SubJson);
						break;
						//传感器开关
					case 2319:
						Transform2SessiorStatus(frame.data, SubJson);
						break;
						//数据错误
					case 65039:
						Transform2ErrorData(frame.data, SubJson);
						break;
						//通讯结束 Oxff04
					case 65295:
						Transform2CloeseConnection(frame.data, SubJson);
						break;
						//心跳包数据 0x3A0f
					case 14863:
						Transform2Heartbeat(frame.data, SubJson);
						break;
					default:
						SubJson.insert("Command", frame.Command);
						break;
					}
					Count += 1;//数据个数
					//数据备份
					QDateTime current_date_time = QDateTime::currentDateTime();
					QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
					QString current_day = current_date_time.toString("yyyy-MM-dd");
					QString fileName = QCoreApplication::applicationDirPath() + "\\SNQX\\" + QString::number(frame.SrcAddr) + "\\" + current_day;
					QDir dir(fileName);
					if (!dir.exists())
						dir.mkpath(fileName);//创建多级目录
					fileName += "\\data.txt";
					QFile file(fileName);

					if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
					{
					}
					QTextStream in(&file);

					QString ConvStr;
					for (int i = 0; i < strBuff.length(); i++)
					{
						ConvStr += (QString::number(strBuff[i].unicode(), 16)) + " ";
					}
					in << current_date << "\r\n" << ConvStr << "\r\n";
					file.close();
					json.insert(QString::number(Count), SubJson);
					i = j;//当前循环
					break;
				}
			}
		}
	}
	json.insert("DataLength", Count);//JSON数据个数
	if (Current_P >= buff.length())//判断当前指针位置
	{
		buff.clear();
	}//清除内存
	else
	{
		buff.remove(0, Current_P);
	}//将剩余字节存入缓存
	return 1;
}

QString Convert2Time(QString strTime)
{
	QString tmp;
	tmp = strTime.mid(0, 4) + "-" + strTime.mid(4, 2) + "-" + strTime.mid(6, 2) + " " + strTime.mid(8, 2) + ":" + strTime.mid(10, 2) + ":" + strTime.mid(12, 2);
	return tmp;
}

//采集时钟发送命令
void Transform2Time(QString data, QJsonObject &json)
{
	json.insert("DataType", 2);//数据类型 观测数据
	json.insert("ValueCount", 8);//返回值个数
	json.insert("Command",2205);
    //时间
	QString century = QString("%1").arg((int)data[0].unicode(), 2, 10, QChar('0'));
	QString year = QString("%1").arg((int)data[1].unicode(), 2, 10, QChar('0'));
	QString month = QString("%1").arg((int)data[2].unicode(), 2, 10, QChar('0'));
	QString day = QString("%1").arg((int)data[3].unicode(), 2, 10, QChar('0'));
	QString hour = QString("%1").arg((int)data[4].unicode(), 2, 10, QChar('0'));
	QString min = QString("%1").arg((int)data[5].unicode(), 2, 10, QChar('0'));
	QString sec = QString("%1").arg((int)data[6].unicode(), 2, 10, QChar('0'));
	QString time = Convert2Time(century + year + month + day + hour + min + sec);
	QJsonObject subJson;
	subJson.insert("Count", 1);
	subJson.insert("Params1", time);
	json.insert("Parameter", subJson);
}

//采集器地址
void Transform2Addr(QString data, QJsonObject &json)
{
	json.insert("DataType", 2);//数据类型 观测数据
	json.insert("ValueCount", 8);//返回值个数
	json.insert("Command", 2207);
    //地址
	int addr = data[1].unicode() + data[0].unicode() * 256;
	QJsonObject subJson;
	subJson.insert("Count", 1);
	subJson.insert("Params1", QString::number(addr));
	json.insert("Parameter", subJson);
}
//IP地址和端口号
void Transform2IPPort(QString data, QJsonObject &json)
{
	json.insert("DataType", 2);//数据类型 观测数据
	json.insert("ValueCount", 8);//返回值个数
	json.insert("Command", 2202);
	//获取IP
	QString IP;
	IP.sprintf("%d.%d.%d.%d", (int)data[0].unicode(), (int)data[1].unicode(), (int)data[2].unicode(), (int)data[3].unicode());

	//获取端口
	int Port = data[5].unicode();
	Port |= (data[4].unicode() << 8);
	
	QJsonObject subJson;
	subJson.insert("Count", 2);
	subJson.insert("Params1",IP);
	subJson.insert("Params2",Port);
	json.insert("Parameter", subJson);
}

//10分钟数据
void Transform2FeatureData(QString data, QJsonObject &json)
{
	json.insert("DataType", 1);//数据类型 观测数据
	//时间
	QString century = QString("%1").arg((int)data[0].unicode(), 2, 10, QChar('0'));
	QString year = QString("%1").arg((int)data[1].unicode(), 2, 10, QChar('0'));
	QString month = QString("%1").arg((int)data[2].unicode(), 2, 10, QChar('0'));
	QString day = QString("%1").arg((int)data[3].unicode(), 2, 10, QChar('0'));
	QString hour = QString("%1").arg((int)data[4].unicode(), 2, 10, QChar('0'));
	QString min = QString("%1").arg((int)data[5].unicode(), 2, 10, QChar('0'));
	QString sec = QString("%1").arg((int)data[6].unicode(), 2, 10, QChar('0'));
	QString time = Convert2Time(century + year + month + day + hour + min + sec);
	json.insert("ObserveTime", time);

	//7，8为源采集地址

	//获取采集板电压
	int v = data[9].unicode() * 256 + data[10].unicode();
	float v_f = (float)v / 100.00;
	json.insert("MainClctrVltgVal", v_f);

	//获取采集板温度
	 v = data[11].unicode() * 256 + data[12].unicode();
	 v_f = (float)v / 100.00;
	 json.insert("MainClctrTmprtVal", v_f);

	 //第一层土壤水分含水量
	  v = data[13].unicode() * 256 + data[14].unicode();
	  v_f = (float)v / 100.00;
	  if (v!= 65535)
		  json.insert("SOILVOLUME10", v_f);

	  //第二层土壤水分含水量
	  v = data[15].unicode() * 256 + data[16].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
		  json.insert("SOILVOLUME20", v_f);

	  //第三层土壤水分含水量
	  v = data[17].unicode() * 256 + data[18].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("SOILVOLUME30", v_f);

	  //第四层土壤水分含水量
	  v = data[19].unicode() * 256 + data[20].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("SOILVOLUME40", v_f);

	  //第一层土壤水分频率
	  v = data[21].unicode() * 256 + data[22].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("SOILFREQUENCY10", v_f);

	  //第二层土壤水分频率
	  v = data[23].unicode() * 256 + data[24].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("SOILFREQUENCY20", v_f);

	  //第三层土壤水分频率
	  v = data[25].unicode() * 256 + data[26].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("SOILFREQUENCY30", v_f);

	  //第四层土壤水分频率
	  v = data[27].unicode() * 256 + data[28].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("SOILFREQUENCY40", v_f);

	  //第一层土壤温度
	  v = data[29].unicode() * 256 + data[30].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("ST_ST1", v_f);

	  //第二层土壤温度
	  v = data[31].unicode() * 256 + data[32].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("ST_ST2", v_f);

	  //第三层土壤温度
	  v = data[33].unicode() * 256 + data[34].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("ST_ST3", v_f);

	  //第四层土壤温度
	  v = data[35].unicode() * 256 + data[36].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("ST_ST4", v_f);

	  //大气温度
	  short tmp= (short)(data[38].unicode()| data[37].unicode()<< 8);
	  //v = data[37].unicode() * 256 + data[38].unicode();
	  v_f = (float)tmp / 100.00;
	  if (tmp != 32767)
	  json.insert("AT_AT1", v_f);

	  //大气湿度
	  v = data[39].unicode() * 256 + data[40].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("AH_RH1", v_f);

	  //大气压
	  v = data[41].unicode() * 256 + data[42].unicode();
	  if (v != 65535)
	  json.insert("STATIONPRESSURE", v);

	  //风向
	  v = data[43].unicode() * 256 + data[44].unicode();
	  if (v != 65535)
	  json.insert("WD_IWD", v);

	  //风速
	  v = data[45].unicode() * 256 + data[46].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("WS_IWS1", v_f);

	  //47 48太阳辐射 49 50光和有效 51 52紫外线强度 
	  //光照
	  v = data[53].unicode() * 65536 + data[54].unicode()*256 +data[55].unicode();
	  if (v != 65535*256)
	  json.insert("BeamStrength", v);

	  //56 57二氧化碳
	  v = data[56].unicode() * 256 + data[57].unicode();
	  if (v != 65535)
	  json.insert("CO2IC",v);
	  //雨量
	  v = data[58].unicode() * 256 + data[59].unicode();
	  v_f = (float)v / 10.00;
	  if (v != 65535)
	  json.insert("MNTRNFL", v_f);

	  //插针式土壤水分
	  v = data[60].unicode() * 256 + data[61].unicode();
	  v_f = (float)v / 100.00;
	  if (v != 65535)
	  json.insert("SOILVOLUME50", v_f);

	  //插针式土壤EC
	  v = data[62].unicode() * 256 + data[63].unicode();
	  if (v != 65535)
	  json.insert("EC", v);
}

//数据错误指令
void Transform2ErrorData(QString data, QJsonObject &json)
{

}

//接收到心跳包
void Transform2Heartbeat(QString data, QJsonObject &json)
{
	json.insert("DataType", 3);//数据类型 3心跳数据

}

//通信结束
void Transform2CloeseConnection(QString data, QJsonObject &json)
{
	json.insert("DataType", 2);//数据类型 观测数据
	json.insert("ValueCount", 8);
	json.insert("Command", 2219);
	QJsonObject subJson;
	subJson.insert("Count", 1);
	subJson.insert("Params1", "T");
	json.insert("Parameter", subJson);
}

//传感器开关状态
void Transform2SessiorStatus(QString data, QJsonObject &json)
{
	json.insert("DataType", 2);//数据类型 观测数据
	json.insert("ValueCount", 8);
	json.insert("Command", 2200);
	QJsonObject subJson;
	subJson.insert("Count", 1);
	QString value;
	/*value.sprintf("%d%d%d%d%d%d%d%d%d%d%d",
		  data.at(0).toLatin1() - '0', data.at(1).toLatin1() - '0', data.at(2).toLatin1() - '0',
		  data.at(3).toLatin1() - '0', data.at(4).toLatin1() - '0', data.at(5).toLatin1() - '0',
		 data.at(6).toLatin1() - '0', data.at(7).toLatin1() - '0', data.at(8).toLatin1() - '0',
		 data.at(9).toLatin1() - '0', data.at(10).toLatin1() - '0');*/
	value.sprintf("%d%d%d%d%d%d%d%d%d%d%d%d",
		(int)(data.at(0).toLatin1()), (int)(data.at(1).toLatin1()), (int)(data.at(2).toLatin1()),
		(int)(data.at(3).toLatin1()), (int)(data.at(4).toLatin1()), (int)(data.at(5).toLatin1()),
		(int)(data.at(6).toLatin1()), (int)(data.at(7).toLatin1()), (int)(data.at(8).toLatin1()),
		(int)(data.at(9).toLatin1()), (int)(data.at(10).toLatin1()),(int)(data.at(11).toLatin1()));
	subJson.insert("Params1", value);
	json.insert("Parameter", subJson);
}
//终端命令
void SetCommand(uint Socket, int CommandType, QString Params1, QString Params2, QString StationID)
{
	switch (CommandType)
	{
	case 2204:
		//设置时钟
	{
		//获取当前时钟
		QDateTime nowtime = QDateTime::currentDateTime();
		QString datetime = nowtime.toString("yyyy.MM.dd hh:mm:ss");
		QString year, month, day, hour, min, sec;
		year = nowtime.toString("yy");
		month = nowtime.toString("MM");
		day = nowtime.toString("dd");
		hour = nowtime.toString("hh");
		min = nowtime.toString("mm");
		sec = nowtime.toString("ss");
		//设置时钟
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x0d;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x01;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//目的地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = 0x14;//20
		chk += bytes[9];
		bytes[10] = year.toInt();
		chk += bytes[10];
		bytes[11] = month.toInt();
		chk += bytes[11];
		bytes[12] = day.toInt();
		chk += bytes[12];
		bytes[13] = hour.toInt();
		chk += bytes[13];
		bytes[14] = min.toInt();
		chk += bytes[14];
		bytes[15] = sec.toInt();
		chk += bytes[15];
		bytes[16] = chk & 0xff;//校验位 低八位
		bytes[17] = (chk >> 8) & 0xff;//高八位
		bytes[18] = 0xdd;
		bytes[20] = 0xff;
		bytes[21] = 0xff;
		::send(Socket, (char *)bytes, 22, 0);
	}
	break;
	case 2205:
		//读时钟
	{
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x06;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x02;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = chk & 0xff;//校验位 低八位
		bytes[10] = (chk >> 8) & 0xff;//高八位
		bytes[11] = 0xdd;
		bytes[12] = 0xff;
		bytes[13] = 0xff;
		::send(Socket, (char *)bytes, 14, 0);
		break;
	}
	case 2203:
		//补抄数据
	{
		QDateTime Time_B, Time_E;
		Time_B = QDateTime::fromString(Params1, "yyyy-MM-dd hh:mm:ss");
		Time_E = QDateTime::fromString(Params2, "yyyy-MM-dd hh:mm:ss");

		QString yearB, monthB, dayB, hourB, minB, yearE, monthE, dayE, hourE, minE;
		yearB = Time_B.toString("yy");;
		monthB = Time_B.toString("MM");
		dayB = Time_B.toString("dd");
		hourB = Time_B.toString("hh");
		minB = Time_B.toString("mm");

		yearE = Time_E.toString("yy");//结束时间
		monthE = Time_E.toString("MM");
		dayE = Time_E.toString("dd");
		hourE = Time_E.toString("hh");
		minE = Time_E.toString("mm");
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x10;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x19;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = yearB.toInt() - 2000;
		chk += bytes[9];
		bytes[10] = monthB.toInt();
		chk += bytes[10];
		bytes[11] = dayB.toInt();
		chk += bytes[11];
		bytes[12] = hourB.toInt();
		chk += bytes[12];
		bytes[13] = minB.toInt();
		chk += bytes[13];
		bytes[14] = yearE.toInt() - 2000;
		chk += bytes[14];
		bytes[15] = monthE.toInt();
		chk += bytes[15];
		bytes[16] = dayE.toInt();
		chk += bytes[16];
		bytes[17] = hourE.toInt();
		chk += bytes[17];
		bytes[18] = minE.toInt();
		chk += bytes[18];
		bytes[19] = chk & 0xff;//校验位 低八位
		bytes[20] = (chk >> 8) & 0xff;//高八位
		bytes[21] = 0xdd;
		bytes[22] = 0xff;
		bytes[23] = 0xff;
		::send(Socket, (char *)bytes, 24, 0);
		break;
	}
	case 2201:
		//设置IP
	{
		int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0, port = 0;
		QList<QString> iplist = Params1.split('.');
		ip1 = iplist[0].toInt();
		ip2 = iplist[1].toInt();
		ip3 = iplist[2].toInt();
		ip4 = iplist[3].toInt();
		port = Params2.toInt();
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x0c;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x0c;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = ip1;//ip
		chk += bytes[9];
		bytes[10] = ip2;
		chk += bytes[10];
		bytes[11] = ip3;
		chk += bytes[11];
		bytes[12] = ip4;
		chk += bytes[12];
		bytes[13] = (port >> 8) & 0xff;//port
		chk += bytes[13];
		bytes[14] = port & 0xff;
		chk += bytes[14];
		bytes[15] = chk & 0xff;//校验位 低八位
		bytes[16] = (chk >> 8) & 0xff;//高八位
		bytes[17] = 0xdd;
		bytes[18] = 0xff;
		bytes[19] = 0xff;
		::send(Socket, (char *)bytes, 20, 0);
		break;
	}
	case 2202:
		//读取IP
	{
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x06;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x0d;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = chk & 0xff;//校验位 低八位
		bytes[10] = (chk >> 8) & 0xff;//高八位
		bytes[11] = 0xdd;
		bytes[12] = 0xff;
		bytes[13] = 0xff;
		::send(Socket, (char *)bytes, 14, 0);
		break;
	}
	case 2200:
		//读取传感器状态
	{
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x06;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x09;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = chk & 0xff;//校验位 低八位
		bytes[10] = (chk >> 8) & 0xff;//高八位
		bytes[11] = 0xdd;
		bytes[12] = 0xff;
		bytes[13] = 0xff;
		::send(Socket, (char *)bytes, 14, 0);
		break;
	}
	case 2218:
		//设置传感器开关
	{
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		if (Params1.count() != 11)
			break;
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x11;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x08;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		//bytes[9] = (int)(Params1.at(0).toLatin1());//土壤水分
		//chk += bytes[9];
		//bytes[10] = (int)(Params1.at(1).toLatin1());//空气温度
		//chk += bytes[10];
		//bytes[11] = (int)(Params1.at(2).toLatin1());//气压
		//chk += bytes[11];
		//bytes[12] = (int)(Params1.at(3).toLatin1());//风向风速
		//chk += bytes[12];
		//bytes[13] = (int)(Params1.at(4).toLatin1());//辐射
		//chk += bytes[13];
		//bytes[14] = (int)(Params1.at(5).toLatin1());//光和有效
		//chk += bytes[14];
		//bytes[15] = (int)(Params1.at(6).toLatin1());//紫外线
		//chk += bytes[15];
		//bytes[16] = (int)(Params1.at(7).toLatin1());//光照度
		//chk += bytes[16];
		//bytes[17] = (int)(Params1.at(8).toLatin1());//二氧化碳
		//chk += bytes[17];
		//bytes[18] = (int)(Params1.at(9).toLatin1());//插针式土壤
		//chk += bytes[18];
		//bytes[19] = (int)(Params1.at(10).toLatin1());//雨量
		//chk += bytes[19];
		bytes[9] = Params1.at(0).toLatin1() - '0';//土壤水分
		chk += bytes[9];
		bytes[10] = Params1.at(1).toLatin1() - '0';//空气温度
		chk += bytes[10];
		bytes[11] = Params1.at(2).toLatin1() - '0';//气压
		chk += bytes[11];
		bytes[12] = Params1.at(3).toLatin1() - '0';//风向风速
		chk += bytes[12];
		bytes[13] = Params1.at(4).toLatin1() - '0';//辐射
		chk += bytes[13];
		bytes[14] = Params1.at(5).toLatin1() - '0';//光和有效
		chk += bytes[14];
		bytes[15] = Params1.at(6).toLatin1() - '0';//紫外线
		chk += bytes[15];
		bytes[16] = Params1.at(7).toLatin1() - '0';//光照度
		chk += bytes[16];
		bytes[17] = Params1.at(8).toLatin1() - '0';//二氧化碳
		chk += bytes[17];
		bytes[18] = Params1.at(9).toLatin1() - '0';//插针式土壤
		chk += bytes[18];
		bytes[19] = Params1.at(10).toLatin1() - '0';//雨量
		chk += bytes[19];
		bytes[20] = Params1.at(11).toLatin1() - '0';
		chk += bytes[20];
		bytes[21] = chk & 0xff;//校验位 低八位
		bytes[22] = (chk >> 8) & 0xff;//高八位
		bytes[23] = 0xdd;
		bytes[24] = 0xff;
		bytes[25] = 0xff;
		::send(Socket, (char *)bytes, 26, 0);
	}
	break;
	case 2206:
		//设置采集器地址
	{
		int addr = 0;
		addr =Params1.toInt();
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x08;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x03;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = (addr >> 8) & 0xff;//地址高八位
		chk += bytes[9];
		bytes[10] = addr;
		chk += bytes[10];
		bytes[11] = chk & 0xff;//校验位 低八位
		bytes[12] = (chk >> 8) & 0xff;//高八位
		bytes[13] = 0xdd;
		bytes[14] = 0xff;
		bytes[15] = 0xff;
		::send(Socket, (char *)bytes, 16, 0);
	}
	break;
	case 2207:
		//读取采集器地址
	{
		int chk = 0;
		int SrcAdrr = StationID.toInt();
		BYTE bytes[1024] = { 0 };
		bytes[0] = 0xaa;
		bytes[1] = 0x06;//帧长度
		bytes[2] = 0x00;//帧长度
		bytes[3] = 0x8f;//帧命令
		chk += bytes[3];
		bytes[4] = 0x04;//帧命令
		chk += bytes[4];
		bytes[5] = SrcAdrr & 0xff;//源地址
		chk += bytes[5];
		bytes[6] = (SrcAdrr >> 8) & 0xff;
		chk += bytes[6];
		bytes[7] = 0;//源地址
		chk += bytes[7];
		bytes[8] = 0;
		chk += bytes[8];
		bytes[9] = chk & 0xff;//校验位 低八位
		bytes[10] = (chk >> 8) & 0xff;//高八位
		bytes[11] = 0xdd;
		bytes[12] = 0xff;
		bytes[13] = 0xff;
		::send(Socket, (char *)bytes, 14, 0);
	}
	break;
	default:
		break;
	}
}
