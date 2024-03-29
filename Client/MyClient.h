#ifndef MYCLIENT_H
#define MYCLIENT_H

#include<iostream>
#include<string>
#include<sstream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<conio.h>
#include<regex>
#include <iomanip>
#include "Game.h"
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
	/*	ServerIP = "127.0.0.1";
		portNumber = 54010;*/
	}

	Client(string ip, int port)
	{
		ServerIP = ip;
		portNumber = port;
	}

	void setServerIP(string ip)
	{
		this->ServerIP = ip;
	}

	void setPortNumber(int port)
	{
		this->portNumber = port;
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

void LoginHandle(Client& hexgate, string& messagetosend, bool& logged);
void inputMaskedPassword(string& pass);
void RegisterHandle(Client& hexgate, string& messagetosend);
void ChangePasswordHandle(Client& hexgate, string& messagetosend);
void EncryptPassword(string& pass);

int get_option(string input);
void show_help_checkuser();
void show_help_setup();

void CreateRoomHandle(Client& hexgate, string& messagetosend, int& flag);
void UploadFileHandle(Client& hexgate, string& messagetosend, vector<vector<char>>& map, vector<vector<char>>& stat);
void Attack(Client& hexgate, string& messagetosend, int turn, vector<vector<char>> map, vector<vector<char>> stat,int& flag);
void getAttacked(Client& hexgate, vector<vector<char>>& stat, vector<vector<char>>& map, int& SHIP);

#endif
