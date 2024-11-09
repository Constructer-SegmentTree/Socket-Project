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
public:
    bool InitWinSock(void) {
        // Startup Winsock.
        if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0) {
            // Startup Failed.
            perror("WSA startup failed");
            cerr << "WSAStartup Failed: " << WSAGetLastError() << endl;
            return true;
        } return false;
    }
    
    bool CreateSocket(void) {
        // Create A Socket (IPv4).
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd < 0) {
            // Creation Failed.
            perror("Socket creation failed");
            cerr << "Socket creation failed: " << GetLastError() << endl;
            return true;
        } return false;
    }

    bool BindSocket(unsigned short port,string IP) {
        // Bind Socket (16bits).
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(IP.c_str());
        serverAddress.sin_port = htons(port);
        if(bind(sockfd,(sockaddr*)(&serverAddress),sizeof(serverAddress)) == SOCKET_ERROR) {
            // Bind Failed.
            perror("Socket bind failed");
            cerr << "Socket bind failed: " << GetLastError() << endl;
            return true;
        } return false;
    }

    bool ListenSocket(unsigned short num) {
        // Set Socket To Listenly.
        if(listen(sockfd,num) < 0) {
            // Setting Failed.
            perror("Socket(listener) creation failed");
            cerr << "Socket(listener) creation failed: " << GetLastError() << endl;
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
                perror("Socket Accept Failed");
                cerr << "Socket Accept Failed: " << GetLastError() << endl;
                continue;
            } return newSocket;
        }
    }

    void ExitWinSock(void) {
        // Cleanup Winsock.
        WSACleanup();
    }
};
#endif
