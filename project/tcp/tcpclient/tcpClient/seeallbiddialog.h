#ifndef SEEALLBIDDIALOG_H
#define SEEALLBIDDIALOG_H

#include <QDialog>

namespace Ui {
    class SeeAllBidDialog;
}

class SeeAllBidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeeAllBidDialog(QWidget *parent,QString data);
    ~SeeAllBidDialog();

private:
    Ui::SeeAllBidDialog *ui;
    QString allbidinfo;
};

#endif // SEEALLBIDDIALOG_H
