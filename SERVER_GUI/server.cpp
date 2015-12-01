#include "server.h"
#include "ui_server.h"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <stdio.h>
#include <string>
#pragma comment (lib, "ws2_32")
using namespace std;


SOCKET sockClient;//client socket
vector <SOCKET> clientSocketGroup;//socket pool
int rev = 0;
int button = 0;
SOCKET sockSrv;
int client_count = 0;
HANDLE bufferMutex;//Semaphore
int uid_number = 100;
int item_number = 8;
int item_vector_num = 0;
//---------------UID-----------------------//
struct UID
{
    int number;
    SOCKET sockets_value;
    int registed = 0;

};

vector<UID> uid;

//---------------/UID-----------------------//

//---------------ITEM-----------------------//
struct ITEM
{
    string name;
    string price = "NULL";
    string owner = "NULL";
    string buyer = "NULL";
    int itemcode = 0;
    int show = 0;

};

vector<ITEM> item;


SERVER::SERVER(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SERVER)
{
    ui->setupUi(this);
    //----------------load socket dll-----------------------//

        WORD wVersionRequested;
        WSADATA wsaData;
        wVersionRequested = MAKEWORD(2, 2);

        //find error
        int err = WSAStartup(wVersionRequested, &wsaData);
        if (err != 0)
        {
            ui->label->setText("WSAStartup error");

        }
        ui->label->setText("WSAStartup finished");

}

SERVER::~SERVER()
{
    delete ui;
}

void SERVER::on_Button1_clicked()
{

}
