/********************************************************************************
** Form generated from reading UI file 'bidpricedialog.ui'
**
** Created: Sat Dec 5 22:01:10 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIDPRICEDIALOG_H
#define UI_BIDPRICEDIALOG_H

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

class Ui_BidPriceDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QLineEdit *lineEdit;

    void setupUi(QDialog *BidPriceDialog)
    {
        if (BidPriceDialog->objectName().isEmpty())
            BidPriceDialog->setObjectName(QString::fromUtf8("BidPriceDialog"));
        BidPriceDialog->resize(511, 444);
        label = new QLabel(BidPriceDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 10, 501, 171));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setItalic(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(BidPriceDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 350, 187, 57));
        lineEdit = new QLineEdit(BidPriceDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(60, 230, 381, 71));

        retranslateUi(BidPriceDialog);

        QMetaObject::connectSlotsByName(BidPriceDialog);
    } // setupUi

    void retranslateUi(QDialog *BidPriceDialog)
    {
        BidPriceDialog->setWindowTitle(QApplication::translate("BidPriceDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BidPriceDialog", "write the price \n"
"you want\n"
"then press confirm", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("BidPriceDialog", "confirm", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BidPriceDialog: public Ui_BidPriceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIDPRICEDIALOG_H
