// https://blog.csdn.net/2302_79840586/article/details/143577975
#ifndef _SERVER_HPP_
#define _SERVER_HPP_
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <WinSock2.h>
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

    bool BindSocket(unsigned short port) {
        // Bind Socket (16bits).
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);
        if(bind(sockfd,(sockaddr*)(&serverAddress),sizeof(serverAddress)) < 0) {
            // Bind Failed.
            perror("Socket bind failed");
            cerr << "Socket bind failed: " << GetLastError() << endl;
            return true;
        } return false;
    }

    void ExitWinSock(void) {
        // Cleanup Winsock.
        WSACleanup();
    }
};
#endif
