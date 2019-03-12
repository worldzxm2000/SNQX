#include "ControlUI.h"

ControlUI::ControlUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint);
	ui.CloseBtn->setToolTipName(QString::fromLocal8Bit("关闭"));
	ui.MinBtn->setToolTipName(QString::fromLocal8Bit("最小化"));
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));//最小化按钮
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));//关闭按钮
	cmmIndex = 0;
	m_pLoadingLabel = new QLabel(this);
	m_pLoadingLabel->setGeometry(this->width() / 2 - 80, this->height() / 2 - 150, 150, 150);
	m_pLoadingLabel->setStyleSheet("QLabel {background-color: transparent;}");
	m_pTimer = new QTimer(this);
    // 设定超时时间100毫秒100
	m_pTimer->setInterval(125);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
	StartAnimation();

	/*connect(ui.TRBtn, SIGNAL(checkedChanged(bool)), this, SLOT(on_TRBtn_clicked(bool)));
	connect(ui.WDBtn, SIGNAL(checkedChanged(bool)), this, SLOT(on_WDBtn_clicked(bool )));
	connect(ui.FXBtn, SIGNAL(checkedChanged(bool)), this, SLOT(on_FXBtn_clicked(bool )));*/
	/*connect(ui.ZWXBtn, SIGNAL(checkedChanged(bool)), this, SLOT(on_ZWXBtn_clicked(bool )));
	connect(ui.FSBtn, SIGNAL(checkedChanged(bool )), this, SLOT(on_FSBtn_clicked(bool )));
	connect(ui.GZDBtn, SIGNAL(checkedChanged(bool )), this, SLOT(on_GZDBtn_clicked(bool )));
	connect(ui.QYBtn, SIGNAL(checkedChanged(bool )), this, SLOT(on_QYBtn_clicked(bool )));
	connect(ui.GHYXBtn, SIGNAL(checkedChanged(bool )), this, SLOT(on_GHYXBtn_clicked(bool )));
	connect(ui.EYHTBtn, SIGNAL(checkedChanged(bool )), this, SLOT(on_EYHTBtn_clicked(bool )));
	connect(ui.CZSBtn, SIGNAL(checkedChanged(bool )), this, SLOT(on_CZSBtn_clicked(bool )));
	connect(ui.YLBtn, SIGNAL(checkedChanged(bool )), this, SLOT(on_YLBtn_clicked(bool )));*/
}

ControlUI::~ControlUI()
{

}

void ControlUI::closeEvent(QCloseEvent *event)
{
	if (event==NULL)
	{
		return;
	}
	QWidget::close();
	*isActive = false;
	delete this;
}

void ControlUI::slot_minWindow()
{
	this->showMinimized();
}

void ControlUI::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void ControlUI::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void ControlUI::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}

//读取传感器状态
void ControlUI::GetSensorStatus()
{
	cmmIndex = 2200;
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
	StartAnimation();
}

//设置IP
void ControlUI::on_WIPBtn_clicked()
 {
	 cmmIndex = 2201;
	 int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0, port = 0;
	 ip1 = ui.DevicelineEdit_IP1->text().toInt();
	 ip2 = ui.DevicelineEdit_IP2->text().toInt();
	 ip3 = ui.DevicelineEdit_IP3->text().toInt();
	 ip4 = ui.DevicelineEdit_IP4->text().toInt();
	 port = ui.DevicelineEdit_Port->text().toInt();
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
	 bytes[9] =ip1;//ip
	 chk += bytes[9];
	 bytes[10] = ip2;
	 chk += bytes[10];
	 bytes[11] = ip3;
	 chk += bytes[11];
	 bytes[12] = ip4;
	 chk += bytes[12];
	 bytes[13] = port & 0xff;
	 chk += bytes[13];
	 bytes[14] = (port >> 8) & 0xff;//port 
	 chk += bytes[14];
	 bytes[15] = chk & 0xff;//校验位 低八位
	 bytes[16] = (chk >> 8) & 0xff;//高八位
	 bytes[17] = 0xdd;
	 bytes[18] = 0xff;
	 bytes[19] = 0xff;
	 ::send(Socket, (char *)bytes, 20, 0);
	 StartAnimation();
 }

//读取IP
 void ControlUI::on_RIPBtn_clicked()
 {
	 cmmIndex = 2202;
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
	 StartAnimation();
 }

