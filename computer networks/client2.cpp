#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNONGS
#include <winsock2.h>
#include <string>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

#define SRV_HOST "localhost"
#define SRV_PORT 1111
#define CLNT_PORT 2222


struct Server {
    string type_string;
    int type;
    Server() : type_string(""), type(0) {};
};

struct Node {
    string name;
    int type;
    int grant;
    Node* next;
    Node(string name, int grant) : name(name), type(0), grant(grant), next(nullptr) {};
};

struct Client {
    string name;
    int grant;
    int type;
    Client() : name(""), type(0), grant(0) {};
};

struct List {
    Node* first;
    Node* last;

    List() : first(nullptr), last(nullptr) {}

    bool isEmpty() {
        return first == nullptr;
    }

    void pushBack(string name, int grant) {
        Node* c = new Node(name, grant);
        if (isEmpty()) {
            first = c;
            last = c;
            return;
        }
        last->next = c;
        last = c;
    }

    void printList() {
        if (isEmpty()) {
            return;
        }
        Node* p = first;
        string type_of_grant;
        while (p) {
            switch (p->type) {
            case 0: {
                type_of_grant = "no grant.";
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

    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
        cout << "Error WSAStartup \n" << WSAGetLastError();
        return -1;

    }
    SOCKET soc; // создание сокета клиента
    hostent* hp;
    sockaddr_in clnt_sin;
    sockaddr_in srv_sin;
    soc = socket(AF_INET, SOCK_STREAM, 0);
    clnt_sin.sin_family = AF_INET;
    clnt_sin.sin_addr.s_addr = 0;
    clnt_sin.sin_port = htons(CLNT_PORT);
    bind(soc, (sockaddr*)&clnt_sin, sizeof(clnt_sin));  //связывание сокета с адресом клиента
    hp = gethostbyname(SRV_HOST);
    srv_sin.sin_port = htons(SRV_PORT);
    srv_sin.sin_family = AF_INET;
    ((unsigned long*)&srv_sin.sin_addr)[0] = ((unsigned  long**)hp->h_addr_list)[0][0];
    connect(soc, (sockaddr*)&srv_sin, sizeof(srv_sin));

    int f_length;
    List l;

    Client form_1;
    Server form_2;

    while (true) {
        cout << "Input student's name or stop: ";
        cin >> form_1.name;

        if (form_1.name == "stop") {
            send(soc, (char*)&form_1, sizeof(Client), 0);
            break;
        }

        cout << "Input student's grant: ";
        cin >> form_1.grant;

        l.pushBack(form_1.name, form_1.grant);

        form_1.type = 0;

        send(soc, (char*)&form_1, sizeof(Client), 0);

        recv(soc, (char*)&form_2, sizeof(Server), 0);

        l.last->type = form_2.type;
        printType(l.last->type);

    }

    closesocket(soc);
    l.printList();
    return 0;

}