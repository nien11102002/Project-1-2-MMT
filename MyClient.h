#ifndef MYCLIENT_H
#define MYCLIENT_H

#include<iostream>
#include<string>
#include<sstream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<thread>
#pragma comment(lib, "WS2_32.lib")
using namespace std;

class Client {
private:
	string ServerIP;
	int portNumber;
	sockaddr_in hint;
	SOCKET serverSocket;
	bool recvThreadRunning;

public:
	thread recvThread;
	bool joinChat = true;

	Client() {
		recvThreadRunning = false;
		ServerIP = "127.0.0.1";
		portNumber = 54010;
	}

	bool initSocket() {
		WSADATA hextech;
		WORD version = MAKEWORD(2, 2);
		int result = WSAStartup(version, &hextech);
		if (result != 0) {
			cout << "Error: can't start Winsock." << endl;
			return false;
		}
		return true;
	}

	void CreateSocket() {
		serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket == INVALID_SOCKET) {
			cout << "Error: can't create socket." << endl;
			WSACleanup();
			exit(-1);
		}

		hint.sin_family = AF_INET;
		hint.sin_port = htons(portNumber);
		inet_pton(AF_INET, ServerIP.c_str(), &hint.sin_addr);
	}

	void ConnectSocket() {
		CreateSocket();
		int connResult = connect(serverSocket, (sockaddr*)&hint, sizeof(hint));

		if (connResult == SOCKET_ERROR) {
			cout << "Error: can't connect to server." << endl;
			closesocket(serverSocket);
			WSACleanup();
			exit(-1);
		}
		else
			cout << "Connected to Server.\n";
	}

	void ThreadRecv() {
		recvThreadRunning = true;
		while (recvThreadRunning) {

			char buf[4096];
			ZeroMemory(buf, 4096);

			int bytesReceived = recv(serverSocket, buf, 4096, 0);
			if (bytesReceived > 0)		//If client disconnects, bytesReceived = 0; if error, bytesReceived = -1;
				cout << string(buf, 0, bytesReceived) << endl;

		}
	}

	void Sending(string text) {
		if (!text.empty() && serverSocket != INVALID_SOCKET) 
			send(serverSocket, text.c_str(), text.size() + 1, 0);
	}

	~Client(){
		closesocket(serverSocket);
		WSACleanup();
		if (recvThreadRunning) {
			recvThreadRunning = false;
			recvThread.join();	//Destroy safely to thread. 
		}
	}

};

#endif