//补抄
 void ControlUI::on_DownBtn_clicked()
 {
	 cmmIndex = 2203;
	 QString yearB, monthB, dayB, hourB, minB, yearE, monthE, dayE, hourE, minE;
	 yearB = ui.BdateTimeEdit->sectionText(QDateTimeEdit::YearSection);
	 monthB = ui.BdateTimeEdit->sectionText(QDateTimeEdit::MonthSection);
	 dayB = ui.BdateTimeEdit->sectionText(QDateTimeEdit::DaySection);
	 hourB = ui.BdateTimeEdit->sectionText(QDateTimeEdit::HourSection);
	 minB = ui.BdateTimeEdit->sectionText(QDateTimeEdit::MinuteSection);

	 yearE = ui.EdateTimeEdit->sectionText(QDateTimeEdit::YearSection);
	 monthE = ui.EdateTimeEdit->sectionText(QDateTimeEdit::MonthSection);
	 dayE = ui.EdateTimeEdit->sectionText(QDateTimeEdit::DaySection);
	 hourE = ui.EdateTimeEdit->sectionText(QDateTimeEdit::HourSection);
	 minE = ui.EdateTimeEdit->sectionText(QDateTimeEdit::MinuteSection);
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
 }

//设置时间
 void ControlUI::on_WTimeBtn_clicked()
 {
	 cmmIndex = 2204;
	 QDateTime nowtime = QDateTime::currentDateTime();
	 QString datetime = nowtime.toString("yyyy.MM.dd hh:mm:ss");
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
	 StartAnimation();
 }

//读取时间
 void ControlUI::on_RTimeBtn_clicked()
 {
	 cmmIndex = 2205;
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
	 StartAnimation();
 }

 //设置地址
 void ControlUI::on_WAddrBtn_clicked()
 {
	 cmmIndex = 2206;
	 int addr = 0;
	 addr = ui.lineEdit_Addr->text().toInt();
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
	 bytes[9] = addr & 0xff;
	 chk += bytes[9];
	 bytes[10] = (addr >> 8) & 0xff;//地址高八位
	 chk += bytes[10];
	 bytes[11] = chk & 0xff;//校验位 低八位
	 bytes[12] = (chk >> 8) & 0xff;//高八位
	 bytes[13] = 0xdd;
	 bytes[14] = 0xff;
	 bytes[15] = 0xff;
	 ::send(Socket, (char *)bytes, 16, 0);
	 StartAnimation();
 }

 //读取地址
 void ControlUI::on_RAddrBtn_clicked()
 {
	 cmmIndex = 2207;
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
	 StartAnimation();
 }

// //土壤水分传感器开关
//void ControlUI::on_TRBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2208;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = check;//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////温度传感器开关
//void ControlUI::on_WDBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2209;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] =check;//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////风向传感器开关
//void ControlUI::on_FXBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2210;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = check;//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////紫外线传感器开关
//void ControlUI::on_ZWXBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2211;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] =check;//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////总辐射传感器开关
//void ControlUI::on_FSBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2212;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = check;//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////光照度传感器开关
//void ControlUI::on_GZDBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2213;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = check;//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////气压传感器开关
//void ControlUI::on_QYBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2214;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = check;//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////光和有效传感器开关
//void ControlUI::on_GHYXBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2215;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = check;//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = check;//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////二氧化碳传感器开关
//void ControlUI::on_EYHTBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2216;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = check;//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////插针式土壤水分传感器开关
//void ControlUI::on_CZSBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2217;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] =check;//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = ui.YLBtn->getChecked();//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}
//
////雨量传感器开关
//void ControlUI::on_YLBtn_clicked(bool check)
//{
//	////状态改变
//	//cmmIndex = 2218;
//	//int chk = 0;
//	//int SrcAdrr = StationID.toInt();
//	//BYTE bytes[1024] = { 0 };
//	//bytes[0] = 0xaa;
//	//bytes[1] = 0x11;//帧长度
//	//bytes[2] = 0x00;//帧长度
//	//bytes[3] = 0x8f;//帧命令
//	//chk += bytes[3];
//	//bytes[4] = 0x08;//帧命令
//	//chk += bytes[4];
//	//bytes[5] = SrcAdrr & 0xff;//源地址
//	//chk += bytes[5];
//	//bytes[6] = (SrcAdrr >> 8) & 0xff;
//	//chk += bytes[6];
//	//bytes[7] = 0;//源地址
//	//chk += bytes[7];
//	//bytes[8] = 0;
//	//chk += bytes[8];
//	//bytes[9] = ui.TRBtn->getChecked();//土壤水分
//	//chk += bytes[9];
//	//bytes[10] = ui.WDBtn->getChecked();//空气温度
//	//chk += bytes[10];
//	//bytes[11] = ui.QYBtn->getChecked();//气压
//	//chk += bytes[11];
//	//bytes[12] = ui.FXBtn->getChecked();//风向风速
//	//chk += bytes[12];
//	//bytes[13] = ui.FSBtn->getChecked();//辐射
//	//chk += bytes[13];
//	//bytes[14] = ui.GHYXBtn->getChecked();//光和有效
//	//chk += bytes[14];
//	//bytes[15] = ui.ZWXBtn->getChecked();//紫外线
//	//chk += bytes[15];
//	//bytes[16] = ui.GZDBtn->getChecked();//光照度
//	//chk += bytes[16];
//	//bytes[17] = ui.EYHTBtn->getChecked();//二氧化碳
//	//chk += bytes[17];
//	//bytes[18] = ui.CZSBtn->getChecked();//插针式土壤
//	//chk += bytes[18];
//	//bytes[19] = check;//雨量
//	//chk += bytes[19];
//	//bytes[20] = chk & 0xff;//校验位 低八位
//	//bytes[21] = (chk >> 8) & 0xff;//高八位
//	//bytes[22] = 0xdd;
//	//bytes[23] = 0xff;
//	//bytes[24] = 0xff;
//	//::send(Socket, (char *)bytes, 25, 0);
//	//StartAnimation();
//}

