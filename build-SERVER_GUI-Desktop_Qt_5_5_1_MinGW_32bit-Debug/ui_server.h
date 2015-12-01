/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SERVER
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *Button1;
    QPushButton *Button2;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SERVER)
    {
        if (SERVER->objectName().isEmpty())
            SERVER->setObjectName(QStringLiteral("SERVER"));
        SERVER->resize(802, 511);
        centralWidget = new QWidget(SERVER);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 20, 531, 301));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        Button1 = new QPushButton(centralWidget);
        Button1->setObjectName(QStringLiteral("Button1"));
        Button1->setGeometry(QRect(620, 20, 141, 51));
        Button2 = new QPushButton(centralWidget);
        Button2->setObjectName(QStringLiteral("Button2"));
        Button2->setGeometry(QRect(620, 110, 141, 51));
        SERVER->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SERVER);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 802, 30));
        SERVER->setMenuBar(menuBar);
        statusBar = new QStatusBar(SERVER);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SERVER->setStatusBar(statusBar);

        retranslateUi(SERVER);

        QMetaObject::connectSlotsByName(SERVER);
    } // setupUi

    void retranslateUi(QMainWindow *SERVER)
    {
        SERVER->setWindowTitle(QApplication::translate("SERVER", "SERVER", 0));
        label->setText(QString());
        Button1->setText(QApplication::translate("SERVER", "1", 0));
        Button2->setText(QApplication::translate("SERVER", "2", 0));
    } // retranslateUi

};

namespace Ui {
    class SERVER: public Ui_SERVER {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
