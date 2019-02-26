
#include<windows.h>
#include <QWidget>
#include "ui_ControlUI.h"
#include<QMouseEvent>
#include <QMessageBox>
#include<QTimer>
#include<QPixmap>
class ControlUI : public QWidget
{
	Q_OBJECT

public:
	ControlUI(QWidget *parent = 0);
	~ControlUI();
	void setValue(QStringList);
	bool *isActive;
	void GetSensorStatus();//获取传感器状态
private:
	Ui::ControlUI ui;
	//窗体移动
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	bool m_Drag;               
	QPoint m_DragPosition;
	int cmmIndex;//命令号
	bool m_bCZS, m_bEYH, m_bFS, m_bFX, m_bGHYX, m_bGZD, m_bQY, m_bTR, m_bWD, m_bYL, m_bZWX;//传感器状态
	//等待界面控件
	QLabel *m_pLoadingLabel;
	QLabel *m_pTipLabel;
	//等待界面时间
	QTimer *m_pTimer;
	//图片编号
	int m_nIndex=0;
	//超时判断
	int m_TimeOut=0;
	void StartAnimation();
	void StopAnimation();
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void slot_minWindow();

    void on_TRBtn_clicked(bool check);

    void on_WDBtn_clicked(bool check);

    void on_FXBtn_clicked(bool check);

    void on_ZWXBtn_clicked(bool check);

    void on_FSBtn_clicked(bool check);

    void on_GZDBtn_clicked(bool check);

    void on_QYBtn_clicked(bool check);

    void on_GHYXBtn_clicked(bool check);

    void on_EYHTBtn_clicked(bool check);

    void on_CZSBtn_clicked(bool check);

    void on_YLBtn_clicked(bool check);

    void on_RIPBtn_clicked();

    void on_WIPBtn_clicked();

    void on_RTimeBtn_clicked();

    void on_WTimeBtn_clicked();

    void on_DownBtn_clicked();

    void on_RAddrBtn_clicked();

    void on_WAddrBtn_clicked();

	void on_WSetBtn_clicked();

	void updatePixmap();
public:
	QString StationID;
	uint Socket;
};

