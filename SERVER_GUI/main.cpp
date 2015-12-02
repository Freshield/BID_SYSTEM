#include "server.h"
#include <QApplication>
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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SERVER w;
    w.show();

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
            //--------------server socket init--------------------------//

                //make socket
                sockSrv = socket(AF_INET, SOCK_STREAM, 0);//make server socket
                SOCKADDR_IN addrSrv;
                addrSrv.sin_addr.S_un.S_addr = htons(INADDR_ANY);//any IP is ok
                addrSrv.sin_family = AF_INET;//TCP
                string port_number = "2333";
                int port = atoi(port_number.c_str());
                addrSrv.sin_port = htons(port);//port use htons transfer X86 number to IP number

            ui->label->setText("SOCKET INIT finished");
            //bind
                int bind_rev = bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv));
                //find error
                if (bind_rev == SOCKET_ERROR)
                {
                    ui->label->setText("bind error");

                }

                //listen
                listen(sockSrv, 5);
                ui->label->setText("-----------SERVER INIT FINISHED------------");
                //-----------------thread----------------------------//

                    //declare
                    bufferMutex = CreateSemaphore(NULL, 1, 1, NULL);
                    DWORD WINAPI SendMessageThread(LPVOID IpParameter);

                    DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);

                    ui->label->setText("sendThread init finished");


                    HANDLE sendThread = CreateThread(NULL, 0, SendMessageThread, NULL, 0, NULL);//make send thread
                    while (1)
                        {

                            //accept
                            sockClient = accept(sockSrv, NULL, NULL);//PROBLEM if NULL is ok?

                            HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread, (LPVOID)sockClient, 0, NULL);

                            WaitForSingleObject(bufferMutex, INFINITE);

                            //------------------use quit to quit------------------------//
                            if (button == 1)//TO SOLVE SERVER WRITE QUIT TO QUIT ERROR
                            {
                                ReleaseSemaphore(bufferMutex, 1, NULL);

                                break;
                            }
                            //----------------------------------------------//
                            //puch to socket poll
                            if (sockClient != SOCKET_ERROR)
                            {
                                clientSocketGroup.push_back(sockClient);//can do other vector here to identify the client
                                UID uid_buf;
                                uid_buf.number = uid_number;
                                uid_number++;
                                uid_buf.sockets_value = sockClient;
                                uid.push_back(uid_buf);
                                char test_char[5];
                                string temp = "0-YOUR UID NUMBER IS:<uidnum>";
                                sprintf(test_char, "%d", uid_buf.number);
                                string temp1(test_char);
                                temp.append(temp1);
                                send(sockClient, temp.c_str(), 200, 0);
                                client_count++;

                                //ui->label->setText("UID:"+temp1+"CLIENT CONNECT");

                            }

                            //make receive thread



                            if (receiveThread == NULL)
                            {
                                cout << "CreateThread AnswerThread failed" << endl;
                            }
                            //else
                            //{
                            //	cout << endl << "Create Receive Client Thread OK" << endl;
                            //}
                            ReleaseSemaphore(bufferMutex, 1, NULL);
                        }

                        //----------------finished-----------------------------//

                        WaitForSingleObject(sendThread, INFINITE);

                        CloseHandle(sendThread);
                        CloseHandle(bufferMutex);

                        WSACleanup();
                        cout << "SEE YOU" << endl;

                        //------------------error part---------------------------//




    return a.exec();
}

//-----------------------------------------------------------------------------------------//
DWORD WINAPI SendMessageThread(LPVOID IpParameter)
{

    while (1)
    {

        string send_buf;//set buffer

        string temp = "SERVER SEND:";
        if (client_count == 0)
        {
            cout << endl << "NO CLIENT NOW" << endl;
        }
        getline(cin, send_buf);//get cin
        WaitForSingleObject(bufferMutex, INFINITE);
        cout << endl;
        //------------------use quit to quit----------------------------//
        if (send_buf == "quit")//TO SOLVE SERVER WRITE QUIT TO QUIT ERROR
        {
            send_buf.push_back('\0');

            for (size_t i = 0; i < clientSocketGroup.size(); i++)
            {
                send(clientSocketGroup[i], send_buf.c_str(), 200, 0);
            }
            button = 1;
            closesocket(sockSrv);

            ReleaseSemaphore(bufferMutex, 1, NULL);

            break;//can send some info here
        }
        //-------------------------------------------------//
        for (size_t i = 0; i < clientSocketGroup.size(); i++)
        {
            //sprintf(test_char, "SERVER SEND:%.200s", sizeof(send_buf),send_buf);
            int uidnum_buf;
            temp.append(send_buf);
            send(clientSocketGroup[i], temp.c_str(), 200, 0);
            temp = "SERVER SEND:";
            for (size_t j = 0; j < uid.size(); j++)
            {
                SOCKET registed_buf = uid[j].sockets_value;
                if (registed_buf == clientSocketGroup[i])
                {
                    uidnum_buf = uid[i].number;
                    cout << "SENT TO UID " << uidnum_buf << " CLIENT SUCCESS" << endl;

                }
            }
        }
        ReleaseSemaphore(bufferMutex, 1, NULL);

    }
    return 0;
}

//----------------------------------------------------------------------------------------//

DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter)
{
    SOCKET ClientSocket = (SOCKET)(LPVOID)IpParameter;//received socket
    while (1)
    {
        if (button == 1)//TO SOLVE SERVER WRITE QUIT TO QUIT ERROR
        {
            break;
        }

        char recv_buf[200];
        //receive

        rev = recv(ClientSocket, recv_buf, 200, 0);//received data

        WaitForSingleObject(bufferMutex, INFINITE);

        if (button == 1)//TO SOLVE SERVER WRITE QUIT TO QUIT ERROR
        {
            ReleaseSemaphore(bufferMutex, 1, NULL);

            break;
        }

        //find error
        if (rev == SOCKET_ERROR)//TO SLOVE CLINET SHUTDOWN ERROR
        {
            cout << endl << "RECEIVE ERROR" << endl;

            //release this client
            vector<SOCKET>::iterator result = find(clientSocketGroup.begin(),
                clientSocketGroup.end(), ClientSocket);
            clientSocketGroup.erase(result);
            int num_uid_buf;
            for (size_t i = 0; i < uid.size(); i++)
            {
                SOCKET erase_buf = uid[i].sockets_value;
                if (erase_buf == ClientSocket)
                {
                    num_uid_buf = uid[i].number;
                    uid.erase(uid.begin() + i);
                }
            }
            cout << endl << "ATTENTION: UID " << num_uid_buf << " CLIENT HAS LEAVED..." << endl;

            client_count--;
            closesocket(ClientSocket);
            //find all this client bid and item
            //find the client's uid

            char uidnum_char[5];
            sprintf(uidnum_char, "%d", num_uid_buf);
            string client_uidnum(uidnum_char);
            //for item
            int owneritem = 0;
            for (size_t i = 0; i < item.size(); i++)
            {
                if (item[i].owner == client_uidnum && item[i].show == 0)//to avoid client withdraw
                {
                    owneritem++;
                }
            }
            //find the buyer num
            int buyeritem = 0;
            for (size_t i = 0; i < item.size(); i++)
            {
                if (item[i].buyer == client_uidnum && item[i].show == 0)//to avoid client withdraw
                {
                    buyeritem++;
                }
            }
            //figure out
            if (owneritem != 0)//have some item
            {
                //inform all client
                string allclientinfo = "SERVER SEND: UID ";
                allclientinfo.append(client_uidnum);
                allclientinfo.append(" CLIENT WAS GONE, THE ITEM BLOW CANCELLED");
                for (size_t i = 0; i < clientSocketGroup.size(); i++)
                {
                    send(clientSocketGroup[i], allclientinfo.c_str(), 200, 0);
                }
                cout << allclientinfo << endl;
                //when find an item owner is this uid
                for (size_t i = 0; i < item.size(); i++)
                {
                    if (item[i].owner == client_uidnum && item[i].show == 0)//to avoid client withdraw
                    {
                        item[i].show = 1;//withdraw the item first

                        char item_buf[5];
                        sprintf(item_buf, "%d", i);
                        string item_vector(item_buf);
                        allclientinfo.append(item_vector);
                        string forbuyer = "ITEM ";
                        forbuyer.append(item_vector);
                        forbuyer.append(" CANCELLED\n");
                        string namebuf = "NAME: ";
                        string pricebuf = "PRICE: ";
                        string ownerbuf = "OWNER: ";
                        string buyerbuf = "BUYER: ";
                        string codebuf = "ITEM CODE: ";
                        string endbuf = " \n";
                        string bidname = item[i].name;
                        string bidprice = item[i].price;
                        string bidowner = item[i].owner;
                        string bidbuyer = item[i].buyer;
                        char bid_char[5];
                        sprintf(bid_char, "%d", item[i].itemcode);
                        string bidcode(bid_char);
                        //for buyer
                        forbuyer.append(namebuf);
                        forbuyer.append(bidname);
                        forbuyer.append(endbuf);
                        forbuyer.append(pricebuf);
                        forbuyer.append(bidprice);
                        forbuyer.append(endbuf);
                        forbuyer.append(ownerbuf);
                        forbuyer.append(bidowner);
                        forbuyer.append(endbuf);
                        forbuyer.append(buyerbuf);
                        forbuyer.append(bidbuyer);
                        forbuyer.append(endbuf);
                        forbuyer.append(codebuf);
                        forbuyer.append(bidcode);
                        forbuyer.append(endbuf);
                        //send all client
                        for (size_t i = 0; i < clientSocketGroup.size(); i++)
                        {
                            send(clientSocketGroup[i], forbuyer.c_str(), 200, 0);
                        }
                        cout << forbuyer << endl;
                    }
                }
            }
            if (buyeritem != 0)//have some bid
            {
                //inform all client
                string allclientinfo = "SERVER SEND: UID ";
                allclientinfo.append(client_uidnum);
                allclientinfo.append(" CLIENT WAS GONE, THE ITEM BID BLOW CANCELLED, BUT ITEM SAVED");
                for (size_t i = 0; i < clientSocketGroup.size(); i++)
                {
                    send(clientSocketGroup[i], allclientinfo.c_str(), 200, 0);
                }
                cout << allclientinfo << endl;
                //when find an item owner is this uid
                for (size_t i = 0; i < item.size(); i++)
                {
                    if (item[i].buyer == client_uidnum && item[i].show == 0)//to avoid client withdraw
                    {
                        //change the price and buyer
                        item[i].price = "NULL";
                        item[i].buyer = "NULL";
                        //inform
                        char item_buf[5];
                        sprintf(item_buf, "%d", i);
                        string item_vector(item_buf);
                        allclientinfo.append(item_vector);
                        string forbuyer = "ITEM ";
                        forbuyer.append(item_vector);
                        forbuyer.append(" BID CANCELLED\n");
                        string namebuf = "NAME: ";
                        string pricebuf = "PRICE: ";
                        string ownerbuf = "OWNER: ";
                        string buyerbuf = "BUYER: ";
                        string codebuf = "ITEM CODE: ";
                        string endbuf = " \n";
                        string bidname = item[i].name;
                        string bidprice = item[i].price;
                        string bidowner = item[i].owner;
                        string bidbuyer = item[i].buyer;
                        char bid_char[5];
                        sprintf(bid_char, "%d", item[i].itemcode);
                        string bidcode(bid_char);
                        //for buyer
                        forbuyer.append(namebuf);
                        forbuyer.append(bidname);
                        forbuyer.append(endbuf);
                        forbuyer.append(pricebuf);
                        forbuyer.append(bidprice);
                        forbuyer.append(endbuf);
                        forbuyer.append(ownerbuf);
                        forbuyer.append(bidowner);
                        forbuyer.append(endbuf);
                        forbuyer.append(buyerbuf);
                        forbuyer.append(bidbuyer);
                        forbuyer.append(endbuf);
                        forbuyer.append(codebuf);
                        forbuyer.append(bidcode);
                        forbuyer.append(endbuf);
                        //send all client
                        for (size_t i = 0; i < clientSocketGroup.size(); i++)
                        {
                            send(clientSocketGroup[i], forbuyer.c_str(), 200, 0);
                        }
                        cout << forbuyer << endl;
                    }
                }
            }


            ReleaseSemaphore(bufferMutex, 1, NULL);

            if (client_count == 0)
            {
                cout << endl << "NO CLIENT NOW" << endl;
            }

            break;
        }

        //find quit
        if (recv_buf[0] == 'q' && recv_buf[1] == 'u' && recv_buf[2] == 'i' &&
            recv_buf[3] == 't' && recv_buf[4] == '\0')
        {

            //find item uid num
            int num_uid_buf;
            for (size_t i = 0; i < uid.size(); i++)
            {
                SOCKET erase_buf = uid[i].sockets_value;
                if (erase_buf == ClientSocket)
                {
                    num_uid_buf = i;
                }
            }

            //figure out
            if (uid[num_uid_buf].registed == 1)//not deregisted yet
            {
                send(ClientSocket, "1-SERVER SEND: YOUR QUIT FAILED, CAUSE YOU ARE NOT DEREGISTED", 200, 0);
                cout << endl << "UID " << uid[num_uid_buf].number << " CLIENT QUIT FAILED, CAUSE NOT DEREGISTED" << endl;

            }
            else//normal quit
            {
                send(ClientSocket, "2-8888", 200, 0);
                vector<SOCKET>::iterator result = find(clientSocketGroup.begin(),
                    clientSocketGroup.end(), ClientSocket);
                clientSocketGroup.erase(result);
                //find item in vector uid
                int num_uid_buf;
                for (size_t i = 0; i < uid.size(); i++)
                {
                    SOCKET erase_buf = uid[i].sockets_value;
                    if (erase_buf == ClientSocket)
                    {
                        num_uid_buf = uid[i].number;
                        uid.erase(uid.begin() + i);
                    }
                }
                client_count--;
                closesocket(ClientSocket);


                ReleaseSemaphore(bufferMutex, 1, NULL);

                cout << endl << "ATTENTION: UID " << num_uid_buf << " CLIENT HAS LEAVED..." << endl;
                if (client_count == 0)
                {
                    cout << endl << "NO CLIENT NOW" << endl;
                }
                break;
            }


        }
        else if (recv_buf[0] == 'C' && recv_buf[1] == 'L' && recv_buf[2] == 'I' &&
            recv_buf[3] == 'E' && recv_buf[4] == 'N' && recv_buf[5] == 'T')
        {

//------------------------------FIGURE OUT PART-------------------------------------------------//
//------------------------------FIGURE OUT PART-------------------------------------------------//
//------------------------------FIGURE OUT PART-------------------------------------------------//
            string recv_str;//turn char to string
            string first_part;//the first part
            string header_part;//header
            string uidnum_part;//uid
            string message_part;//message
            string itemname_part;//item name
            string itemcode_part;//item code
            string itemprice_part;//item price
            string reader;
            recv_str = recv_buf;//change model
            size_t found_header_begin;//header position
            size_t found_header_end;//header position
            size_t found_uidnum_begin;//uid position
            size_t found_uidnum_end;//uid position
            size_t found_message_begin;//message position
            size_t found_message_end;//message position
            size_t found_itemname_begin;//item name position
            size_t found_itemname_end;//item name position
            size_t found_itemcode_begin;//item name position
            size_t found_itemcode_end;//item name position
            size_t found_itemprice_begin;//item name position
            size_t found_itemprice_end;//item name position
                                     //found
            found_header_begin = recv_str.find("<header>");//get the header
            found_header_end = recv_str.find("</heade>");//get the header
            found_uidnum_begin = recv_str.find("<uidnum>");//get the uid
            found_uidnum_end = recv_str.find("</uidnu>");//get the uid
            found_message_begin = recv_str.find("<messag>");//get the message
            found_message_end = recv_str.find("</messa>");//get the message
            first_part = recv_str.substr(0, found_header_begin);//first
            header_part = recv_str.substr(found_header_begin + 8, found_header_end - found_header_begin - 8);//header
            uidnum_part = recv_str.substr(found_uidnum_begin + 8, found_uidnum_end - found_uidnum_begin - 8);//uidnum
            message_part = recv_str.substr(found_message_begin + 8, found_message_end - found_message_begin - 8);//message

                                                          //put together
            reader = first_part;
            reader.append(message_part);
            cout << endl << reader << endl;//show
//----------------------------------switch-----------------------------------------------------//
//----------------------------------switch-----------------------------------------------------//
//----------------------------------switch-----------------------------------------------------//
            if (header_part == "0")//0 is to registe
            {
                //-----------find client--------------//
                int vector_num = 255;
                for (size_t i = 0; i < uid.size(); i++)
                {
                    SOCKET registed_buf = uid[i].sockets_value;
                    if (registed_buf == ClientSocket)
                    {vector_num = i;}
                }
                if (vector_num == 255)
                {
                    cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
                    send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
                }
                else
                {
                    if (uid[vector_num].registed == 0)
                    {

                        uid[vector_num].registed = 1;
                        cout << endl << "UID " << uidnum_part << " CLIENT REGISTED SUCCESS" << endl;
                        send(ClientSocket, "SERVER SEND:YOUR REGISTED SUCCESS", 200, 0);
                    }
                    else
                    {
                        //-------------------------TODO-------------------------------------//
                        cout << endl << "UID " << uidnum_part << " CLIENT HAS BEEN REGISTED" << endl;
                        send(ClientSocket, "SERVER SEND:YOU WERE REGISTED,DO NOT REGISTED AGAIN,PLEASE", 200, 0);
                    }
                }

            }
            else if (header_part == "1")//1 is SEE THE BID NOW
            {
                //-----------find client--------------//
                int vector_num = 255;
                for (size_t i = 0; i < uid.size(); i++)
                {
                    SOCKET registed_buf = uid[i].sockets_value;
                    if (registed_buf == ClientSocket)
                    {
                        vector_num = i;
                    }
                }
                if (vector_num == 255)
                {
                    cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
                    send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
                }
                else
                {
                    if (uid[vector_num].registed == 0)
                    {
                        cout << endl << "UID " << uidnum_part << " CLIENT NOT REGISTED YET" << endl;
                        send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
                    }
                    else
                    {
                        //-------------------------TODO-------------------------------------//
                        if (item_vector_num == 0)//if no item now
                        {
                            send(ClientSocket, "SERVER SEND:THERE ARE NO ITEM NOW", 200, 0);
                            cout << endl << "UID " << uidnum_part << " ASK ALL BID BUT NO ITEM NOW" << endl;
                        }
                        else
                        {
                            send(ClientSocket, "SERVER SEND: ALL ITEM ARE HERE", 200, 0);
                            for (size_t i = 0; i < item.size(); i++)
                            {
                                if (item[i].show == 0)//to avoid the client withdraw item
                                {
                                    char middle_use[5];
                                    string send_item_buf1 = "ITEM ";//first part
                                    sprintf(middle_use, "%d", i);
                                    string item_number1(middle_use);//number part
                                    send_item_buf1.append(item_number1);
                                    string send_item_buf2 = " :NAME IS ";
                                    send_item_buf1.append(send_item_buf2);//name part
                                    send_item_buf1.append(item[i].name);
                                    send_item_buf2 = " PRICE IS ";
                                    send_item_buf1.append(send_item_buf2);//price part
                                    send_item_buf1.append(item[i].price);
                                    send_item_buf2 = " OWNER IS UID";
                                    send_item_buf1.append(send_item_buf2);//owner part
                                    send_item_buf1.append(item[i].owner);
                                    send_item_buf2 = " BUYER IS UID";
                                    send_item_buf1.append(send_item_buf2);//buyer part
                                    send_item_buf1.append(item[i].buyer);
                                    send_item_buf2 = " ITEM CODE IS ";//code part
                                    send_item_buf1.append(send_item_buf2);//code part
                                    sprintf(middle_use, "%d", item[i].itemcode);
                                    string item_codebuf(middle_use);//code part
                                    send_item_buf1.append(item_codebuf);
                                    send_item_buf1.append(" ;");
                                    send(ClientSocket, send_item_buf1.c_str(), 200, 0);//send it
                                }

                            }
                            cout << endl << "UID " << uidnum_part << " ASK ALL BID" << endl;
                        }


                    }
                }//HERE
            }
            else if (header_part == "2")//2 is SUBMITTING AN ITEM
            {
                //-----------find client--------------//
                int vector_num = 255;
                for (size_t i = 0; i < uid.size(); i++)
                {
                    SOCKET registed_buf = uid[i].sockets_value;
                    if (registed_buf == ClientSocket)
                    {
                        vector_num = i;
                    }
                }
                if (vector_num == 255)
                {
                    cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
                    send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
                }
                else
                {
                    if (uid[vector_num].registed == 0)
                    {
                        cout << endl << "UID " << uidnum_part << " CLIENT NOT REGISTED YET" << endl;
                        send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
                    }
                    else
                    {
                        //-------------------------TODO-------------------------------------//
                        //DO NOT FORGET DO THE 5 MINITE THREAD HERE
                        found_itemname_begin = recv_str.find("<itenam>");//get the item name
                        found_itemname_end = recv_str.find("</itena>");//get the item name
                        itemname_part = recv_str.substr(found_itemname_begin + 8, found_itemname_end - found_itemname_begin - 8);//name
                        //save the item
                        ITEM item_buf;
                        item_buf.owner = uidnum_part;//owner's uid
                        item_buf.itemcode = item_number;//item's code
                        item_number++;//do not forget to add the total num
                        item_vector_num++;//do not forget to add the total num
                        item_buf.name = itemname_part;//item's name
                        item.push_back(item_buf);//add to vector item

                        //create 5 minite thread
                        DWORD WINAPI waittimeThread(LPVOID IpParameter);
                        static int item_timebuf;
                        item_timebuf = item_buf.itemcode;
                        HANDLE WaitThread = CreateThread(NULL, 0, waittimeThread, (LPVOID)item_timebuf, 0, NULL);
                        send(ClientSocket, "SERVER SEND:SUBMIT SUCCESS", 200, 0);
                        cout << "UID" << uidnum_part << " CLIENT SUBMIT AN ITEM" << endl;
                        cout << "NAME IS " << itemname_part << endl;
                    }
                }//HERE
            }
            else if (header_part == "3")//3 is BID ONE ITEM
            {
                found_itemcode_begin = recv_str.find("<itecod>");//get the item code
                found_itemcode_end = recv_str.find("</iteco>");//get the item code
                found_itemprice_begin = recv_str.find("<itepri>");//get the item price
                found_itemprice_end = recv_str.find("</itepr>");//get the item price
                itemcode_part = recv_str.substr(found_itemcode_begin + 8, found_itemcode_end - found_itemcode_begin - 8);//code
                itemprice_part = recv_str.substr(found_itemprice_begin + 8, found_itemprice_end - found_itemprice_begin - 8);//price
                //-----------find client--------------//
                int vector_num = 255;
                for (size_t i = 0; i < uid.size(); i++)
                {
                    SOCKET registed_buf = uid[i].sockets_value;
                    if (registed_buf == ClientSocket)
                    {
                        vector_num = i;
                    }
                }
                if (vector_num == 255)
                {
                    cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
                    send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
                }
                else
                {
                    if (uid[vector_num].registed == 0)
                    {
                        cout << endl << "UID " << uidnum_part << " CLIENT NOT REGISTED YET" << endl;
                        send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
                    }
                    else
                    {
                        //-------------------------TODO-------------------------------------//

                        int bidcode = atoi(itemcode_part.c_str());
                        int bidprice = atoi(itemprice_part.c_str());
                        int bidnum = 255;
                        //find the item
                        for (size_t i = 0; i < item.size(); i++)
                        {
                            int codenum_buf = item[i].itemcode;
                            if (codenum_buf == bidcode)
                            {
                                bidnum = i;//item's num in vector
                            }
                        }
                        if (bidnum == 255 || item[bidnum].show == 1)//to avoid client withdraw
                        {
                            cout << endl << "CAN NOT FIND ITEM CODE " << itemcode_part << " ITEM" << endl;
                            send(ClientSocket, "CAN NOT FIND YOUR ITEM WANT TO BID IN VECTOR", 200, 0);
                        }
                        else
                        {
                            //figure out the price
                            //no one was bid
                            if (item[bidnum].price == "NULL")
                            {
                                item[bidnum].price = itemprice_part;
                                item[bidnum].buyer = uidnum_part;

                                //inform all client
                                string forclient = "SERVER SEND:ONE ITEM'S PRICE CHANGED\n";
                                string namebuf = "NAME: ";
                                string pricebuf = "PRICE: ";
                                string ownerbuf = "OWNER: ";
                                string buyerbuf = "BUYER: ";
                                string codebuf = "ITEM CODE: ";
                                string endbuf = " \n";
                                string bidname = item[bidnum].name;
                                string bidprice = item[bidnum].price;
                                string bidowner = item[bidnum].owner;
                                string bidbuyer = item[bidnum].buyer;
                                char bid_char[5];
                                sprintf(bid_char, "%d", item[bidnum].itemcode);
                                string bidcode(bid_char);
                                //for buyer
                                forclient.append(namebuf);
                                forclient.append(bidname);
                                forclient.append(endbuf);
                                forclient.append(pricebuf);
                                forclient.append(bidprice);
                                forclient.append(endbuf);
                                forclient.append(ownerbuf);
                                forclient.append(bidowner);
                                forclient.append(endbuf);
                                forclient.append(buyerbuf);
                                forclient.append(bidbuyer);
                                forclient.append(endbuf);
                                forclient.append(codebuf);
                                forclient.append(bidcode);
                                forclient.append(endbuf);
                                for (size_t i = 0; i < clientSocketGroup.size(); i++)
                                {
                                    send(clientSocketGroup[i], forclient.c_str(), 200, 0);
                                }
                                cout << endl << forclient << endl;

                            }
                            else//price was available
                            {
                                int itemprice_now = atoi(item[bidnum].price.c_str());
                                //figure out
                                //smaller or equal
                                if (bidprice <= itemprice_now)
                                {
                                    send(ClientSocket, "BID FAILED, YOUR PRICE IS LOWER OR EQUAL THE PRICE NOW", 200, 0);
                                    cout << endl << "UID " << uidnum_part << " CLIENT BID FAILED, CAUSE PRICE IS LOW" << endl;
                                }
                                //higher
                                else
                                {
                                    item[bidnum].price = itemprice_part;
                                    item[bidnum].buyer = uidnum_part;

                                    //inform all client
                                    string forclient = "SERVER SEND:ONE ITEM'S PRICE CHANGED\n";
                                    string namebuf = "NAME: ";
                                    string pricebuf = "PRICE: ";
                                    string ownerbuf = "OWNER: ";
                                    string buyerbuf = "BUYER: ";
                                    string codebuf = "ITEM CODE: ";
                                    string endbuf = " \n";
                                    string bidname = item[bidnum].name;
                                    string bidprice = item[bidnum].price;
                                    string bidowner = item[bidnum].owner;
                                    string bidbuyer = item[bidnum].buyer;
                                    char bid_char[5];
                                    sprintf(bid_char, "%d", item[bidnum].itemcode);
                                    string bidcode(bid_char);
                                    //for buyer
                                    forclient.append(namebuf);
                                    forclient.append(bidname);
                                    forclient.append(endbuf);
                                    forclient.append(pricebuf);
                                    forclient.append(bidprice);
                                    forclient.append(endbuf);
                                    forclient.append(ownerbuf);
                                    forclient.append(bidowner);
                                    forclient.append(endbuf);
                                    forclient.append(buyerbuf);
                                    forclient.append(bidbuyer);
                                    forclient.append(endbuf);
                                    forclient.append(codebuf);
                                    forclient.append(bidcode);
                                    forclient.append(endbuf);
                                    for (size_t i = 0; i < clientSocketGroup.size(); i++)
                                    {
                                        send(clientSocketGroup[i], forclient.c_str(), 200, 0);
                                    }
                                    cout << endl << forclient << endl;
                                }

                            }
                        }


                    }
                }//HERE
            }
    else if (header_part == "4")//4 is SEE THE BID NOW
    {
        //-----------find client--------------//
        int vector_num = 255;
        for (size_t i = 0; i < uid.size(); i++)
        {
            SOCKET registed_buf = uid[i].sockets_value;
            if (registed_buf == ClientSocket)
            {
                vector_num = i;
            }
        }
        if (vector_num == 255)
        {
            cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
            send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
        }
        else
        {
            if (uid[vector_num].registed == 0)
            {
                cout << endl << "UID " << uidnum_part << " CLIENT NOT REGISTED YET" << endl;
                send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
            }
            else
            {
                //-------------------------TODO-------------------------------------//
                //find the bid num
                int bidding_num = 0;
                for (size_t i = 0; i < item.size(); i++)
                {
                    if (item[i].buyer == uidnum_part)
                    {
                        bidding_num++;
                    }
                }
                //figure out
                //no bid
                if (bidding_num == 0)
                {
                    send(ClientSocket, "CAN NOT FIND YOUR ANY BID", 200, 0);
                    cout << endl << "UID " << uidnum_part << " CLIENT NOT BID ANYMORE" << endl;
                }
                else
                {

                        send(ClientSocket, "SERVER SEND: ALL YOUR BID ARE HERE", 200, 0);
                        for (size_t i = 0; i < item.size(); i++)
                        {
                            if (item[i].buyer == uidnum_part)
                            {
                                char middle_use[5];
                                string send_item_buf1 = "ITEM ";//first part
                                sprintf(middle_use, "%d", i);
                                string item_number1(middle_use);//number part
                                send_item_buf1.append(item_number1);
                                string send_item_buf2 = " :NAME IS ";
                                send_item_buf1.append(send_item_buf2);//name part
                                send_item_buf1.append(item[i].name);
                                send_item_buf2 = " PRICE IS ";
                                send_item_buf1.append(send_item_buf2);//price part
                                send_item_buf1.append(item[i].price);
                                send_item_buf2 = " OWNER IS UID";
                                send_item_buf1.append(send_item_buf2);//owner part
                                send_item_buf1.append(item[i].owner);
                                send_item_buf2 = " BUYER IS UID";
                                send_item_buf1.append(send_item_buf2);//buyer part
                                send_item_buf1.append(item[i].buyer);
                                send_item_buf2 = " CODE IS ";//code part
                                send_item_buf1.append(send_item_buf2);//code part
                                sprintf(middle_use, "%d", item[i].itemcode);
                                string item_codebuf(middle_use);//code part
                                send_item_buf1.append(item_codebuf);
                                send_item_buf1.append(" ;");
                                send(ClientSocket, send_item_buf1.c_str(), 200, 0);//send it
                            }



                       }


                }

            }
        }//HERE
    }
    else if (header_part == "5")//5 is SEE THE SALE NOW
    {
        //-----------find client--------------//
        int vector_num = 255;
        for (size_t i = 0; i < uid.size(); i++)
        {
            SOCKET registed_buf = uid[i].sockets_value;
            if (registed_buf == ClientSocket)
            {
                vector_num = i;
            }
        }
        if (vector_num == 255)
        {
            cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
            send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
        }
        else
        {
            if (uid[vector_num].registed == 0)
            {
                cout << endl << "UID " << uidnum_part << " CLIENT NOT REGISTED YET" << endl;
                send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
            }
            else
            {
                //-------------------------TODO-------------------------------------//
                //find the bid num
                int bidding_num1 = 0;
                for (size_t i = 0; i < item.size(); i++)
                {
                    if (item[i].owner == uidnum_part && item[i].show == 0)//to avoid client withdraw
                    {
                        bidding_num1++;
                    }
                }
                //figure out
                //no bid
                if (bidding_num1 == 0)
                {
                    send(ClientSocket, "CAN NOT FIND YOUR ANY ITEM", 200, 0);
                    cout << endl << "UID " << uidnum_part << " CLIENT NOT ITEM ANYMORE" << endl;
                }
                else
                {

                        send(ClientSocket, "SERVER SEND: ALL YOUR ITEM ARE HERE", 200, 0);
                        for (size_t i = 0; i < item.size(); i++)
                        {
                            if (item[i].owner == uidnum_part && item[i].show == 0)
                            {
                                char middle_use[5];
                                string send_item_buf1 = "ITEM ";//first part
                                sprintf(middle_use, "%d", i);
                                string item_number1(middle_use);//number part
                                send_item_buf1.append(item_number1);
                                string send_item_buf2 = " :NAME IS ";
                                send_item_buf1.append(send_item_buf2);//name part
                                send_item_buf1.append(item[i].name);
                                send_item_buf2 = " PRICE IS ";
                                send_item_buf1.append(send_item_buf2);//price part
                                send_item_buf1.append(item[i].price);
                                send_item_buf2 = " OWNER IS UID";
                                send_item_buf1.append(send_item_buf2);//owner part
                                send_item_buf1.append(item[i].owner);
                                send_item_buf2 = " BUYER IS UID";
                                send_item_buf1.append(send_item_buf2);//buyer part
                                send_item_buf1.append(item[i].buyer);
                                send_item_buf2 = " ITEM CODE IS ";//code part
                                send_item_buf1.append(send_item_buf2);//code part
                                sprintf(middle_use, "%d", item[i].itemcode);
                                string item_codebuf(middle_use);//code part
                                send_item_buf1.append(item_codebuf);
                                send_item_buf1.append(" ;");
                                send(ClientSocket, send_item_buf1.c_str(), 200, 0);//send it
                            }

                        }




                }

            }
        }//HERE
    }
    else if (header_part == "6")//6 is TRY TO DEREGISTER
    {
        //-----------find client--------------//
        int vector_num = 255;
        for (size_t i = 0; i < uid.size(); i++)
        {
            SOCKET registed_buf = uid[i].sockets_value;
            if (registed_buf == ClientSocket)
            {
                vector_num = i;
            }
        }
        if (vector_num == 255)
        {
            cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
            send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
        }
        else
        {
            if (uid[vector_num].registed == 0)
            {
                cout << endl << "UID " << uidnum_part << " CLIENT NOT REGISTED YET" << endl;
                send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
            }
            else
            {
                //-------------------------TODO-------------------------------------//
                //find the owner num
                int owneritem = 0;
                for (size_t i = 0; i < item.size(); i++)
                {
                    if (item[i].owner == uidnum_part && item[i].show == 0)//to avoid client withdraw
                    {
                        owneritem++;
                    }
                }
                //find the buyer num
                int buyeritem = 0;
                for (size_t i = 0; i < item.size(); i++)
                {
                    if (item[i].buyer == uidnum_part && item[i].show == 0)//to avoid client withdraw
                    {
                        buyeritem++;
                    }
                }
                //figure out
                //no bid or sale now
                if (owneritem == 0 && buyeritem == 0)
                {
                    //find the client
                    int uidclient = atoi(uidnum_part.c_str());

                    for (size_t i = 0; i < uid.size(); i++)
                    {
                        int uidnum_buf = uid[i].number;
                        if (uidnum_buf == uidclient)
                        {
                            uid[i].registed = 0;//deregisted
                        }
                    }
                    send(ClientSocket, "SERVER SEND: YOUR DEREGISTED SUCCESS", 200, 0);
                    cout << endl << "UID " << uidnum_part << " CLIENT DEREGISTED SUCCESS" << endl;
                }
                else
                {

                    send(ClientSocket, "SERVER SEND: YOUR DEREGISTED FAILED, CAUSE YOU HAVE BID OR SALE NOW", 200, 0);
                    cout << endl << "UID " << uidnum_part << " CLIENT DEREGISTED FAILED, CAUSE HAVE BID OR SALE NOW" << endl;


                }

            }
        }//HERE
    }
    else if (header_part == "7")//7 is TRYING TO WITHDRAW ONE ITEM
    {
        found_itemcode_begin = recv_str.find("<itecod>");//get the item code
        found_itemcode_end = recv_str.find("</iteco>");//get the item code
        itemcode_part = recv_str.substr(found_itemcode_begin + 8, found_itemcode_end - found_itemcode_begin - 8);//code
                                                                                                                     //-----------find client--------------//
        int vector_num = 255;
        for (size_t i = 0; i < uid.size(); i++)
        {
            SOCKET registed_buf = uid[i].sockets_value;
            if (registed_buf == ClientSocket)
            {
                vector_num = i;
            }
        }
        if (vector_num == 255)
        {
            cout << endl << "CAN NOT FIND UID " << uidnum_part << " CLINET" << endl;
            send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
        }
        else
        {
            if (uid[vector_num].registed == 0)
            {
                cout << endl << "UID " << uidnum_part << " CLIENT NOT REGISTED YET" << endl;
                send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
            }
            else
            {
                //-------------------------TODO-------------------------------------//

                int bidcode = atoi(itemcode_part.c_str());
                int bidnum = 255;
                //find the item
                for (size_t i = 0; i < item.size(); i++)
                {
                    int codenum_buf = item[i].itemcode;
                    if (codenum_buf == bidcode)
                    {
                        bidnum = i;//item's num in vector
                    }
                }
                if (bidnum == 255)
                {
                    cout << endl << "CAN NOT FIND ITEM CODE " << itemcode_part << " ITEM" << endl;
                    send(ClientSocket, "CAN NOT FIND YOUR ITEM WANT TO WITHDRAW IN VECTOR", 200, 0);
                }
                else
                {
                    //figure out the item
                    //no one was bid
                    if (item[bidnum].buyer == "NULL")
                    {

                        //release the item in vector
                        item[bidnum].show = 1;
                        item_vector_num--;//do not forget to reduce the total num


                        //inform all client
                        string forclient = "SERVER SEND:ONE ITEM WITHDRAW\n";
                        string namebuf = "NAME: ";
                        string pricebuf = "PRICE: ";
                        string ownerbuf = "OWNER: ";
                        string buyerbuf = "BUYER: ";
                        string codebuf = "ITEM CODE: ";
                        string endbuf = " \n";
                        string bidname = item[bidnum].name;
                        string bidprice = item[bidnum].price;
                        string bidowner = item[bidnum].owner;
                        string bidbuyer = item[bidnum].buyer;
                        char bid_char[5];
                        sprintf(bid_char, "%d", item[bidnum].itemcode);
                        string bidcode(bid_char);
                        //for buyer
                        forclient.append(namebuf);
                        forclient.append(bidname);
                        forclient.append(endbuf);
                        forclient.append(pricebuf);
                        forclient.append(bidprice);
                        forclient.append(endbuf);
                        forclient.append(ownerbuf);
                        forclient.append(bidowner);
                        forclient.append(endbuf);
                        forclient.append(buyerbuf);
                        forclient.append(bidbuyer);
                        forclient.append(endbuf);
                        forclient.append(codebuf);
                        forclient.append(bidcode);
                        forclient.append(endbuf);
                        for (size_t i = 0; i < clientSocketGroup.size(); i++)
                        {
                            send(clientSocketGroup[i], forclient.c_str(), 200, 0);
                        }
                        cout << endl << forclient << endl;

                    }
                    else//there have buyer
                    {
                        string error_withdraw = "SERVER SEND: THE ITEM CODE ";
                        char bid_char[5];
                        sprintf(bid_char, "%d", item[bidnum].itemcode);
                        string bidcode(bid_char);
                        error_withdraw.append(bidcode);
                        error_withdraw.append(" ITEM HAS BUYER, SO CAN NOT WITHDRAW ");
                        send(ClientSocket, error_withdraw.c_str(), 200, 0);
                        cout << endl << error_withdraw << endl;

                    }
                }

            }
        }//HERE
    }
//------------------------------FIGURE OUT PART-------------------------------------------------//
//------------------------------FIGURE OUT PART-------------------------------------------------//
//------------------------------FIGURE OUT PART-------------------------------------------------//
        }
        else
        {
            //-----------find client--------------//
            int vector_num = 255;
            int uidnum_buf = 255;
            for (size_t i = 0; i < uid.size(); i++)
            {
                SOCKET registed_buf = uid[i].sockets_value;
                if (registed_buf == ClientSocket)
                {
                    vector_num = i;
                    uidnum_buf = uid[i].number;
                }
            }
            if (vector_num == 255)
            {
                cout << endl << "CAN NOT FIND UID " << uidnum_buf << " CLINET" << endl;
                send(ClientSocket, "CAN NOT FIND YOUR UID IN VECTOR", 200, 0);
            }
            else
            {
                if (uid[vector_num].registed == 0)
                {
                    cout << endl << "UID " << uidnum_buf << " CLIENT NOT REGISTED YET" << endl;
                    send(ClientSocket, "SERVER SEND:YOUR ARE NOT REGISTED YET", 200, 0);
                }
                else
                {
                    //-------------------------TODO-------------------------------------//
                    cout << endl << recv_buf << endl;
                }

            }//HERE

        }
        ReleaseSemaphore(bufferMutex, 1, NULL);
    }
    return 0;
}

