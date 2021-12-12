#ifndef MYCLIENT_H
#define MYCLIENT_H

#include<iostream>
#include<string>
#include<sstream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<conio.h>
#include<regex>

#pragma comment(lib, "WS2_32.lib")
using namespace std;

static string player;

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


	void Sending(string text) {
		if (!text.empty() && serverSocket != INVALID_SOCKET)
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

	string Receive() {
		char buffer[1024] = {};
		string reply;
		if (recv(serverSocket, buffer, 1024, 0) < 0)// teo
			return "";
		reply = string(buffer);
		return reply;
	}

	SOCKET Socket() {
		return this->serverSocket;
	}

	~Client() {
		closesocket(serverSocket);
		WSACleanup();
	}

};

void LoginHandle(Client& hexgate, string& messagetosend);
void inputMaskedPassword(string& pass);
void RegisterHandle(Client& hexgate, string& messagetosend);

void show_help_checkuser();
void show_help_setup();
#endif