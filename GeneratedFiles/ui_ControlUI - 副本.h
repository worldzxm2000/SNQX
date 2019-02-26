/********************************************************************************
** Form generated from reading UI file 'ControlUI.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLUI_H
#define UI_CONTROLUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include"SwitchButton.h"
#include"MyButton.h"
QT_BEGIN_NAMESPACE

class Ui_ControlUI
{
public:
    QGroupBox *groupBox_2;
    QLabel *TiltleLabel;
    QGroupBox *groupBox_3;
    QScrollArea *ScrollArea_MinBtn;
    QWidget *ScrollAreaWidgetContents_MinBtn;
	MyButton *MinBtn;
    QScrollArea *ScrollArea_CloseBtn;
    QWidget *ScrollAreaWidgetContents_CloseBtn;
	MyButton *CloseBtn;
    QGroupBox *groupBox;
    QGroupBox *groupBox_down;
    QDateTimeEdit *BdateTimeEdit;
    QDateTimeEdit *EdateTimeEdit;
    QPushButton *DownBtn;
    QGroupBox *groupBox_time;
    QDateTimeEdit *RdateTimeEdit;
    QPushButton *RTimeBtn;
    QPushButton *WTimeBtn;
    QGroupBox *groupBox_IP;
    QPushButton *RIPBtn;
    QPushButton *WIPBtn;
    QLineEdit *DevicelineEdit_IP1;
    QLineEdit *DevicelineEdit_IP2;
    QLineEdit *DevicelineEdit_IP3;
    QLineEdit *DevicelineEdit_IP4;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *DevicelineEdit_Port;
    QLabel *label_5;
    QGroupBox *groupBox_Addr;
    QPushButton *RAddrBtn;
    QPushButton *WAddrBtn;
    QLineEdit *lineEdit_Addr;
    QGroupBox *groupBox_Sensor;
    QLabel *label;
	SwitchButton *TRBtn;
    QLabel *label_7;
	SwitchButton *WDBtn;
	SwitchButton *QYBtn;
    QLabel *label_8;
    QLabel *label_9;
	SwitchButton *FXBtn;
    QLabel *label_10;
	SwitchButton *GHYXBtn;
    QLabel *label_11;
	SwitchButton *FSBtn;
    QLabel *label_12;
	SwitchButton *ZWXBtn;
    QLabel *label_13;
	SwitchButton *EYHTBtn;
    QLabel *label_14;
	SwitchButton *GZDBtn;
	SwitchButton *CZSBtn;
    QLabel *label_15;
	SwitchButton *YLBtn;
    QLabel *label_16;
    QPushButton *WSetBtn;
	SwitchButton *CZSECBtn;
    QLabel *label_17;
    QLabel *TitleLabel_Name;

    void setupUi(QWidget *ControlUI)
    {
        if (ControlUI->objectName().isEmpty())
            ControlUI->setObjectName(QStringLiteral("ControlUI"));
        ControlUI->resize(410, 607);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        ControlUI->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("../Image/png/Weather.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ControlUI->setWindowIcon(icon);
        ControlUI->setStyleSheet(QStringLiteral("background:rgb(77,77, 77);color:white"));
        groupBox_2 = new QGroupBox(ControlUI);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(5, 5, 401, 591));
        groupBox_2->setFont(font);
        TiltleLabel = new QLabel(groupBox_2);
        TiltleLabel->setObjectName(QStringLiteral("TiltleLabel"));
        TiltleLabel->setGeometry(QRect(10, 10, 32, 32));
        TiltleLabel->setFont(font);
        TiltleLabel->setPixmap(QPixmap(QString::fromUtf8("../Image/png/control.png")));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(350, 10, 46, 26));
        groupBox_3->setFont(font);
        ScrollArea_MinBtn = new QScrollArea(groupBox_3);
        ScrollArea_MinBtn->setObjectName(QStringLiteral("ScrollArea_MinBtn"));
        ScrollArea_MinBtn->setGeometry(QRect(2, 3, 20, 20));
        ScrollArea_MinBtn->setFont(font);
        ScrollArea_MinBtn->setWidgetResizable(true);
        ScrollAreaWidgetContents_MinBtn = new QWidget();
        ScrollAreaWidgetContents_MinBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_MinBtn"));
        ScrollAreaWidgetContents_MinBtn->setGeometry(QRect(0, 0, 18, 18));
		MinBtn = new MyButton("../Image/png/Mini.png", 1, ScrollAreaWidgetContents_MinBtn);
        MinBtn->setObjectName(QStringLiteral("MinBtn"));
        MinBtn->setGeometry(QRect(1, 1, 18, 18));
        MinBtn->setFont(font);
        ScrollArea_MinBtn->setWidget(ScrollAreaWidgetContents_MinBtn);
        ScrollArea_CloseBtn = new QScrollArea(groupBox_3);
        ScrollArea_CloseBtn->setObjectName(QStringLiteral("ScrollArea_CloseBtn"));
        ScrollArea_CloseBtn->setGeometry(QRect(24, 3, 20, 20));
        ScrollArea_CloseBtn->setFont(font);
        ScrollArea_CloseBtn->setWidgetResizable(true);
        ScrollAreaWidgetContents_CloseBtn = new QWidget();
        ScrollAreaWidgetContents_CloseBtn->setObjectName(QStringLiteral("ScrollAreaWidgetContents_CloseBtn"));
        ScrollAreaWidgetContents_CloseBtn->setGeometry(QRect(0, 0, 18, 18));
		CloseBtn = new MyButton("../Image/png/Close.png", 1, ScrollAreaWidgetContents_CloseBtn);
        CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
        CloseBtn->setGeometry(QRect(1, 1, 18, 18));
        CloseBtn->setFont(font);
        ScrollArea_CloseBtn->setWidget(ScrollAreaWidgetContents_CloseBtn);
        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 50, 381, 531));
        groupBox->setFont(font);
        groupBox_down = new QGroupBox(groupBox);
        groupBox_down->setObjectName(QStringLiteral("groupBox_down"));
        groupBox_down->setGeometry(QRect(10, 440, 241, 81));
        groupBox_down->setFont(font);
        BdateTimeEdit = new QDateTimeEdit(groupBox_down);
        BdateTimeEdit->setObjectName(QStringLiteral("BdateTimeEdit"));
        BdateTimeEdit->setGeometry(QRect(10, 20, 141, 22));
        BdateTimeEdit->setFont(font);
        BdateTimeEdit->setDateTime(QDateTime(QDate(2018, 9, 1), QTime(0, 0, 0)));
        EdateTimeEdit = new QDateTimeEdit(groupBox_down);
        EdateTimeEdit->setObjectName(QStringLiteral("EdateTimeEdit"));
        EdateTimeEdit->setGeometry(QRect(10, 50, 141, 22));
        EdateTimeEdit->setFont(font);
        EdateTimeEdit->setDateTime(QDateTime(QDate(2018, 9, 1), QTime(0, 0, 0)));
        DownBtn = new QPushButton(groupBox_down);
        DownBtn->setObjectName(QStringLiteral("DownBtn"));
        DownBtn->setGeometry(QRect(160, 20, 75, 23));
        DownBtn->setFont(font);
        groupBox_time = new QGroupBox(groupBox);
        groupBox_time->setObjectName(QStringLiteral("groupBox_time"));
        groupBox_time->setGeometry(QRect(190, 340, 171, 91));
        groupBox_time->setFont(font);
        RdateTimeEdit = new QDateTimeEdit(groupBox_time);
        RdateTimeEdit->setObjectName(QStringLiteral("RdateTimeEdit"));
        RdateTimeEdit->setGeometry(QRect(10, 20, 151, 22));
        RdateTimeEdit->setFont(font);
        RdateTimeEdit->setDateTime(QDateTime(QDate(2018, 9, 1), QTime(0, 0, 0)));
        RTimeBtn = new QPushButton(groupBox_time);
        RTimeBtn->setObjectName(QStringLiteral("RTimeBtn"));
        RTimeBtn->setGeometry(QRect(10, 50, 75, 23));
        RTimeBtn->setFont(font);
        WTimeBtn = new QPushButton(groupBox_time);
        WTimeBtn->setObjectName(QStringLiteral("WTimeBtn"));
        WTimeBtn->setGeometry(QRect(90, 50, 75, 23));
        WTimeBtn->setFont(font);
        groupBox_IP = new QGroupBox(groupBox);
        groupBox_IP->setObjectName(QStringLiteral("groupBox_IP"));
        groupBox_IP->setGeometry(QRect(10, 10, 351, 91));
        groupBox_IP->setFont(font);
        RIPBtn = new QPushButton(groupBox_IP);
        RIPBtn->setObjectName(QStringLiteral("RIPBtn"));
        RIPBtn->setGeometry(QRect(15, 55, 75, 23));
        RIPBtn->setFont(font);
        WIPBtn = new QPushButton(groupBox_IP);
        WIPBtn->setObjectName(QStringLiteral("WIPBtn"));
        WIPBtn->setGeometry(QRect(105, 55, 75, 23));
        WIPBtn->setFont(font);
        DevicelineEdit_IP1 = new QLineEdit(groupBox_IP);
        DevicelineEdit_IP1->setObjectName(QStringLiteral("DevicelineEdit_IP1"));
        DevicelineEdit_IP1->setGeometry(QRect(15, 25, 41, 20));
        DevicelineEdit_IP1->setFont(font);
        DevicelineEdit_IP2 = new QLineEdit(groupBox_IP);
        DevicelineEdit_IP2->setObjectName(QStringLiteral("DevicelineEdit_IP2"));
        DevicelineEdit_IP2->setGeometry(QRect(75, 25, 41, 20));
        DevicelineEdit_IP2->setFont(font);
        DevicelineEdit_IP3 = new QLineEdit(groupBox_IP);
        DevicelineEdit_IP3->setObjectName(QStringLiteral("DevicelineEdit_IP3"));
        DevicelineEdit_IP3->setGeometry(QRect(135, 25, 41, 20));
        DevicelineEdit_IP3->setFont(font);
        DevicelineEdit_IP4 = new QLineEdit(groupBox_IP);
        DevicelineEdit_IP4->setObjectName(QStringLiteral("DevicelineEdit_IP4"));
        DevicelineEdit_IP4->setGeometry(QRect(195, 25, 41, 20));
        DevicelineEdit_IP4->setFont(font);
        label_2 = new QLabel(groupBox_IP);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(62, 30, 10, 12));
        label_2->setFont(font);
        label_3 = new QLabel(groupBox_IP);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(123, 30, 10, 12));
        label_3->setFont(font);
        label_4 = new QLabel(groupBox_IP);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(182, 30, 10, 12));
        label_4->setFont(font);
        DevicelineEdit_Port = new QLineEdit(groupBox_IP);
        DevicelineEdit_Port->setObjectName(QStringLiteral("DevicelineEdit_Port"));
        DevicelineEdit_Port->setGeometry(QRect(255, 25, 81, 20));
        DevicelineEdit_Port->setFont(font);
        label_5 = new QLabel(groupBox_IP);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(240, 30, 10, 12));
        label_5->setFont(font);
        groupBox_Addr = new QGroupBox(groupBox);
        groupBox_Addr->setObjectName(QStringLiteral("groupBox_Addr"));
        groupBox_Addr->setGeometry(QRect(10, 340, 171, 91));
        groupBox_Addr->setFont(font);
        RAddrBtn = new QPushButton(groupBox_Addr);
        RAddrBtn->setObjectName(QStringLiteral("RAddrBtn"));
        RAddrBtn->setGeometry(QRect(10, 50, 75, 23));
        RAddrBtn->setFont(font);
        WAddrBtn = new QPushButton(groupBox_Addr);
        WAddrBtn->setObjectName(QStringLiteral("WAddrBtn"));
        WAddrBtn->setGeometry(QRect(90, 50, 75, 23));
        WAddrBtn->setFont(font);
        lineEdit_Addr = new QLineEdit(groupBox_Addr);
        lineEdit_Addr->setObjectName(QStringLiteral("lineEdit_Addr"));
        lineEdit_Addr->setGeometry(QRect(10, 20, 151, 20));
        lineEdit_Addr->setFont(font);
        groupBox_Sensor = new QGroupBox(groupBox);
        groupBox_Sensor->setObjectName(QStringLiteral("groupBox_Sensor"));
        groupBox_Sensor->setGeometry(QRect(10, 110, 351, 231));
        groupBox_Sensor->setFont(font);
        label = new QLabel(groupBox_Sensor);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 31, 16));
        label->setFont(font);
        TRBtn = new SwitchButton(groupBox_Sensor);
        TRBtn->setObjectName(QStringLiteral("TRBtn"));
        TRBtn->setGeometry(QRect(60, 25, 51, 23));
		TRBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_7 = new QLabel(groupBox_Sensor);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 80, 41, 16));
        label_7->setFont(font);
        WDBtn = new SwitchButton(groupBox_Sensor);
        WDBtn->setObjectName(QStringLiteral("WDBtn"));
        WDBtn->setGeometry(QRect(60, 75, 51, 23));
		WDBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        QYBtn = new SwitchButton(groupBox_Sensor);
        QYBtn->setObjectName(QStringLiteral("QYBtn"));
        QYBtn->setGeometry(QRect(60, 115, 51, 23));
		QYBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_8 = new QLabel(groupBox_Sensor);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 120, 41, 16));
        label_8->setFont(font);
        label_9 = new QLabel(groupBox_Sensor);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(130, 80, 31, 16));
        label_9->setFont(font);
        FXBtn = new SwitchButton(groupBox_Sensor);
        FXBtn->setObjectName(QStringLiteral("FXBtn"));
        FXBtn->setGeometry(QRect(170, 25, 51, 23));
		FXBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_10 = new QLabel(groupBox_Sensor);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(115, 30, 50, 16));
        label_10->setFont(font);
        GHYXBtn = new SwitchButton(groupBox_Sensor);
        GHYXBtn->setObjectName(QStringLiteral("GHYXBtn"));
        GHYXBtn->setGeometry(QRect(170, 115, 51, 23));
		GHYXBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_11 = new QLabel(groupBox_Sensor);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(115, 120, 50, 16));
        label_11->setFont(font);
        FSBtn = new SwitchButton(groupBox_Sensor);
        FSBtn->setObjectName(QStringLiteral("FSBtn"));
        FSBtn->setGeometry(QRect(170, 75, 51, 23));
		FSBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_12 = new QLabel(groupBox_Sensor);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(230, 80, 50, 16));
        label_12->setFont(font);
        ZWXBtn = new SwitchButton(groupBox_Sensor);
        ZWXBtn->setObjectName(QStringLiteral("ZWXBtn"));
        ZWXBtn->setGeometry(QRect(280, 25, 51, 23));
		ZWXBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_13 = new QLabel(groupBox_Sensor);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(230, 30, 50, 16));
        label_13->setFont(font);
        EYHTBtn = new SwitchButton(groupBox_Sensor);
        EYHTBtn->setObjectName(QStringLiteral("EYHTBtn"));
        EYHTBtn->setGeometry(QRect(280, 115, 51, 23));
		EYHTBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_14 = new QLabel(groupBox_Sensor);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(225, 120, 50, 16));
        label_14->setFont(font);
        GZDBtn = new SwitchButton(groupBox_Sensor);
        GZDBtn->setObjectName(QStringLiteral("GZDBtn"));
        GZDBtn->setGeometry(QRect(280, 75, 51, 23));
		GZDBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        CZSBtn = new SwitchButton(groupBox_Sensor);
        CZSBtn->setObjectName(QStringLiteral("CZSBtn"));
        CZSBtn->setGeometry(QRect(60, 155, 51, 23));
		CZSBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_15 = new QLabel(groupBox_Sensor);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 160, 41, 16));
        label_15->setFont(font);
        YLBtn = new SwitchButton(groupBox_Sensor);
        YLBtn->setObjectName(QStringLiteral("YLBtn"));
        YLBtn->setGeometry(QRect(170, 155, 51, 23));
		YLBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_16 = new QLabel(groupBox_Sensor);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(120, 160, 41, 16));
        label_16->setFont(font);
        WSetBtn = new QPushButton(groupBox_Sensor);
        WSetBtn->setObjectName(QStringLiteral("WSetBtn"));
        WSetBtn->setGeometry(QRect(250, 155, 75, 23));
        WSetBtn->setFont(font);
        CZSECBtn = new SwitchButton(groupBox_Sensor);
        CZSECBtn->setObjectName(QStringLiteral("CZSECBtn"));
        CZSECBtn->setGeometry(QRect(60, 200, 51, 23));
		CZSECBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
        label_17 = new QLabel(groupBox_Sensor);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 200, 41, 16));
        label_17->setFont(font);
        TitleLabel_Name = new QLabel(groupBox_2);
        TitleLabel_Name->setObjectName(QStringLiteral("TitleLabel_Name"));
        TitleLabel_Name->setGeometry(QRect(45, 15, 111, 16));
        TitleLabel_Name->setFont(font);
        QWidget::setTabOrder(DevicelineEdit_IP1, DevicelineEdit_IP2);
        QWidget::setTabOrder(DevicelineEdit_IP2, DevicelineEdit_IP3);
        QWidget::setTabOrder(DevicelineEdit_IP3, DevicelineEdit_IP4);
        QWidget::setTabOrder(DevicelineEdit_IP4, DevicelineEdit_Port);
        QWidget::setTabOrder(DevicelineEdit_Port, RIPBtn);
        QWidget::setTabOrder(RIPBtn, WIPBtn);
        QWidget::setTabOrder(WIPBtn, lineEdit_Addr);
        QWidget::setTabOrder(lineEdit_Addr, RAddrBtn);
        QWidget::setTabOrder(RAddrBtn, WAddrBtn);
        QWidget::setTabOrder(WAddrBtn, RdateTimeEdit);
        QWidget::setTabOrder(RdateTimeEdit, RTimeBtn);
        QWidget::setTabOrder(RTimeBtn, WTimeBtn);
        QWidget::setTabOrder(WTimeBtn, BdateTimeEdit);
        QWidget::setTabOrder(BdateTimeEdit, EdateTimeEdit);
        QWidget::setTabOrder(EdateTimeEdit, DownBtn);

        retranslateUi(ControlUI);

        QMetaObject::connectSlotsByName(ControlUI);
    } // setupUi

    void retranslateUi(QWidget *ControlUI)
    {
        ControlUI->setWindowTitle(QApplication::translate("ControlUI", "\344\276\277\346\220\272\345\274\217\346\260\224\350\261\241\350\256\276\345\244\207\346\216\247\345\210\266", nullptr));
        groupBox_2->setTitle(QString());
        TiltleLabel->setText(QString());
        groupBox_3->setTitle(QString());
        MinBtn->setText(QApplication::translate("ControlUI", "PushButton", nullptr));
        CloseBtn->setText(QApplication::translate("ControlUI", "PushButton", nullptr));
        groupBox->setTitle(QString());
        groupBox_down->setTitle(QApplication::translate("ControlUI", "\346\225\260\346\215\256\350\241\245\346\212\204", nullptr));
        DownBtn->setText(QApplication::translate("ControlUI", "\350\241\245\346\212\204\346\225\260\346\215\256", nullptr));
        groupBox_time->setTitle(QApplication::translate("ControlUI", "\350\256\276\345\244\207\346\227\266\351\227\264", nullptr));
        RTimeBtn->setText(QApplication::translate("ControlUI", "\350\257\273\345\217\226\346\227\266\351\222\237", nullptr));
        WTimeBtn->setText(QApplication::translate("ControlUI", "\350\256\276\347\275\256\346\227\266\351\222\237", nullptr));
        groupBox_IP->setTitle(QApplication::translate("ControlUI", "IP\347\253\257\345\217\243", nullptr));
        RIPBtn->setText(QApplication::translate("ControlUI", "\350\257\273\345\217\226IP", nullptr));
        WIPBtn->setText(QApplication::translate("ControlUI", "\350\256\276\347\275\256IP", nullptr));
        label_2->setText(QApplication::translate("ControlUI", ".", nullptr));
        label_3->setText(QApplication::translate("ControlUI", ".", nullptr));
        label_4->setText(QApplication::translate("ControlUI", ".", nullptr));
        label_5->setText(QApplication::translate("ControlUI", "\357\274\232", nullptr));
        groupBox_Addr->setTitle(QApplication::translate("ControlUI", "\351\207\207\351\233\206\345\231\250\345\234\260\345\235\200", nullptr));
        RAddrBtn->setText(QApplication::translate("ControlUI", "\350\257\273\345\217\226\345\234\260\345\235\200", nullptr));
        WAddrBtn->setText(QApplication::translate("ControlUI", "\350\256\276\347\275\256\345\234\260\345\235\200", nullptr));
        lineEdit_Addr->setText(QString());
        groupBox_Sensor->setTitle(QApplication::translate("ControlUI", "\344\274\240\346\204\237\345\231\250", nullptr));
        label->setText(QApplication::translate("ControlUI", "\345\234\237\345\243\244", nullptr));
        label_7->setText(QApplication::translate("ControlUI", "\346\270\251\346\271\277\345\272\246", nullptr));
        label_8->setText(QApplication::translate("ControlUI", "\346\260\224\345\216\213", nullptr));
        label_9->setText(QApplication::translate("ControlUI", "\350\276\220\345\260\204", nullptr));
        label_10->setText(QApplication::translate("ControlUI", "\351\243\216\351\200\237\351\243\216\345\220\221", nullptr));
        label_11->setText(QApplication::translate("ControlUI", "\345\205\211\345\222\214\346\234\211\346\225\210", nullptr));
        label_12->setText(QApplication::translate("ControlUI", "\345\205\211\347\205\247\345\272\246", nullptr));
        label_13->setText(QApplication::translate("ControlUI", "\347\264\253\345\244\226\347\272\277", nullptr));
        label_14->setText(QApplication::translate("ControlUI", "\344\272\214\346\260\247\345\214\226\347\242\263", nullptr));
        label_15->setText(QApplication::translate("ControlUI", "\346\217\222\351\222\210\345\274\217", nullptr));
        label_16->setText(QApplication::translate("ControlUI", "\351\233\250\351\207\217", nullptr));
        WSetBtn->setText(QApplication::translate("ControlUI", "\350\256\276\347\275\256", nullptr));
        label_17->setText(QApplication::translate("ControlUI", "\345\234\237\345\243\244EC", nullptr));
        TitleLabel_Name->setText(QApplication::translate("ControlUI", "\344\276\277\346\220\272\345\274\217\346\260\224\350\261\241\347\253\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlUI: public Ui_ControlUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLUI_H
