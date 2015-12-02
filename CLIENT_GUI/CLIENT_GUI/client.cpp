#include "client.h"
#include "ui_client.h"
#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#pragma comment (lib, "ws2_32")
using namespace std;
int rev = 0;
string try_again;
SOCKET sockSrv;
int uid_number;
int quit_wait = 1;
int quit_button = 0;
HANDLE bufferMutex;//Semaphore



int connect_button = 0;
int statue = 0;


string first_show = "\
=========================================\n\
=                                       =\n\
=    ||         ======     ======       =\n\
=    ||         ||           ||         =\n\
=    ||         ======       ||         =\n\
=    ||         ||           ||         =\n\
=    =====      ======       ||         =\n\
=                                       =\n\
=                 *                     =\n\
=                                       =\n\
=   ======      ======     ======       =\n\
=   ||    ||      ||       ||    ||     =\n\
=   ========      ||       ||    ||     =\n\
=   ||    ||      ||       ||    ||     =\n\
=   ======      ======     ======       =\n\
=                                       =\n\
=========================================\n\
";

string chioce = "\
=========================                    \n\
   WHAT DO YOU WANT?                       \n\
PRESS 0:REGISTER FIRST                                           \n\
PRESS 1:SEE ALL BID NOW                    \n\
PRESS 2:SUBMIT AN ITEM                     \n\
PRESS 3:BIT AN ITEM                                           \n\
PRESS 4:SEE YOUR BID                                           \n\
PRESS 5:SEE YOUR ITEM                                           \n\
PRESS 6:TRY TO DEREGISTER                                    \n\
PRESS 7:TRY TO WITHDRAW THE ITEM                                    \n\
PRESS 8:CLEAN THE SCREEN                                    \n\
";

/*void goingtoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}*/

client::client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
label_tryagain:
    //-------------------socket dll strat--------------//
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);

    //find error
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        cout << "WSAStartup error" << endl;

    }

    //--------------------socket init----------------//
    sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    //find error
    if (sockSrv == INVALID_SOCKET)
    {
        cout << "make socket error" << endl;
        WSACleanup();
    }

    SOCKADDR_IN addrSrv;

    cout << "Write server's IP address please or press 1 to set 127.0.0.1\nor press 2 to set 192.168.0.233" << endl;
    addrSrv.sin_family = AF_INET;
    string IP_addr;
    string port_number;
    cin >> IP_addr;
    if (IP_addr == "1")
    {
        IP_addr = "127.0.0.1";
    }
    else if (IP_addr == "2")
    {
        IP_addr = "192.168.0.233";
    }
    addrSrv.sin_addr.S_un.S_addr = inet_addr(IP_addr.c_str());


    cout << "Write server's port number please or press 1 to set 2333" << endl;
    cin >> port_number;
    if (port_number == "1")
    {
        port_number = "2333";
    }
    int port = atoi(port_number.c_str());
    addrSrv.sin_port = htons(port);

    cout << "-----------CLIENT INIT FINISHED------------" << endl;
    //-----------------------------------------------------------------//
    //connect

    rev = connect(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    //find error
    if (rev == SOCKET_ERROR)//TO SOLVE NO SERVER ERROR
    {
        cout << endl << "CONNECT ERROR" << endl;
        cout << endl << "PRESS ANY TO TRY AGAIN" << endl;
        closesocket(sockSrv);
        WSACleanup();

        cout << endl << "ENTER quit to quit or any other word to try again" << endl;
        cin >> try_again;

        if (try_again == "quit")
        {
            cout << "END LINKING..." << endl;

        }
        else
        {
            closesocket(sockSrv);
            connect_button = 0;
            goto label_tryagain;
        }

    }

    cout << endl << "-----------CLIENT CONNECT FINISHED------------" << endl;


    //goingtoxy(0, 0);
    system("cls");
    cout << first_show << endl;
    cout << chioce << endl;
    cout << "CLIENT SEND:" << endl;

    //send(sockSrv, "\nAtten: A client has enter...", 200, 0);//first send to server

    //---------------------thread-------------------------------//

    bufferMutex = CreateSemaphore(NULL, 1, 1, NULL);

    DWORD WINAPI SendMessageThread(LPVOID IpParameter);
    DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);

    HANDLE sendThread = CreateThread(NULL, 0, SendMessageThread, NULL, 0, NULL);
    HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread, NULL, 0, NULL);

    //--------------------finished-------------------------------//
    WaitForSingleObject(sendThread, INFINITE);

    if (connect_button == 1)//TO SOLVE SERVER SHUTDOWN ERROR
    {
        closesocket(sockSrv);
        CloseHandle(sendThread);
        CloseHandle(receiveThread);
        CloseHandle(bufferMutex);
        WSACleanup();
        connect_button = 0;
        goto label_tryagain;
    }

    closesocket(sockSrv);
    CloseHandle(sendThread);
    CloseHandle(receiveThread);
    WSACleanup();
    cout << "END LINKING..." << endl;


}

