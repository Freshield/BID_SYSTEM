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
