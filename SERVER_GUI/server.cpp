#include "server.h"
#include "ui_server.h"


SERVER::SERVER(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SERVER)
{

    ui->setupUi(this);

}

SERVER::~SERVER()
{
    delete ui;
}

void SERVER::on_Button1_clicked()
{


}
