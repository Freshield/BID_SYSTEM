#ifndef WITHDRAWITEMDIALOG_H
#define WITHDRAWITEMDIALOG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
    class WithdrawItemDialog;
}

class WithdrawItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawItemDialog(QWidget *parent,QString data,QString parentuid);
    ~WithdrawItemDialog();

private:
    Ui::WithdrawItemDialog *ui;
    QString biditeminfo;
    QString m_itemscode;
    QString m_itemprice;
    QString m_parentuid;
signals:
    void biditemsinfo(QString itemcode);
private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
};

#endif // WITHDRAWITEMDIALOG_H
