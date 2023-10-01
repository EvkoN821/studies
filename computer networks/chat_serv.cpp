// chat_serv.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <string>
#include <vector>
#pragma warning(disable: 4996) 
#pragma comment (lib, "Ws2_32.lib")

using namespace std;

CRITICAL_SECTION cs;
vector <pair<string, SOCKET>> sockStore(0);

const short serverPort = 1234; // Порт сервера

enum typeOfMessage {
    CONNECT,
    DISCONNECT,
    ALL
};

struct Client {
    char nick[1024];
    typeOfMessage current;
    char message[1024];
};

void initializeLibrary() {  //для инициализации использования библиотеки виндоус сокетс
    WSADATA wsaData;//содержит информацию о реализации сокетов Windows
    int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData); // MAKEWORD(2, 2) == 0x0202 - версия 2.2;  вызывается для инициации использования WS2 _32.dll.
    if (errorCode != 0) {
        cout << "Error initialization" << endl;
        exit(1);
    }
}

SOCKET createSocket() { //создание сокета
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // Создает TCP сокет
    if (sock == INVALID_SOCKET) {
        cout << "Error socket creation" << endl;
        exit(1);
    }
    return sock;
}

void bindSocket(SOCKET sock) { //связывание сокета с ip и портом
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = serverPort;
    address.sin_addr.s_addr = 0;
    int errorCode = bind(sock, (sockaddr*)&address, sizeof(address));
    if (errorCode != 0) {
        cout << "Error bind" << endl;
        exit(1);
    }
}

SOCKET acceptConnection(SOCKET listeningSock) {
    sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    SOCKET result = accept(listeningSock, (sockaddr*)&clientAddress, &clientAddressSize);
    // Делаем что то с адресом клиента clientAddress
    // Если не нужно, можно просто сделать accept(listeningSock, NULL, NULL)
    HOSTENT* hst;
    hst = gethostbyaddr((char*)&clientAddress.sin_addr, 4, AF_INET);
    cout << "New connection: ";
    cout << ((hst) ? hst->h_name : "Unknown host") << "/" << inet_ntoa(clientAddress.sin_addr) << "/" << ntohs(clientAddress.sin_port) << '\n';
    //inet_ntoa преобразует сетевой адрес Интернета (Iv4) в строку ASCII
    //ntohs преобразует u_short из сетевого порядка байтов TCP / IP в порядок байтов хоста
    return result;
}

Client clearClient(Client example) { // удаление данных о клиенте
    example.nick[0] = '\n';
    example.current = DISCONNECT;
    example.message[0] = '\n';
    return example;
}

Client readRequest(SOCKET sock) {  //чтение сообщения клиента
    Client buffer;
    int bytes = recv(sock, (char*)&buffer, sizeof(buffer), 0);
    if (bytes == 0) { // Если клиент отсоединился
        buffer = clearClient(buffer);
        return buffer;
    }
    else if (bytes < 0) {
        cout << "ERROR" << endl;
        buffer = clearClient(buffer);
        return buffer;
    }
    else return buffer;
}

bool alreadyExist(string nick) { //проверка существует ли клиент с таким именем
    for (int i = 0; i < sockStore.size(); i++) {
        if (sockStore[i].first == nick)
            return true;
    }
    return false;
}


bool writeResponse(SOCKET sock, string str) { //вывод информации от сервера
    int bytes = send(sock, str.c_str(), str.length() + 1, 0);//c_str - возвращает символ const char* , указывающий на строку с завершением null
    if (bytes < 0) {
        cout << "ERROR" << endl;
        return true;
    }
    else return bytes == 0;
}

DWORD WINAPI ThreadWork(LPVOID lpParameter) { //dword - 32 разрядное целие число без знака, от 0;  LPVOID lpParametr- данные потока
    SOCKET clientSock = *(SOCKET*)lpParameter;
    while (true) {
        Client request = readRequest(clientSock);
        EnterCriticalSection(&cs);
        if (request.current == CONNECT) {    //клиент присоединился
            if (alreadyExist(string(request.nick))) {   //если его имя занято
                writeResponse(clientSock, "Nickname has already been taken");
                closesocket(clientSock);
                LeaveCriticalSection(&cs);
                break;
            }
            else {  //если имя не занято, вывод тех кто онлайн и приветствия 
                string list_of_members = "";
                if (!sockStore.empty()) {
                    list_of_members += "\nOnline:\n";
                    for (pair<string, SOCKET> example : sockStore) {
                        list_of_members += example.first;
                        list_of_members += "\n";
                    }
                }
                writeResponse(clientSock, "You have joined the chat. Command: '-leave' \n" + list_of_members);
                sockStore.push_back(make_pair(string(request.nick), clientSock));
            }
        }
        else if (request.current == DISCONNECT) { // клиент отсоединился
            closesocket(clientSock);
            sockStore.erase(std::find(sockStore.begin(), sockStore.end(), make_pair(string(request.nick), clientSock)));
            for (int i = 0; i < sockStore.size(); i++) {
                writeResponse(sockStore[i].second, string(request.nick) + " leave the chat. \n");
            }
            LeaveCriticalSection(&cs);
            break;
        }
        else if (request.current == ALL) { //отправка сообщения всем
            for (int i = 0; i < sockStore.size(); i++) {
                if (clientSock != sockStore[i].second)
                    writeResponse(sockStore[i].second, string(request.message));
            }
        }
        LeaveCriticalSection(&cs);
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, 0);
    SetConsoleCP(1251);  //устанавливает кодировку ввода из консоли и из редактора кода
    SetConsoleOutputCP(1251); //устанавливает кодировку вывода на консоль;
    initializeLibrary(); //для инициализации использования библиотеки виндоус сокетс
    InitializeCriticalSection(&cs);  // инициализация секции
    SOCKET listeningSock = createSocket(); // создание сокета
    bindSocket(listeningSock); // связывание сокета с ip и портом
    listen(listeningSock, SOMAXCONN); //слушает порт и ждет когда будет установлено соединение
    cout << "Listening..." << endl;
    while (true) {
        SOCKET clientSock = acceptConnection(listeningSock); //принимает запрос на установку соединения
        CreateThread(NULL, 0, &ThreadWork, &clientSock, 0, NULL); //создание потока (дескриптор защиты,  начальный размер стека,  функция потока,  опции создания,  индетификатор потока)
    }
}
