#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>

namespace Ui {
class SERVER;
}

class SERVER : public QMainWindow
{
    Q_OBJECT

public:
    explicit SERVER(QWidget *parent = 0);
    ~SERVER();

private slots:
    void on_Button1_clicked();

private:
    Ui::SERVER *ui;
};

#endif // SERVER_H
