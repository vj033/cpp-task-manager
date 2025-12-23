//server
#include <iostream>
#include <winsock2.h>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // 1. Initialize Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // 2. Create server socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    // 3. Bind socket to IP + Port
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // 4. Start listening
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 8080...\n";

    // 5. Accept client connection
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected!\n";

    // 6. Receive message from client
    char buffer[1028];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Client says: " << buffer << std::endl;

        // 7. Send response back
        const char* response = "Message received by server";
        send(clientSocket, response, strlen(response), 0);
    }
    else if (bytesReceived == 0) {
        std::cout << "Client disconnected.\n";
    }
    else {
        std::cerr << "recv() failed\n";
    }

    // 8. Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
