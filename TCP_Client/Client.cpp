#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;

    // Start Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create Socket
    SOCKET clientSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    std::cout << "Socket created\n";

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}