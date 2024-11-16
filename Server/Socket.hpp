// https://blog.csdn.net/2302_79840586/article/details/143577975
#ifndef _SERVER_HPP_
#define _SERVER_HPP_
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class Server {
private:
    WSAData wsaData;
    SOCKET sockfd;
    static const int MaxDataLen = 1024;
public:
    bool InitWinSock(void) {
        // Startup Winsock.
        if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0) {
            // Startup Failed.
            cerr << "WSAStartup Failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }
    
    bool CreateSocket(void) {
        // Create A Socket (IPv4).
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd == INVALID_SOCKET) {
            // Creation Failed.
            cerr << "Socket creation failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }

    bool BindSocket(unsigned short port,string IP) {
        // Bind Socket (16bits).
        sockaddr_in serverAddress = {0};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(IP.c_str());
        serverAddress.sin_port = htons(port);
        if(bind(sockfd,(sockaddr*)(&serverAddress),sizeof(serverAddress)) == SOCKET_ERROR) {
            // Bind Failed.
            cerr << "Socket bind failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }

    bool ListenSocket(unsigned short num) {
        // Set Socket To Listenly.
        if(listen(sockfd,num) < 0) {
            // Setting Failed.
            cerr << "Socket(listener) creation failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }

    SOCKET AcceptSocket(void) {
        // Accept Clients Socket.
        sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        while(true) {
            SOCKET newSocket = accept(sockfd,(sockaddr*)(&sockfd),&clientAddressSize);
            if(newSocket == INVALID_SOCKET) {
                // Accept Failed.
                cerr << "Socket Accept Failed: " << WSAGetLastError() << endl;
                continue;
            } return newSocket;
        }
    }

    bool SendData(SOCKET ClientSocket,const char* Data) {
        // Send Data To Client.
        if(send(ClientSocket,Data,strlen(Data),0) == SOCKET_ERROR) {
            // Send Failed.
            cerr << "Send failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }

    string RecvData(SOCKET ClientSocket) {
        char buffer[MaxDataLen];
        recv(ClientSocket,buffer,sizeof(buffer),0);
        return string(buffer);
    }

    void ExitWinSock(void) {
        // Cleanup Winsock.
        WSACleanup();
    }
};

class Client {
private:
    WSAData wsaData;
    SOCKET sockfd;
    static const int MaxDataLen = 1024;
public:
    bool InitWinSock(void) {
        // Startup Winsock.
        if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0) {
            // Startup Failed.
            cerr << "WSAStartup Failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }
    
    bool CreateSocket(void) {
        // Create A Socket (IPv4).
        sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(sockfd == INVALID_SOCKET) {
            // Creation Failed.
            cerr << "Socket creation failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }

    bool ConnectSocket(unsigned short port,string IP) {
        // Connect Server.
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.s_addr = inet_addr(IP.c_str());
        if(connect(sockfd,(sockaddr*)(&serverAddress),sizeof(serverAddress)) == SOCKET_ERROR) {
            cerr << "Connection failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }

    bool SendData(const char* Data) {
        // Send Data To Server.
        if(send(sockfd,Data,strlen(Data),0) == SOCKET_ERROR) {
            // Send Failed.
            cerr << "Send failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }

    string RecvData(void) {
        char buffer[MaxDataLen];
        recv(sockfd,buffer,sizeof(buffer),0);
        return string(buffer);
    }

    void ExitWinSock(void) {
        // Cleanup Winsock.
        WSACleanup();
    }
};

#endif
