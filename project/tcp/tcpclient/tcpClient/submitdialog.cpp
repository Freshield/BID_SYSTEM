#include "submitdialog.h"
#include "ui_submitdialog.h"
#include <QMessageBox>

SubmitDialog::SubmitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubmitDialog)
{
    ui->setupUi(this);
}

SubmitDialog::~SubmitDialog()
{
    delete ui;
}

void SubmitDialog::on_pushButton_clicked()
{
    QString getter = ui->lineEdit->text();
    if(getter == "")
    {
        QMessageBox::warning(this,tr("NAME"),tr("Name can not be empty!"));
        return;

    }
    else
    {
        emit CallMainWindowItemName(getter);
        close();
    }
}
