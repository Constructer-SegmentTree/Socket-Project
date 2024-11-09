#include "Socket.hpp"

Client client;
int main(void) {
    client.InitWinSock();
    client.CreateSocket();
    client.ConnectSocket(8080,"127.0.0.1");
    system("pause");
    return 0;
}
