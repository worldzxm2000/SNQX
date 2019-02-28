#ifndef SH_TRSF_SJD_H
#define SH_TRSF_SJD_H
#define SH_TRSF_SJD_H_EXPORT __declspec(dllexport)
#ifdef SH_TRSF_SJD_H_EXPORT
#else
#define SH_TRSF_SJD __declspec(dllimport)
#endif
#include<windows.h>
#include<qjsonobject.h>
#include "ControlUI.h"

#define HEADER 0xAA
#define TAIL 0xDD
#define FE 0xFE
#define SNQX "7"
typedef struct DataFrame {
	//����(2�ֽ�)
	int len;
	//Դ��ַ(2�ֽ�)
	int SrcAddr;
	//Ŀ�ĵ�ַ(2�ֽ�)
	int DesAddr;
	//֡����
	int Command;
	//������
	QString data;

} Frame;


//����ṹ������
typedef union
{
	struct
	{
		byte low_byte;
		byte mlow_byte;
		byte mhigh_byte;
		byte high_byte;
	}float_byte;
	float  value;
}FLOAT_UNION;

//�ɼ�ʱ�ӷ�������
void Transform2Time(QString data, QJsonObject &json);
//�ɼ�����ַ
void Transform2Addr(QString data, QJsonObject &json);
//10��������
void Transform2FeatureData(QString data, QJsonObject &json);
//������
void Transform2Heartbeat(QString data, QJsonObject &json);
//ͨ�Ž���
void Transform2CloeseConnection(QString data, QJsonObject &json);
//���ݴ���ָ��
void Transform2ErrorData(QString data, QJsonObject &json);
//��ȡIP
void Transform2IPPort(QString data, QJsonObject &json);
//����������״̬
void Transform2SessiorStatus(QString data, QJsonObject &json);
//ʱ���ʽ
QString Convert2Time(QString strTime);
//��������
EXTERN_C SH_TRSF_SJD_H_EXPORT LRESULT Char2Json(QString &buff, QJsonObject &json);
//���ô���
EXTERN_C SH_TRSF_SJD_H_EXPORT void  GetControlWidget(QString StationID, uint Socket, QWidget* parent = NULL);
//��ȡҵ���
EXTERN_C SH_TRSF_SJD_H_EXPORT int GetServiceTypeID();
//��ȡҵ������
EXTERN_C SH_TRSF_SJD_H_EXPORT QString GetServiceTypeName();
//��ȡ�汾��
EXTERN_C SH_TRSF_SJD_H_EXPORT QString GetVersionNo();
//��ȡ�˿ں�
EXTERN_C SH_TRSF_SJD_H_EXPORT int GetPort();
//����ʱ��
EXTERN_C SH_TRSF_SJD_H_EXPORT void SetTime(QString StationID, uint Socket);
//��ʾ����ֵ
EXTERN_C SH_TRSF_SJD_H_EXPORT void  SetValueToControlWidget(QStringList list);
//��������
EXTERN_C SH_TRSF_SJD_H_EXPORT void SetCommand(uint Socket, int CommandType, QString Params1, QString Params2, QString StationID);

ControlUI *w;
bool isActive=false;//�ж��ն˴����Ƿ���

#endif // SH_TRSF_SJD_H
