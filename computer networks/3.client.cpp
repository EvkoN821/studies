#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// подавление предупреждений библиотеки winsock2
#include <winsock2.h>
#include <iostream>
#pragma comment (lib,"Ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define max_packet_size 65535

struct Request {
    string host;
    string path;
    Request() : host(""), path(""){};
};

int main() {
    WSADATA         ws;
    SOCKET          s;
    sockaddr_in     adr;
    HOSTENT* hn;
    char    buff[max_packet_size];
    if (WSAStartup(0x0202, &ws) != 0) {
        return -1;
    }
    if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, 0))){
        return -1;
    }

    Request data;

    cout << "Input full path: "<< "for example: www.json.org/json-en.html";
    string full_path, temp;
    getline(cin, full_path);
    long pos = 0;
	//собираем request
    if(full_path.find('/') != string::npos){  
        pos = full_path.find('/');
        temp = full_path;
        data.host = temp.erase(pos, full_path.length()-1);
        data.path = full_path.erase(0, pos+1);
    } else {
        data.host = full_path;
    }
    string request = "GET /" + data.path + " HTTP/1.1\nHost: "+data.host+"\n\n"; //
    cout << endl << request << endl;
    if (nullptr == (hn = gethostbyname(data.host.c_str()))){ //получение адреса
        return -1;
    }
	// заполняем  поля структуры adr для использование ее в connect
    adr.sin_family = AF_INET;
    ((unsigned long*)&adr.sin_addr)[0] = ((unsigned long**)hn->h_addr_list)[0][0];
    adr.sin_port = htons(data.host == "localhost" ? 8000 : 80);

    if (SOCKET_ERROR == connect(s, (sockaddr*)&adr, sizeof(adr))){ //установление соединения с сервером
        int res = WSAGetLastError(); return -1;
    }
    if (SOCKET_ERROR == send(s, request.c_str(), request.size(), 0)){ //посылаем запрос серверу
        int res = WSAGetLastError(); return -1;
    }
    int len = 0;
    do{
        if (SOCKET_ERROR == (len = recv(s, (char*)&buff, max_packet_size, 0))){
            int res = WSAGetLastError();     return -1;
        }
        for (int i = 0; i < len; i++)
            cout << buff[i];

    } while (len != 0); //получаем данные по частям, пока не len != 0.

    if (SOCKET_ERROR == closesocket(s)){ //закрытие соединения
        return -1;
    }
    cin.get();
    return 1;
}
