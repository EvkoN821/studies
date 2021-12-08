#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;

#define SRV_PORT 1234
struct Server {
    string type_string;
    int type;

    Server() : type_string(""), type(0) {};
};

struct Client{
    string name;
    int grant;
    int type;

    Client() : name(""), grant(0), type(0){};
};

int main() {
    char buff[1024];
    if(WSAStartup(0x0202, (WSADATA *)&buff[0])){
        cout << "Error WSAStartup \n" <<WSAGetLastError();
        return -1;
    }
    SOCKET dSocket = socket(AF_INET,SOCK_DGRAM,0); // создание сокета сервера
    if (dSocket == INVALID_SOCKET){
        cout << "Socket() error: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }

    Client form_1;
    Server form_2;
    sockaddr_in sAddr;
    sAddr.sin_family=AF_INET;
    sAddr.sin_addr.s_addr=INADDR_ANY;
    sAddr.sin_port=htons(SRV_PORT);
    if(bind(dSocket,(sockaddr *)&sAddr, sizeof(sAddr))){  // связывание сокета с локальным адресом
        cout << "Bind error: " << WSAGetLastError() << endl;
        closesocket(dSocket);
        WSACleanup();
        return -1;
    }

    while (true){
        sockaddr_in cAddr;
        int cAddr_size = sizeof(cAddr);
        int check = recvfrom(dSocket, (char*)&form_1, sizeof(Client),0,(sockaddr *)&cAddr, &cAddr_size); // прием данных от клиента
        if(check == SOCKET_ERROR) {
            cout << "Recvfrom error: "<< WSAGetLastError() << endl;
        }

        HOSTENT *hst = gethostbyaddr((char*)&cAddr.sin_addr,4,AF_INET);  // определение параметров клиента айпи адрес, симвл имени, порта
        cout << " new message from: " << ((hst)?hst->h_name:"Unknown host") << " " << inet_ntoa(cAddr.sin_addr)<< " " << ntohs(cAddr.sin_port) << endl;

        cout << "Info what i've got: " << form_1.grant << " grant from my friend" << endl;
        if (form_1.grant >= 3000) {
            form_2.type = 2;
            form_2.type_string="Increased grant";
        }
        else if (form_1.grant < 3000 && form_1.grant >0) {
            form_2.type = 1;
            form_2.type_string="Standard grant";
        }
        else if (form_1.grant == 0){
            form_2.type = 0;
            form_2.type_string="no grant";
        }
        sendto(dSocket, (char*)&form_2, sizeof(Server), 0, (sockaddr *)&cAddr, sizeof(cAddr));
        }

    return 0;

    }