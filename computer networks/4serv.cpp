// 4serv.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>  
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib")  
using namespace std;
#define SRV_PORT 1234    
#pragma once
enum GRANT_TYPE { //перечисление
    GRANT_TYPE_ZERO,
    GRANT_TYPE_INCREASED,
    GRANT_TYPE_NORMAL,
    GRANT_TYPE_NAN,
};
struct ClientForm {
    int grant;
};
struct ServerForm {
    GRANT_TYPE grant = GRANT_TYPE_NAN;
};
void inline printClient(int client) {
    cout << "Amount of clients is:" << client << endl;
}
int nclient = 0; //количество клиентов
CRITICAL_SECTION cs;  //Объект критическая секция обеспечивает синхронизацию. Этим объектом может владеть только один поток, что и обеспечивает синхронизацию.
DWORD WINAPI handleClient(LPVOID client_socket) { //dword - 32 разрядное целие число без знака, от 0;  LPVOID lpParametr- данные потока
    ClientForm in;
    ServerForm out;
    SOCKET sock;
    sock = ((SOCKET*)client_socket)[0];
    while (1) {
        recv(sock, (char*)&in, sizeof(ClientForm), 0); //чтение данных клиента
        EnterCriticalSection(&cs);  //вход в секцию
        if (in.grant < 0) {
            LeaveCriticalSection(&cs); //завершение секции
            break;
        }
        if (in.grant > 2000) out.grant = GRANT_TYPE_INCREASED;
        else if (in.grant > 0) out.grant = GRANT_TYPE_NORMAL;
        else out.grant = GRANT_TYPE_ZERO;
        LeaveCriticalSection(&cs); //завершение секции
        send(sock, (char*)&out, sizeof(ServerForm), 0); //отправка данных клиенту
    }
    cout << "client is lost";
    nclient--;
    printClient(nclient);
    closesocket(sock);
    return 0;
}
int main() {
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
    {
        cout << "Error WSAStartup \n" << WSAGetLastError();   
        return -1;
    }
    SOCKET s, s_new;
    int from_len;
    sockaddr_in sin, from_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET; //формат адреса, 
    sin.sin_addr.s_addr = 0; //адрес (номер) узла сети
    sin.sin_port = htons(SRV_PORT);  // yномер порта на узле сети
    bind(s, (sockaddr*)&sin, sizeof(sin)); //связывание сокета с ip адресом и портом
    string msg, msg1;
    listen(s, SOMAXCONN); //слушает порт и ждет когда будет установлено соединение
    InitializeCriticalSection(&cs); //инициализация секции
    while (1) {
        from_len = sizeof(from_sin);
        s_new = accept(s, (sockaddr*)&from_sin, &from_len); //принимает запрос на установку соединения
        cout << "new connected client " << endl;
        nclient++;
        printClient(nclient);
        CreateThread(NULL, NULL, handleClient, &s_new, NULL, NULL); //создание потока (дескриптор защиты,  начальный размер стека,  функция потока,  опции создания,  индетификатор потока)
    }
    return 0;
}