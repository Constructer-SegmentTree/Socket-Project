#include "Socket.hpp"

Server server;
int main(void) {
    server.InitWinSock();
    server.CreateSocket();
    server.BindSocket(8080,"0.0.0.0");
    server.ListenSocket(3);
    SOCKET Sock = server.AcceptSocket();
    server.SendData(Sock,"Hello world!");
    cout << server.RecvData(Sock) << endl;
    server.ExitWinSock();
    system("pause");
    return 0;
}
