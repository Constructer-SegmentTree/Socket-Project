#include "Socket.hpp"

Client client;
int main(void) {
    client.InitWinSock();
    client.CreateSocket();
    client.ConnectSocket(8080,"127.0.0.1");
    cout << client.RecvData() << endl;
    client.SendData("Hello, Server!");
    system("pause");
    return 0;
}