//设置开关
void ControlUI::on_WSetBtn_clicked()
{
	//状态改变
	cmmIndex = 2218;
	int chk = 0;
	int SrcAdrr = StationID.toInt();
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
	bytes[9] = ui.TRBtn->getChecked()==true?1:0;//土壤水分
	chk += bytes[9];
	bytes[10] = ui.WDBtn->getChecked() == true ? 1 : 0;//空气温度
	chk += bytes[10];
	bytes[11] = ui.QYBtn->getChecked() == true ? 1 : 0;//气压
	chk += bytes[11];
	bytes[12] = ui.FXBtn->getChecked() == true ? 1 : 0;//风向风速
	chk += bytes[12];
	bytes[13] = ui.FSBtn->getChecked() == true ? 1 : 0;//辐射
	chk += bytes[13];
	bytes[14] = ui.GHYXBtn->getChecked() == true ? 1 : 0;//光和有效
	chk += bytes[14];
	bytes[15] = ui.ZWXBtn->getChecked() == true ? 1 : 0;//紫外线
	chk += bytes[15];
	bytes[16] = ui.GZDBtn->getChecked() == true ? 1 : 0;//光照度
	chk += bytes[16];
	bytes[17] = ui.EYHTBtn->getChecked() == true ? 1 : 0;//二氧化碳
	chk += bytes[17];
	bytes[18] = ui.CZSBtn->getChecked() == true ? 1 : 0;//插针式土壤
	chk += bytes[18];
	bytes[19] = ui.YLBtn->getChecked() == true ? 1 : 0;//雨量
	chk += bytes[19];
	bytes[20] = ui.CZSECBtn->getChecked() == true ? 1 : 0;//土壤EC
	chk += bytes[20];
	bytes[21] = chk & 0xff;//校验位 低八位
	bytes[22] = (chk >> 8) & 0xff;//高八位
	bytes[23] = 0xdd;
	bytes[24] = 0xff;
	bytes[25] = 0xff;
	::send(Socket, (char *)bytes, 26, 0);
	StartAnimation();
}

//等待设备反馈界面
void ControlUI::updatePixmap()
{
	// 若当前图标下标超过8表示到达末尾，重新计数。
	m_nIndex++;
	m_TimeOut++;
	if (m_TimeOut > 64)
	{
		m_TimeOut = 0;
		StopAnimation();
		QMessageBox::warning(this, QString::fromLocal8Bit("操作状态"), QString::fromLocal8Bit("读取设备信息已超时！"));
		//switch (cmmIndex)
		//{	
		//case 2208://土壤水分开关
		//	ui.TRBtn->setChecked(!ui.TRBtn->getChecked());
		//	break;
		//case 2209://空气温度
		//	ui.WDBtn->setChecked(!ui.WDBtn->getChecked());
		//	break;
		//case 2210://风向
		//	ui.FXBtn->setChecked(!ui.FXBtn->getChecked());
		//	break;
		//case 2211://紫外线
		//	ui.ZWXBtn->setChecked(!ui.ZWXBtn->getChecked());
		//	break;
		//case 2212://辐射
		//	ui.FSBtn->setChecked(!ui.FSBtn->getChecked());
		//	break;
		//case 2213://光照度
		//	ui.GZDBtn->setChecked(!ui.GZDBtn->getChecked());
		//	break;
		//case 2214://气压
		//	ui.QYBtn->setChecked(!ui.QYBtn->getChecked());
		//	break;
		//case 2215://光和有效
		//	ui.GHYXBtn->setChecked(!ui.GHYXBtn->getChecked());
		//	break;
		//case 2216://二氧化碳
		//	ui.EYHTBtn->setChecked(!ui.EYHTBtn->getChecked());
		//	break;
		//case 2217://插针式
		//	ui.CZSBtn->setChecked(!ui.CZSBtn->getChecked());
		//	break;
		//case 2218://雨量
		//	ui.YLBtn->setChecked(!ui.YLBtn->getChecked());
		//	break;
		//default:
		//	break;
		//}
	}
	if (m_nIndex > 8)
		m_nIndex = 1;

	QPixmap pixmap(QString("../Image/png/Loading%1.png").arg(m_nIndex));
	m_pLoadingLabel->setPixmap(pixmap);
}
// 启动定时器
void ControlUI::StartAnimation()
{
	m_pLoadingLabel->show();
	m_pTimer->start();
	m_TimeOut = 0;
}

