#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <string>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;

#define SRV_HOST "127.0.0.1"
#define SRV_PORT 1234


struct Server{
    string type_string;
    int type;

    Server(): type_string(""), type(0){};
};
struct Client{
    string name;
    int grant;
    int type;

    Client(): name(""), type(0), grant(0){};
};
struct Node {
    string name;
    int type;
    int grant;
    Node* next;

    Node(string name, int grant): name(name), type(0), grant(grant), next(nullptr){};
};

struct List {
    Node *first;
    Node *last;

    List() : first(nullptr), last(nullptr) {}
    
    void pushBack(string name, int grant) {
        Node *c = new Node(name, grant);
        if (isEmpty()) {
            first = c;
            last = c;
            return;
        }
        last->next = c;
        last = c;
    }
	
	bool isEmpty() {
        return first == nullptr;
    }
	
    void printList() {
        if (isEmpty()) {
            return;
        }
        Node *p = first;
        string type_of_grant;
        while (p) {
            switch (p->type) {
                case 0: {
                    type_of_grant = "Zero grant.";
                    break;
                }
                case 1: {
                    type_of_grant = "Standart grant.";
                    break;
                }
                case 2: {
                    type_of_grant = "Increased grant.";
                    break;
                }
            }
            cout << p->name << " " << p->grant << " " << type_of_grant;
            cout << endl;
            p = p->next;
        }
    }
};

void printType(int type) {
    switch (type) {
        case 0: {
            cout << "no grant.";
            cout << endl;
            break;
        }
        case 1: {
            cout << "Standart grant.";
            cout << endl;
            break;
        }
        case 2: {
            cout << "Increased grant.";
            cout << endl;
            break;
        }
    }
}

int main() {
    char buff[10*1024];
    if(WSAStartup(0x0202,(WSADATA *)&buff[0])){
        cout << "Error WSAStartup: " << WSAGetLastError() << endl;
        return -1;
    }
    SOCKET dSocket = socket(AF_INET, SOCK_DGRAM, 0); // создание дейтаграммного сокета в домене IPv4 
    if(dSocket == INVALID_SOCKET){
        cout << "Socket error: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    HOSTENT *hst;
    sockaddr_in sAddr;  // заполнение адресной структуры параметрами сервера
    sAddr.sin_family=AF_INET;  
    sAddr.sin_port=htons(SRV_PORT);
    if(inet_addr(SRV_HOST)){
        sAddr.sin_addr.s_addr= inet_addr((SRV_HOST));  // если адрес в числовом формате
    } else if (hst= gethostbyname(SRV_HOST)){
        sAddr.sin_addr.s_addr=((unsigned long **)hst->h_addr_list)[0][0]; // получение ip  по символьному имени по днс
    } else {
        cout << "Unknown host: " << WSAGetLastError() << endl;
        closesocket(dSocket);
        WSACleanup();
        return -1;
    }
    List l;
    Client form_1;
    Server form_2;
    while(true) {
        cout << "Input student's name or stop: ";
        cin >> form_1.name;
        if(form_1.name == "stop"){
            break;
        }
        cout << "Input student's grant: ";
        cin >> form_1.grant;
        l.pushBack(form_1.name, form_1.grant);
        form_1.type=0;
        sendto(dSocket, (char*)&form_1, sizeof(Client), 0, (sockaddr *)&sAddr, sizeof(sAddr)); // передача сообщений на сервер
        sockaddr_in SRAddr;
        int SRAddr_size = sizeof(SRAddr);
        int check = recvfrom(dSocket, (char*)&form_2, sizeof(Server), 0, (sockaddr *)&SRAddr, &SRAddr_size);  // прием сообщения с сервера
        if(check == SOCKET_ERROR){
            cout << "Recvfrom error: " << WSAGetLastError() << endl;
            closesocket(dSocket);
            WSACleanup();
            return -1;
        }
        l.last->type=form_2.type;
        printType(l.last->type);
    }
    closesocket(dSocket);
    WSACleanup();
    l.printList();
    return 0;

}