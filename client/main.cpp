#include<iostream>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib");

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cerr << "WSAStartup failed\n";
		return 1;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Socket creation failed";
		WSACleanup();
		return 1;
	}

	sockaddr_in severAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Connection failed\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	char buffer[1028];
	int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
	buffer[bytes] = '\0';

	std::cout << "Server says: " << buffer << std::endl;

	closesocket();
	WSACleanup();
	return 0;

}