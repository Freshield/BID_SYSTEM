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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SERVER
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SERVER)
    {
        if (SERVER->objectName().isEmpty())
            SERVER->setObjectName(QStringLiteral("SERVER"));
        SERVER->resize(698, 512);
        centralWidget = new QWidget(SERVER);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 20, 531, 301));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        SERVER->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SERVER);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 698, 30));
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
    } // retranslateUi

};

namespace Ui {
    class SERVER: public Ui_SERVER {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
