#include "Server.hpp"

Server server;
int main(void) {
    server.InitWinSock();
    server.CreateSocket();
    server.BindSocket(8080);
    server.ExitWinSock();
    system("pause");
    return 0;
}