DWORD WINAPI waittimeThread(LPVOID IpParameter)//need to do all the things
{
    int buf_thread = (int)(LPVOID)IpParameter;//received item code
    int vectoritem_num;//item's num in vector
    int vectoruid_num;//item's owner's uid in vector
    int vectorbuy_num;//item's buyer's uid in vector
    Sleep(300000);
    //maybe can use
    /*
    if(buyer == "null")
    {
       sleep
    }
    else
    {
    }
    */



    while (1)
    {
        //find the item num
        for (size_t i = 0; i < item.size(); i++)
        {
            int codenum_buf = item[i].itemcode;
            if (codenum_buf == buf_thread)
            {
                vectoritem_num = i;//item's num in vector
            }
        }

        //if the owner withdraw the item
        if (item[vectoritem_num].show == 1)
        {
            //release the item in vector
            for (size_t i = 0; i < item.size(); i++)
            {
                int erase_buf = item[i].itemcode;
                if (erase_buf == item[vectoritem_num].itemcode)
                {
                    item.erase(item.begin() + i);
                }
            }
            break;
        }


        //use the item uid to find owner
        int uidowner = atoi(item[vectoritem_num].owner.c_str());

        for (size_t i = 0; i < uid.size(); i++)
        {
            int uidnum_buf = uid[i].number;
            if (uidnum_buf == uidowner)
            {
                vectoruid_num = i;//item's owner's uid ni vector
            }
        }
        //send the owner message
        if (item[vectoritem_num].buyer == "NULL" || item[vectoritem_num].price == "NULL")//no one bid
        {
            string nobidbuf = "SERVER SEND:YOUR ITEM ";
            nobidbuf.append(item[vectoritem_num].name);
            nobidbuf.append(" NO ONE BID, TIEM OUT, REFRESH");
            send(uid[vectoruid_num].sockets_value, nobidbuf.c_str(), 200, 0);
            cout << endl << "OWNER UID" << uidowner << "'S ITEM " << item[vectoritem_num].name << " NO ONE BID";
            cout << " SO IT IS REFRESH 5 MINUTE AGAIN" << endl;
            Sleep(300000);
        }
        else//bid success
        {
            //find the buyer
            int uidbuyer = atoi(item[vectoritem_num].buyer.c_str());//buyer's uid
            for (size_t i = 0; i < uid.size(); i++)
            {
                int uidnum_buf1 = uid[i].number;
                if (uidnum_buf1 == uidbuyer)
                {
                    vectorbuy_num = i;//item's buyer's uid in vector
                }
            }
            //inform
            string forbuyer = "SERVER SEND:YOUR BID IS SUCCESS\n";
            string forowner = "SERVER SEND:YOUR SALE IS SUCCESS\n";
            string namebuf = "NAME: ";
            string pricebuf = "PRICE: ";
            string ownerbuf = "OWNER: ";
            string buyerbuf = "BUYER: ";
            string codebuf = "ITEM CODE: ";
            string endbuf = " \n";
            string bidname = item[vectoritem_num].name;
            string bidprice = item[vectoritem_num].price;
            string bidowner = item[vectoritem_num].owner;
            string bidbuyer = item[vectoritem_num].buyer;
            char bid_char[5];
            sprintf(bid_char, "%d", item[vectoritem_num].itemcode);
            string bidcode(bid_char);
            //for buyer
            forbuyer.append(namebuf);
            forbuyer.append(bidname);
            forbuyer.append(endbuf);
            forbuyer.append(pricebuf);
            forbuyer.append(bidprice);
            forbuyer.append(endbuf);
            forbuyer.append(ownerbuf);
            forbuyer.append(bidowner);
            forbuyer.append(endbuf);
            forbuyer.append(buyerbuf);
            forbuyer.append(bidbuyer);
            forbuyer.append(endbuf);
            forbuyer.append(codebuf);
            forbuyer.append(bidcode);
            forbuyer.append(endbuf);
            send(uid[vectorbuy_num].sockets_value, forbuyer.c_str(), 200, 0);
            //for owner
            forowner.append(namebuf);
            forowner.append(bidname);
            forowner.append(endbuf);
            forowner.append(pricebuf);
            forowner.append(bidprice);
            forowner.append(endbuf);
            forowner.append(ownerbuf);
            forowner.append(bidowner);
            forowner.append(endbuf);
            forowner.append(buyerbuf);
            forowner.append(bidbuyer);
            forowner.append(endbuf);
            forowner.append(codebuf);
            forowner.append(bidcode);
            forowner.append(endbuf);
            send(uid[vectoruid_num].sockets_value, forowner.c_str(), 200, 0);
            //release the item in vector
            for (size_t i = 0; i < item.size(); i++)
            {
                int erase_buf = item[i].itemcode;
                if (erase_buf == item[vectoritem_num].itemcode)
                {
                    item.erase(item.begin() + i);
                    item_vector_num--;//do not forget to reduce the total num
                }
            }
            cout << endl << "ONE ITEM BID SUCCESS" << endl;
            cout << "NAME: " << bidname << endl;
            cout << "PRICE: " << bidprice << endl;
            cout << "OWNER: " << bidowner << endl;
            cout << "BUYER: " << bidbuyer << endl;
            cout << "ITEM CODE: " << bidcode << endl;

            break;
        }
        //send(uid[vectoruid_num].sockets_value, "SERVER SEND:YOUR ITEM IS TIME OUT", 200, 0);

    }

    return 0;
}
