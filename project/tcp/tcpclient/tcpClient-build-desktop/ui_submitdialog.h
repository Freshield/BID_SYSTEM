/********************************************************************************
** Form generated from reading UI file 'submitdialog.ui'
**
** Created: Sat Dec 5 20:13:11 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBMITDIALOG_H
#define UI_SUBMITDIALOG_H

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

class Ui_SubmitDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QDialog *SubmitDialog)
    {
        if (SubmitDialog->objectName().isEmpty())
            SubmitDialog->setObjectName(QString::fromUtf8("SubmitDialog"));
        SubmitDialog->resize(582, 512);
        label = new QLabel(SubmitDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 531, 261));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setItalic(true);
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEdit = new QLineEdit(SubmitDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(110, 300, 381, 61));
        label_2 = new QLabel(SubmitDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 320, 116, 34));
        pushButton = new QPushButton(SubmitDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(180, 410, 187, 57));

        retranslateUi(SubmitDialog);

        QMetaObject::connectSlotsByName(SubmitDialog);
    } // setupUi

    void retranslateUi(QDialog *SubmitDialog)
    {
        SubmitDialog->setWindowTitle(QApplication::translate("SubmitDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SubmitDialog", "Pleas write the \n"
"item's name\n"
"that you want to submit\n"
"and press confirm", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SubmitDialog", "NAME:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SubmitDialog", "CONFIRM", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SubmitDialog: public Ui_SubmitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBMITDIALOG_H
