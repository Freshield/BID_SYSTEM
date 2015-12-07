#ifndef BIDPRICEDIALOG_H
#define BIDPRICEDIALOG_H

#include <QDialog>

namespace Ui {
    class BidPriceDialog;
}

class BidPriceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BidPriceDialog(QWidget *parent,QString parentuid);
    ~BidPriceDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BidPriceDialog *ui;
    QString m_parentuid;
signals:
    void itempriceget(QString price);
};

#endif // BIDPRICEDIALOG_H
