#ifndef MYCLIENT_H
#define MYCLIENT_H

#include<iostream>
#include<string>
#include<sstream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;

class Client {
private:
	string ServerIP;
	int portNumber;
	sockaddr_in hint;
	SOCKET serverSocket;

public:

	Client() {
		ServerIP = "127.0.0.1";
		portNumber = 54010;
	}

	bool initSocket() {// khởi tạo các thông tin cơ bản của socket
		WSADATA hextech;
		WORD version = MAKEWORD(2, 2); // phiên bản 2.2.
		int result = WSAStartup(version, &hextech);
		if (result != 0) {
			cout << "Error: can't start Winsock." << endl;
			return false;
		}
		return true;
	}

	void CreateSocket() {
		serverSocket = socket(AF_INET, SOCK_STREAM, 0); // tạo socket
		if (serverSocket == INVALID_SOCKET) {
			cout << "Error: can't create socket." << endl;
			WSACleanup();
			exit(-1);
		}

		hint.sin_family = AF_INET; // gán IPv4
		hint.sin_port = htons(portNumber); // gán port number
		inet_pton(AF_INET, ServerIP.c_str(), &hint.sin_addr);// thiết lập nội dung
	}

	void ConnectSocket() {

		CreateSocket();
		int connResult = connect(serverSocket, (sockaddr*)&hint, sizeof(hint));// kết nốserverserver

		if (connResult == SOCKET_ERROR) {
			cout << "Error: can't connect to server." << endl;
			closesocket(serverSocket);
			WSACleanup();
			exit(-1);
		}
		else
			cout << "Connected to Server.\n";
	}


	void Sending(string text) {
		if (!text.empty() && serverSocket != INVALID_SOCKET)// gửi gói tiserverserver
		{
			int result = send(serverSocket, text.c_str(), text.size() + 1, 0);

			if (result == SOCKET_ERROR) {
				cout << "send fail with error: " << WSAGetLastError() << endl;
				closesocket(serverSocket);
				WSACleanup();
				exit(1);
			}
		}

	}

	string Receive() { // nhận gói tin từ server
		char buffer[1024] = { '\0' };
		string reply;
		if (recv(serverSocket, buffer, 1024, 0) < 0)// kiểm tra xem có nhận đc k?
		{
			cout << "receive failed!" << endl;
			return "LOI";
		}
		reply = string(buffer);
		return reply;
	}

	~Client() {
		closesocket(serverSocket);
		WSACleanup();
	}

};

#endif
