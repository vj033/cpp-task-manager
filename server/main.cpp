#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <thread>


#pragma comment(lib, "ws2_32.lib")

void handleClient(SOCKET clientSocket);

void handleClient(SOCKET clientSocket)
{
    char buffer[1028];

    while (true)
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';
            std::cout << "Client says: " << buffer << std::endl;

            if (strcmp(buffer, "exit") == 0)
            {
                std::cout << "Client requested disconnect\n";
                break;
            }

            const char* response = "Server received your message";
            send(clientSocket, response, strlen(response), 0);
        }
        else if (bytesReceived == 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }
        else
        {
            std::cerr << "recv failed\n";
            break;
        }
    }

    closesocket(clientSocket);
}

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    std::cout << "Server listening on port 8080...\n";

    while (true)
    {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket != INVALID_SOCKET)
        {
            std::thread(handleClient, clientSocket).detach();
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
