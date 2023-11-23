/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QWidget *responsiveness;
    QWidget *responsiveness_indicator;
    QWidget *call_for_help;
    QWidget *help_indicator;
    QWidget *attach_defibs;
    QWidget *defibs_indicator;
    QWidget *analyzing;
    QWidget *analyzing_indicator;
    QWidget *cpr_img1;
    QWidget *shock;
    QWidget *shock_indicator;
    QWidget *display;
    QWidget *connectors;
    QWidget *cpr_img_2;
    QWidget *cpr;
    QWidget *cpr_indicator;
    QPushButton *power_button;
    QWidget *status_indicator;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1037, 920);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(183, 197, 86);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1041, 771));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 92, 100);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        responsiveness = new QWidget(frame);
        responsiveness->setObjectName(QString::fromUtf8("responsiveness"));
        responsiveness->setGeometry(QRect(90, 220, 201, 141));
        responsiveness->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        responsiveness_indicator = new QWidget(responsiveness);
        responsiveness_indicator->setObjectName(QString::fromUtf8("responsiveness_indicator"));
        responsiveness_indicator->setGeometry(QRect(180, 120, 18, 18));
        responsiveness_indicator->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);\n"
"border-style: solid;\n"
"border-width: 5px;\n"
"border-radius: 8px;\n"
"max-width: 8px;\n"
"max-height: 8px;\n"
"min-width: 8px;\n"
"min-height: 8px;"));
        call_for_help = new QWidget(frame);
        call_for_help->setObjectName(QString::fromUtf8("call_for_help"));
        call_for_help->setGeometry(QRect(430, 20, 201, 141));
        call_for_help->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        help_indicator = new QWidget(call_for_help);
        help_indicator->setObjectName(QString::fromUtf8("help_indicator"));
        help_indicator->setGeometry(QRect(10, 120, 18, 18));
        help_indicator->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);\n"
"border-style: solid;\n"
"border-width: 5px;\n"
"border-radius: 8px;\n"
"max-width: 8px;\n"
"max-height: 8px;\n"
"min-width: 8px;\n"
"min-height: 8px;"));
        attach_defibs = new QWidget(frame);
        attach_defibs->setObjectName(QString::fromUtf8("attach_defibs"));
        attach_defibs->setGeometry(QRect(810, 290, 201, 141));
        attach_defibs->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        defibs_indicator = new QWidget(attach_defibs);
        defibs_indicator->setObjectName(QString::fromUtf8("defibs_indicator"));
        defibs_indicator->setGeometry(QRect(0, 120, 18, 18));
        defibs_indicator->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);\n"
"border-style: solid;\n"
"border-width: 5px;\n"
"border-radius: 8px;\n"
"max-width: 8px;\n"
"max-height: 8px;\n"
"min-width: 8px;\n"
"min-height: 8px;"));
        analyzing = new QWidget(frame);
        analyzing->setObjectName(QString::fromUtf8("analyzing"));
        analyzing->setGeometry(QRect(670, 580, 201, 141));
        analyzing->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        analyzing_indicator = new QWidget(analyzing);
        analyzing_indicator->setObjectName(QString::fromUtf8("analyzing_indicator"));
        analyzing_indicator->setGeometry(QRect(180, 10, 18, 18));
        analyzing_indicator->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);\n"
"border-style: solid;\n"
"border-width: 5px;\n"
"border-radius: 8px;\n"
"max-width: 8px;\n"
"max-height: 8px;\n"
"min-width: 8px;\n"
"min-height: 8px;"));
        cpr_img1 = new QWidget(frame);
        cpr_img1->setObjectName(QString::fromUtf8("cpr_img1"));
        cpr_img1->setGeometry(QRect(270, 580, 201, 141));
        cpr_img1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        shock = new QWidget(frame);
        shock->setObjectName(QString::fromUtf8("shock"));
        shock->setGeometry(QRect(440, 370, 180, 180));
        shock->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);\n"
"border-style: solid;\n"
"border-width: 50px;\n"
"border-radius: 80px;\n"
"max-width: 80px;\n"
"max-height: 80px;\n"
"min-width: 80px;\n"
"min-height: 80px;\n"
""));
        shock_indicator = new QWidget(shock);
        shock_indicator->setObjectName(QString::fromUtf8("shock_indicator"));
        shock_indicator->setGeometry(QRect(80, 80, 18, 18));
        shock_indicator->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);\n"
"border-style: solid;\n"
"border-width: 5px;\n"
"border-radius: 8px;\n"
"max-width: 8px;\n"
"max-height: 8px;\n"
"min-width: 8px;\n"
"min-height: 8px;"));
        display = new QWidget(frame);
        display->setObjectName(QString::fromUtf8("display"));
        display->setGeometry(QRect(320, 200, 431, 141));
        display->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);"));
        connectors = new QWidget(frame);
        connectors->setObjectName(QString::fromUtf8("connectors"));
        connectors->setGeometry(QRect(10, 330, 51, 331));
        connectors->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);"));
        cpr_img_2 = new QWidget(frame);
        cpr_img_2->setObjectName(QString::fromUtf8("cpr_img_2"));
        cpr_img_2->setGeometry(QRect(110, 470, 211, 151));
        cpr_img_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        cpr = new QWidget(cpr_img_2);
        cpr->setObjectName(QString::fromUtf8("cpr"));
        cpr->setGeometry(QRect(160, 110, 51, 41));
        cpr_indicator = new QWidget(cpr);
        cpr_indicator->setObjectName(QString::fromUtf8("cpr_indicator"));
        cpr_indicator->setGeometry(QRect(20, 10, 18, 18));
        cpr_indicator->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);\n"
"border-style: solid;\n"
"border-width: 5px;\n"
"border-radius: 8px;\n"
"max-width: 8px;\n"
"max-height: 8px;\n"
"min-width: 8px;\n"
"min-height: 8px;"));
        power_button = new QPushButton(centralwidget);
        power_button->setObjectName(QString::fromUtf8("power_button"));
        power_button->setGeometry(QRect(870, 810, 122, 72));
        power_button->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);\n"
"border-style: solid;\n"
"border-width: 1px;\n"
"border-radius: 30px;\n"
"max-width: 120px;\n"
"max-height: 70px;\n"
"min-width: 120px;\n"
"min-height: 70px;\n"
""));
        status_indicator = new QWidget(centralwidget);
        status_indicator->setObjectName(QString::fromUtf8("status_indicator"));
        status_indicator->setGeometry(QRect(30, 810, 120, 80));
        status_indicator->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 118, 123);"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        power_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
