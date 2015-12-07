/********************************************************************************
** Form generated from reading UI file 'seeallbiddialog.ui'
**
** Created: Sat Dec 5 21:07:01 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEEALLBIDDIALOG_H
#define UI_SEEALLBIDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_SeeAllBidDialog
{
public:
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QDialog *SeeAllBidDialog)
    {
        if (SeeAllBidDialog->objectName().isEmpty())
            SeeAllBidDialog->setObjectName(QString::fromUtf8("SeeAllBidDialog"));
        SeeAllBidDialog->resize(1048, 1082);
        label = new QLabel(SeeAllBidDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 0, 671, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setItalic(true);
        label->setFont(font);
        listWidget = new QListWidget(SeeAllBidDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 80, 1021, 991));

        retranslateUi(SeeAllBidDialog);

        QMetaObject::connectSlotsByName(SeeAllBidDialog);
    } // setupUi

    void retranslateUi(QDialog *SeeAllBidDialog)
    {
        SeeAllBidDialog->setWindowTitle(QApplication::translate("SeeAllBidDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SeeAllBidDialog", "Here is all items now", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SeeAllBidDialog: public Ui_SeeAllBidDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEEALLBIDDIALOG_H
