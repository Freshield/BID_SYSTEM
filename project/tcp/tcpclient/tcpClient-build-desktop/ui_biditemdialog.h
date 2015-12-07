/********************************************************************************
** Form generated from reading UI file 'biditemdialog.ui'
**
** Created: Sat Dec 5 22:01:10 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIDITEMDIALOG_H
#define UI_BIDITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_BidItemDialog
{
public:
    QListWidget *listWidget;
    QLabel *label;

    void setupUi(QDialog *BidItemDialog)
    {
        if (BidItemDialog->objectName().isEmpty())
            BidItemDialog->setObjectName(QString::fromUtf8("BidItemDialog"));
        BidItemDialog->resize(1048, 1082);
        listWidget = new QListWidget(BidItemDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 70, 1021, 991));
        label = new QLabel(BidItemDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 10, 831, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setItalic(true);
        label->setFont(font);

        retranslateUi(BidItemDialog);

        QMetaObject::connectSlotsByName(BidItemDialog);
    } // setupUi

    void retranslateUi(QDialog *BidItemDialog)
    {
        BidItemDialog->setWindowTitle(QApplication::translate("BidItemDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BidItemDialog", "Double cliek the item you want to bid", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BidItemDialog: public Ui_BidItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIDITEMDIALOG_H