// 停止定时器
void ControlUI::StopAnimation()
{
	m_pLoadingLabel->hide();
	m_pTimer->stop();
	m_TimeOut = 0;
}

void ControlUI::setValue(QStringList list)
{
	switch (cmmIndex)
	{
		//获取传感器状态
	case 2200:
	{
		if (list.count() < 1)
			break;
		QString SensorStatus = list.at(0);
		if (SensorStatus.count() < 12)
			break;
		bool b;
		b = (int)(SensorStatus.at(0).toLatin1()-'0')==1?true:false;
		ui.TRBtn->setChecked(b);//土壤水分开关
		b = (int)(SensorStatus.at(1).toLatin1()-'0') == 1 ? true : false;
		ui.WDBtn->setChecked(b);//空气温度
		b = (int)(SensorStatus.at(2).toLatin1()-'0') == 1 ? true : false;
		ui.QYBtn->setChecked(b);  //气压
		b = (int)(SensorStatus.at(3).toLatin1()-'0') == 1 ? true : false;//风速
		ui.FXBtn->setChecked(b);
		b = (int)(SensorStatus.at(4).toLatin1()-'0') == 1 ? true : false;;//辐射
		ui.FSBtn->setChecked(b);
		b = (int)(SensorStatus.at(5).toLatin1()-'0') == 1 ? true : false;;//光和有效
		ui.GHYXBtn->setChecked(b);
		b = (int)(SensorStatus.at(6).toLatin1()-'0') == 1 ? true : false;;//紫外线气压
		ui.ZWXBtn->setChecked(b);
		b = (int)(SensorStatus.at(7).toLatin1()-'0') == 1 ? true : false;;//光照度
		ui.GZDBtn->setChecked(b);
		b = (int)(SensorStatus.at(8).toLatin1()-'0') == 1 ? true : false;;//二氧化碳
		ui.EYHTBtn->setChecked(b);
		b = (int)(SensorStatus.at(9).toLatin1()-'0') == 1 ? true : false;;//插针式
		ui.CZSBtn->setChecked(b);
		b = (int)(SensorStatus.at(10).toLatin1()-'0') == 1 ? true : false;;//雨量
		ui.YLBtn->setChecked(b);
		b = (int)(SensorStatus.at(11).toLatin1() - '0') == 1 ? true : false;//土壤EC
		ui.CZSECBtn->setChecked(b);
		break;
	}
	case 2202://读取IP
	{
		if (list.count() < 2)
			break;
		QStringList ip = list.at(0).split(".");
		if (ip.count() < 4)
			break;
		ui.DevicelineEdit_IP1->setText(ip.at(0));
		ui.DevicelineEdit_IP2->setText(ip.at(1));
		ui.DevicelineEdit_IP3->setText(ip.at(2));
		ui.DevicelineEdit_IP4->setText(ip.at(3));
		ui.DevicelineEdit_Port->setText(list.at(1));
		break;
	}
	case 2205://读取时钟
	{
		if (list.count() < 1)
			break;
		QDateTime time = QDateTime::fromString(list.at(0), "yyyy-MM-dd hh:mm:ss");
		ui.RdateTimeEdit->setDateTime(time);
		break;
	}
	case 2207://读取地址
	{
		if (list.count() < 1)
			break;
		QString addr = list.at(0);
		ui.lineEdit_Addr->setText(addr);
		break;
	}
	
	default:
	{
		if (list.count() < 1)
			break;
		QString r = list.at(0);
		if (r.compare(QString::fromLocal8Bit("T")) == 0)
		{
			if (m_pTimer->isActive())
			StopAnimation();
			QMessageBox::about(this, QString::fromLocal8Bit("状态"), QString::fromLocal8Bit("操作成功"));
		}
	}
	break;
	}
	StopAnimation();
}




