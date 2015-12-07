/********************************************************************************
** Form generated from reading UI file 'withdrawitemdialog.ui'
**
** Created: Sun Dec 6 14:30:08 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WITHDRAWITEMDIALOG_H
#define UI_WITHDRAWITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_WithdrawItemDialog
{
public:
    QListWidget *listWidget;
    QLabel *label;

    void setupUi(QDialog *WithdrawItemDialog)
    {
        if (WithdrawItemDialog->objectName().isEmpty())
            WithdrawItemDialog->setObjectName(QString::fromUtf8("WithdrawItemDialog"));
        WithdrawItemDialog->resize(1048, 1082);
        listWidget = new QListWidget(WithdrawItemDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 80, 1021, 991));
        label = new QLabel(WithdrawItemDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 0, 951, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setItalic(true);
        label->setFont(font);

        retranslateUi(WithdrawItemDialog);

        QMetaObject::connectSlotsByName(WithdrawItemDialog);
    } // setupUi

    void retranslateUi(QDialog *WithdrawItemDialog)
    {
        WithdrawItemDialog->setWindowTitle(QApplication::translate("WithdrawItemDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WithdrawItemDialog", "Double click the item you want to withdraw", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WithdrawItemDialog: public Ui_WithdrawItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WITHDRAWITEMDIALOG_H