client::~client()
{
    delete ui;
}

DWORD WINAPI SendMessageThread(LPVOID IpParameter)
{
    int first_avoid = 0;
    while (1)
    {

        string send_buf;
        getline(cin, send_buf);

        WaitForSingleObject(bufferMutex, INFINITE);

        //-------------use quit to quit--------------//
        if (send_buf == "quit")//TO SOLVE SERVER SHUTDOWN AND TO SLOVE CLIENT QUIT TO QUIT
        {
            if (connect_button == 1)
            {

                quit_wait = 1;
                connect_button = 2;
                WSACleanup();
                ReleaseSemaphore(bufferMutex, 1, NULL);
                break;
            }
            send_buf.push_back('\0');
            send(sockSrv, send_buf.c_str(), 200, 0);
            ReleaseSemaphore(bufferMutex, 1, NULL);
            while (quit_wait);//wait the result
            WaitForSingleObject(bufferMutex, INFINITE);
            if (quit_button == 2)//2 means want to quit
            {

                quit_wait = 1;
                connect_button = 2;
                ReleaseSemaphore(bufferMutex, 1, NULL);
                break;
            }
            else
            {

                quit_wait = 1;
                quit_button = 0;
            }

        }
        else if (connect_button == 1)
        {

            WSACleanup();
            ReleaseSemaphore(bufferMutex, 1, NULL);

            break;
        }
        else
        {
            //---------------send thread-----------------------//
            //send_buf.push_back('\0');

            string send_buf1 = "CLIENT UID ";
            string send_buf2 = " send: ";
            string uid_begin = "<uidnum>";
            string uid_end = "</uidnu>";
            string header_begin = "<header>";
            string header_end = "</heade>";
            string message_begin = "<messag>";
            string message;
            string message_end = "</messa>";
            string header_num = "255";
            char temp_char[5];
            sprintf(temp_char, "%d", uid_number);
            string uid_num(temp_char);
            string sender;

            //find the different value

            //----------------------figure out----------------------------//
            if (send_buf == "0")//registe
            {
                header_num = "0";
                message = "I WANT TO REGISTER";

                //append all the info
                sender = send_buf1;
                sender.append(uid_num);
                sender.append(send_buf2);
                sender.append(header_begin);
                sender.append(header_num);
                sender.append(header_end);
                sender.append(uid_begin);
                sender.append(uid_num);
                sender.append(uid_end);
                sender.append(message_begin);
                sender.append(message);
                sender.append(message_end);
                //send
                //cout << endl << sender << endl;
                send(sockSrv, sender.c_str(), 200, 0);
                cout << send_buf1 << uid_num << send_buf2 << message << endl;


            }
            else if (send_buf == "1")//see all bid
            {
                header_num = "1";
                message = "I WANT TO SEE ALL BID";

                //append all the info
                sender = send_buf1;
                sender.append(uid_num);
                sender.append(send_buf2);
                sender.append(header_begin);
                sender.append(header_num);
                sender.append(header_end);
                sender.append(uid_begin);
                sender.append(uid_num);
                sender.append(uid_end);
                sender.append(message_begin);
                sender.append(message);
                sender.append(message_end);
                //send
                //cout << endl << sender << endl;
                send(sockSrv, sender.c_str(), 200, 0);
                cout << send_buf1 << uid_num << send_buf2 << message << endl;
            }
            else if (send_buf == "2")//submit an item
            {
                header_num = "2";
                message = "I WANT TO SUBMIT AN ITEM";

                cout << "PLEASE WRITE THE ITEM'S NAME" << endl;//let client write the item name
                ReleaseSemaphore(bufferMutex, 1, NULL);//cause client will write name so release first
                string item_name;
                getline(cin, item_name);//get the item name
                WaitForSingleObject(bufferMutex, INFINITE);//after the get name also get the semaphore
                string itemname_begin = "<itenam>";
                string itemname_end = "</itena>";
                //append all the info
                sender = send_buf1;
                sender.append(uid_num);
                sender.append(send_buf2);
                sender.append(header_begin);
                sender.append(header_num);
                sender.append(header_end);
                sender.append(uid_begin);
                sender.append(uid_num);
                sender.append(uid_end);
                sender.append(message_begin);
                sender.append(message);
                sender.append(message_end);
                sender.append(itemname_begin);
                sender.append(item_name);
                sender.append(itemname_end);
                //send
                //cout << endl << sender << endl;
                send(sockSrv, sender.c_str(), 200, 0);
                cout << send_buf1 << uid_num << send_buf2 << message << " NAME IS " << item_name << endl;

            }
            else if (send_buf == "3")//bid an item
            {
            label_bidagain:
                header_num = "3";
                message = "I WANT TO BID AN ITEM";

                cout << "PLEASE WRITE THE ITEM'S ITEMCODE" << endl;//let client write the item name
                cout << "OR IF YOU WANT TO SEE ALL BID PRESS 1 " << endl;//see all bid
                cout << "OR IF YOU WANT TO BID LATER PRESS 0 " << endl;//see all bid
                ReleaseSemaphore(bufferMutex, 1, NULL);//cause client will write name so release first
                string bid_choice;
                getline(cin, bid_choice);//get the item choice
                WaitForSingleObject(bufferMutex, INFINITE);//after the get name also get the semaphore
                if (bid_choice == "1")//ask all bid
                {
                    header_num = "1";
                    message = "I WANT TO SEE ALL BID";

                    //append all the info
                    sender = send_buf1;
                    sender.append(uid_num);
                    sender.append(send_buf2);
                    sender.append(header_begin);
                    sender.append(header_num);
                    sender.append(header_end);
                    sender.append(uid_begin);
                    sender.append(uid_num);
                    sender.append(uid_end);
                    sender.append(message_begin);
                    sender.append(message);
                    sender.append(message_end);
                    //send
                    //cout << endl << sender << endl;
                    send(sockSrv, sender.c_str(), 200, 0);
                    header_num = "3";
                    ReleaseSemaphore(bufferMutex, 1, NULL);//cause client will write name so release first
                    Sleep(500);
                    WaitForSingleObject(bufferMutex, INFINITE);//after the get name also get the semaphore
                    goto label_bidagain;
                }
                else if (bid_choice == "0")//not want to bid
                {
                    header_num = "255";
                    message = "I WANT TO BID LATER";

                    //append all the info
                    sender = send_buf1;
                    sender.append(uid_num);
                    sender.append(send_buf2);
                    sender.append(header_begin);
                    sender.append(header_num);
                    sender.append(header_end);
                    sender.append(uid_begin);
                    sender.append(uid_num);
                    sender.append(uid_end);
                    sender.append(message_begin);
                    sender.append(message);
                    sender.append(message_end);
                    //send
                    //cout << endl << sender << endl;
                    send(sockSrv, sender.c_str(), 200, 0);
                    cout << endl << "BID LATER" << endl;
                }
                else if ((atoi(bid_choice.c_str()) >= 0) && (atoi(bid_choice.c_str()) <= 255))//bid
                {
                    cout << "INPUT THE PRICE YOU WANT, UP THAN 0 PLEASE" << endl;//see all bid
                    cout << "OR IF YOU WANT TO BID LATER PRESS 0 " << endl;//see all bid
                    ReleaseSemaphore(bufferMutex, 1, NULL);//cause client will write name so release first
                    string price_choice;
                    getline(cin, price_choice);//get the item choice
                    WaitForSingleObject(bufferMutex, INFINITE);//after the get name also get the semaphore
                    if (price_choice == "0")//not want to bid
                    {
                        header_num = "255";
                        message = "I WANT TO BID LATER";

                        //append all the info
                        sender = send_buf1;
                        sender.append(uid_num);
                        sender.append(send_buf2);
                        sender.append(header_begin);
                        sender.append(header_num);
                        sender.append(header_end);
                        sender.append(uid_begin);
                        sender.append(uid_num);
                        sender.append(uid_end);
                        sender.append(message_begin);
                        sender.append(message);
                        sender.append(message_end);
                        //send
                        //cout << endl << sender << endl;
                        send(sockSrv, sender.c_str(), 200, 0);
                        cout << endl << "BID LATER" << endl;
                    }
                    else if (atoi(price_choice.c_str()) > 0)//normal price
                    {
                        string itemcode_begin = "<itecod>";
                        string itemcode_end = "</iteco>";
                        string itemprice_begin = "<itepri>";
                        string itemprice_end = "</itepr>";
                        //append all the info
                        sender = send_buf1;
                        sender.append(uid_num);
                        sender.append(send_buf2);
                        sender.append(header_begin);
                        sender.append(header_num);
                        sender.append(header_end);
                        sender.append(uid_begin);
                        sender.append(uid_num);
                        sender.append(uid_end);
                        sender.append(message_begin);
                        sender.append(message);
                        sender.append(message_end);
                        sender.append(itemcode_begin);
                        sender.append(bid_choice);
                        sender.append(itemcode_end);
                        sender.append(itemprice_begin);
                        sender.append(price_choice);
                        sender.append(itemprice_end);
                        //send
                        //cout << endl << sender << endl;
                        send(sockSrv, sender.c_str(), 200, 0);
                        //cout << send_buf1 << uid_num << send_buf2 << message << " NAME IS " << item_name << endl;
                    }
                    else//another error input
                    {
                        cout << endl << "some problem accur1" << endl;
                    }

                }
                else//another error input
                {
                    cout << endl << "some problem accur2" << endl;
                }

            }
            else if (send_buf == "4")//see client's bid
            {
                header_num = "4";
                message = "I WANT TO SEE ALL MY BID";

                //append all the info
                sender = send_buf1;
                sender.append(uid_num);
                sender.append(send_buf2);
                sender.append(header_begin);
                sender.append(header_num);
                sender.append(header_end);
                sender.append(uid_begin);
                sender.append(uid_num);
                sender.append(uid_end);
                sender.append(message_begin);
                sender.append(message);
                sender.append(message_end);
                //send
                //cout << endl << sender << endl;
                send(sockSrv, sender.c_str(), 200, 0);
                cout << send_buf1 << uid_num << send_buf2 << message << endl;
            }
            else if (send_buf == "5")//see all the item sale
            {
                header_num = "5";
                message = "I WANT TO SEE ALL MY SALE";

                //append all the info
                sender = send_buf1;
                sender.append(uid_num);
                sender.append(send_buf2);
                sender.append(header_begin);
                sender.append(header_num);
                sender.append(header_end);
                sender.append(uid_begin);
                sender.append(uid_num);
                sender.append(uid_end);
                sender.append(message_begin);
                sender.append(message);
                sender.append(message_end);
                //send
                //cout << endl << sender << endl;
                send(sockSrv, sender.c_str(), 200, 0);
                cout << send_buf1 << uid_num << send_buf2 << message << endl;
            }
            else if (send_buf == "6")//try to deregister
            {
                header_num = "6";
                message = "I WANT TO DEREGISTER";

                //append all the info
                sender = send_buf1;
                sender.append(uid_num);
                sender.append(send_buf2);
                sender.append(header_begin);
                sender.append(header_num);
                sender.append(header_end);
                sender.append(uid_begin);
                sender.append(uid_num);
                sender.append(uid_end);
                sender.append(message_begin);
                sender.append(message);
                sender.append(message_end);
                //send
                //cout << endl << sender << endl;
                send(sockSrv, sender.c_str(), 200, 0);
                cout << send_buf1 << uid_num << send_buf2 << message << endl;
            }
            else if (send_buf == "7")//try to withdraw the item
            {
            label_withdrawagain:
                header_num = "7";
                message = "I WANT TO WITHDRAW MY ITEM";

                cout << "PLEASE WRITE THE ITEM'S ITEMCODE" << endl;//let client write the item name
                cout << "OR IF YOU WANT TO SEE ALL YOUR ITEM PRESS 1 " << endl;//see all bid
                cout << "OR IF YOU WANT TO WITHDRAW LATER PRESS 0 " << endl;//see all bid
                ReleaseSemaphore(bufferMutex, 1, NULL);//cause client will write name so release first
                string bid_choice;
                getline(cin, bid_choice);//get the item choice
                WaitForSingleObject(bufferMutex, INFINITE);//after the get name also get the semaphore
                if (bid_choice == "1")//ask all item
                {
                    header_num = "5";
                    message = "I WANT TO SEE ALL MY SALE";

                    //append all the info
                    sender = send_buf1;
                    sender.append(uid_num);
                    sender.append(send_buf2);
                    sender.append(header_begin);
                    sender.append(header_num);
                    sender.append(header_end);
                    sender.append(uid_begin);
                    sender.append(uid_num);
                    sender.append(uid_end);
                    sender.append(message_begin);
                    sender.append(message);
                    sender.append(message_end);
                    //send
                    //cout << endl << sender << endl;
                    send(sockSrv, sender.c_str(), 200, 0);
                    header_num = "7";
                    ReleaseSemaphore(bufferMutex, 1, NULL);//cause client will write name so release first
                    Sleep(500);
                    WaitForSingleObject(bufferMutex, INFINITE);//after the get name also get the semaphore
                    goto label_withdrawagain;
                }
                else if (bid_choice == "0")//not want to bid
                {
                    header_num = "255";
                    message = "I WANT TO WITHDRAW LATER";

                    //append all the info
                    sender = send_buf1;
                    sender.append(uid_num);
                    sender.append(send_buf2);
                    sender.append(header_begin);
                    sender.append(header_num);
                    sender.append(header_end);
                    sender.append(uid_begin);
                    sender.append(uid_num);
                    sender.append(uid_end);
                    sender.append(message_begin);
                    sender.append(message);
                    sender.append(message_end);
                    //send
                    //cout << endl << sender << endl;
                    send(sockSrv, sender.c_str(), 200, 0);
                    cout << endl << "WITHDRAW LATER" << endl;
                }
                else if ((atoi(bid_choice.c_str()) >= 0) && (atoi(bid_choice.c_str()) <= 255))//item
                {
                    string itemcode_begin = "<itecod>";
                    string itemcode_end = "</iteco>";
                    //append all the info
                    sender = send_buf1;
                    sender.append(uid_num);
                    sender.append(send_buf2);
                    sender.append(header_begin);
                    sender.append(header_num);
                    sender.append(header_end);
                    sender.append(uid_begin);
                    sender.append(uid_num);
                    sender.append(uid_end);
                    sender.append(message_begin);
                    sender.append(message);
                    sender.append(message_end);
                    sender.append(itemcode_begin);
                    sender.append(bid_choice);
                    sender.append(itemcode_end);
                    //send
                    //cout << endl << sender << endl;
                    send(sockSrv, sender.c_str(), 200, 0);
                }
                else//another error input
                {
                    cout << endl << "some problem accur3" << endl;
                }

            }
            else if (send_buf == "8")//clean the screen
            {
                system("cls");
                cout << first_show << endl;
                cout << chioce << endl;
                cout << "CLIENT SEND:" << endl;
            }
            else
            {
                header_num = "255";
                if (first_avoid == 0)
                {
                    first_avoid = 1;
                }
                else
                {
                    cout << endl << "some problem accur4" << endl;
                    cout << send_buf << endl;
                }

            }

            //----------------------figure out----------------------------//
        }
        ReleaseSemaphore(bufferMutex, 1, NULL);

    }
    return 0;
}

DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter)
{
    while (1)
    {
        char recv_buf[200];
        //receive
        rev = recv(sockSrv, recv_buf, 200, 0);

        WaitForSingleObject(bufferMutex, INFINITE);

        if (connect_button == 2)//TO SOLVE CLIENT WRITE QUIT TO QUIT
        {
            ReleaseSemaphore(bufferMutex, 1, NULL);
            break;
        }
        //find error
        if (rev == SOCKET_ERROR)//TO SOLVE SERVER SHUTDOWN ERROR
        {
            cout << endl << "RECEIVE ERROR" << endl;
            cout << endl << "ENTER quit to quit or any other word to try again" << endl;

            connect_button = 1;
            WSACleanup();
            ReleaseSemaphore(bufferMutex, 1, NULL);
            break;
        }
        //------------------------------FIGURE OUT PART-------------------------------------------------//
        //------------------------------FIGURE OUT PART-------------------------------------------------//
        //------------------------------FIGURE OUT PART-------------------------------------------------//

        else if (recv_buf[0] == 'q' && recv_buf[1] == 'u' && recv_buf[2] == 'i' &&//TO SOLVE SERVER QUIT ERROR
            recv_buf[3] == 't' && recv_buf[4] == '\0')
        {

            cout << endl << "ATTENTION: SERVER HAS LEAVED..." << endl;
            cout << endl << "ENTER quit to quit or any other word to try again" << endl;
            WSACleanup();
            connect_button = 1;
            ReleaseSemaphore(bufferMutex, 1, NULL);

            break;
        }

        else if (recv_buf[0] == '1' && recv_buf[1] == '-')
        {
            quit_wait = 0;//reduce the wait
            quit_button = 1;//1 means not quit
            cout << endl << recv_buf + 2 << endl;
        }
        //get uid
        else if (recv_buf[0] == '0' && recv_buf[1] == '-')
        {
            string recv_str;//turn char to string
            string newer01;//get two part of string
            string newer02;//get two part of string
            recv_str = recv_buf;//change model
            size_t found_header;//header position
            size_t found_tag;//tag position
            found_header = recv_str.find("0-");//get the header
            found_tag = recv_str.find("<uidnum>");//get the tag
            newer01 = recv_str.substr(found_header + 2, found_tag - found_header - 2);//get the first string
            newer02 = recv_str.substr(found_tag + 8, sizeof(recv_str) - found_tag - 8);//get the second string
            int uid_get = atoi(newer02.c_str());//change number to int
            uid_number = uid_get;//save the uid number
            newer01.append(newer02);//put first and second together
            cout << endl << newer01 << endl;//show

        }
        else if (recv_buf[0] == '2' && recv_buf[1] == '-'&& recv_buf[2] == '8'&&
            recv_buf[3] == '8'&& recv_buf[4] == '8'&& recv_buf[5] == '8')
        {
            quit_wait = 0;//reduce the wait
            quit_button = 2;//2 means  quit

            ReleaseSemaphore(bufferMutex, 1, NULL);
            break;
        }
        //------------------------------FIGURE OUT PART-------------------------------------------------//
        //------------------------------FIGURE OUT PART-------------------------------------------------//
        //------------------------------FIGURE OUT PART-------------------------------------------------//
        else
        {
            cout << endl << recv_buf << endl;
        }
        ReleaseSemaphore(bufferMutex, 1, NULL);
    }
    return 0;
}
