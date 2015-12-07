/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created: Mon Dec 7 13:58:37 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *messageLabel;
    QPushButton *connectButton;
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
    QPushButton *pushButton;
    QLineEdit *sendLineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *uidnum_label;
    QPushButton *regist_pushButton;
    QPushButton *see_all_bid_pushButton;
    QPushButton *submit_pushButton;
    QPushButton *bid_pushButton;
    QPushButton *see_all_your_bid_pushButton;
    QPushButton *deregist_pushButton;
    QPushButton *withdraw_pushButton;
    QLabel *label_5;
    QLabel *namelabel;
    QPushButton *see_all_your_item_pushButton;

    void setupUi(QDialog *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(1000, 714);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(243, 243, 243, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(249, 249, 249, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(121, 121, 121, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(162, 162, 162, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Client->setPalette(palette);
        label = new QLabel(Client);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 20, 81, 31));
        label_2 = new QLabel(Client);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 70, 81, 31));
        messageLabel = new QLabel(Client);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setGeometry(QRect(0, 130, 751, 511));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        QBrush brush7(QColor(120, 120, 120, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush);
        messageLabel->setPalette(palette1);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        messageLabel->setFont(font);
        messageLabel->setFrameShape(QFrame::Panel);
        messageLabel->setFrameShadow(QFrame::Sunken);
        messageLabel->setWordWrap(true);
        connectButton = new QPushButton(Client);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(800, 10, 191, 61));
        hostLineEdit = new QLineEdit(Client);
        hostLineEdit->setObjectName(QString::fromUtf8("hostLineEdit"));
        hostLineEdit->setGeometry(QRect(240, 10, 491, 51));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        hostLineEdit->setPalette(palette2);
        portLineEdit = new QLineEdit(Client);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setGeometry(QRect(230, 70, 491, 51));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        portLineEdit->setPalette(palette3);
        pushButton = new QPushButton(Client);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setGeometry(QRect(790, 620, 201, 61));
        sendLineEdit = new QLineEdit(Client);
        sendLineEdit->setObjectName(QString::fromUtf8("sendLineEdit"));
        sendLineEdit->setEnabled(false);
        sendLineEdit->setGeometry(QRect(170, 650, 471, 51));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        sendLineEdit->setPalette(palette4);
        label_3 = new QLabel(Client);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 660, 116, 34));
        label_4 = new QLabel(Client);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 10, 51, 21));
        uidnum_label = new QLabel(Client);
        uidnum_label->setObjectName(QString::fromUtf8("uidnum_label"));
        uidnum_label->setGeometry(QRect(90, 10, 81, 21));
        regist_pushButton = new QPushButton(Client);
        regist_pushButton->setObjectName(QString::fromUtf8("regist_pushButton"));
        regist_pushButton->setEnabled(false);
        regist_pushButton->setGeometry(QRect(790, 70, 201, 61));
        see_all_bid_pushButton = new QPushButton(Client);
        see_all_bid_pushButton->setObjectName(QString::fromUtf8("see_all_bid_pushButton"));
        see_all_bid_pushButton->setEnabled(false);
        see_all_bid_pushButton->setGeometry(QRect(790, 140, 201, 61));
        submit_pushButton = new QPushButton(Client);
        submit_pushButton->setObjectName(QString::fromUtf8("submit_pushButton"));
        submit_pushButton->setEnabled(false);
        submit_pushButton->setGeometry(QRect(790, 210, 201, 61));
        bid_pushButton = new QPushButton(Client);
        bid_pushButton->setObjectName(QString::fromUtf8("bid_pushButton"));
        bid_pushButton->setEnabled(false);
        bid_pushButton->setGeometry(QRect(790, 280, 201, 61));
        see_all_your_bid_pushButton = new QPushButton(Client);
        see_all_your_bid_pushButton->setObjectName(QString::fromUtf8("see_all_your_bid_pushButton"));
        see_all_your_bid_pushButton->setEnabled(false);
        see_all_your_bid_pushButton->setGeometry(QRect(790, 350, 201, 61));
        deregist_pushButton = new QPushButton(Client);
        deregist_pushButton->setObjectName(QString::fromUtf8("deregist_pushButton"));
        deregist_pushButton->setEnabled(false);
        deregist_pushButton->setGeometry(QRect(790, 550, 201, 61));
        withdraw_pushButton = new QPushButton(Client);
        withdraw_pushButton->setObjectName(QString::fromUtf8("withdraw_pushButton"));
        withdraw_pushButton->setEnabled(false);
        withdraw_pushButton->setGeometry(QRect(790, 480, 201, 61));
        label_5 = new QLabel(Client);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 40, 71, 31));
        namelabel = new QLabel(Client);
        namelabel->setObjectName(QString::fromUtf8("namelabel"));
        namelabel->setGeometry(QRect(80, 50, 61, 21));
        see_all_your_item_pushButton = new QPushButton(Client);
        see_all_your_item_pushButton->setObjectName(QString::fromUtf8("see_all_your_item_pushButton"));
        see_all_your_item_pushButton->setEnabled(false);
        see_all_your_item_pushButton->setGeometry(QRect(790, 420, 201, 61));

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QDialog *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Client", "host:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Client", "port:", 0, QApplication::UnicodeUTF8));
        messageLabel->setText(QApplication::translate("Client", "Welcome to the Auction system\n"
"\n"
"write host address\n"
"and the port number\n"
"then press connect button\n"
"to connect to the server", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("Client", "connect", 0, QApplication::UnicodeUTF8));
        hostLineEdit->setText(QApplication::translate("Client", "192.168.0.233", 0, QApplication::UnicodeUTF8));
        portLineEdit->setText(QApplication::translate("Client", "2333", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Client", "send", 0, QApplication::UnicodeUTF8));
        sendLineEdit->setText(QString());
        label_3->setText(QApplication::translate("Client", "send:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Client", "uid:", 0, QApplication::UnicodeUTF8));
        uidnum_label->setText(QString());
        regist_pushButton->setText(QApplication::translate("Client", "regist", 0, QApplication::UnicodeUTF8));
        see_all_bid_pushButton->setText(QApplication::translate("Client", "see all bid", 0, QApplication::UnicodeUTF8));
        submit_pushButton->setText(QApplication::translate("Client", "submit an item", 0, QApplication::UnicodeUTF8));
        bid_pushButton->setText(QApplication::translate("Client", "bid an item", 0, QApplication::UnicodeUTF8));
        see_all_your_bid_pushButton->setText(QApplication::translate("Client", "see all your bid", 0, QApplication::UnicodeUTF8));
        deregist_pushButton->setText(QApplication::translate("Client", "deregist", 0, QApplication::UnicodeUTF8));
        withdraw_pushButton->setText(QApplication::translate("Client", "withdraw item", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Client", "name:", 0, QApplication::UnicodeUTF8));
        namelabel->setText(QString());
        see_all_your_item_pushButton->setText(QApplication::translate("Client", "see all you item", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
