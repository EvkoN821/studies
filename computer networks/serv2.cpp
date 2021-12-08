#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib")

using namespace std;

#define SRV_PORT 1111
#define BUF_SIZE 64


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
    SOCKET soc, soc2;
    int from_len;
    char buf[BUF_SIZE]={0};
    sockaddr_in sin, from_sin;
    soc=socket(AF_INET, SOCK_STREAM,0);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(SRV_PORT);
    bind(soc, (sockaddr *)&sin, sizeof(sin));
    string answer;
    int grant;
    int type;
    Client form_1;
    Server form_2;
    listen(soc, 3); // создание очереди клиентов
    while (true){
        from_len = sizeof(from_sin); // выделение из очереди сокета очередного клиента
        soc2 = accept(soc, (sockaddr *)&from_sin, &from_len);
        cout << "New client" << endl;
        while (true) {
            recv(soc2, (char*) &form_1, sizeof(Client), 0); // отправка сообщения
            if(form_1.name=="stop"){
                break;
            }
            cout << "I have just get " << form_1.grant << " grant from this student" << endl;
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
                form_2.type_string="Zero grant";
            }
            send(soc2, (char *) &form_2, sizeof(Server), 0);
        }
        cout << "Client lost" << endl;
        closesocket(soc2);
    }

    return 0;
}