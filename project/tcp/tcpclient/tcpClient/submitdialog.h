#ifndef SUBMITDIALOG_H
#define SUBMITDIALOG_H

#include <QDialog>

namespace Ui {
    class SubmitDialog;
}

class SubmitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubmitDialog(QWidget *parent = 0);
    ~SubmitDialog();

private slots:
    void on_pushButton_clicked();
signals:
    void CallMainWindowItemName(QString name);

private:
    Ui::SubmitDialog *ui;
};

#endif // SUBMITDIALOG_H
