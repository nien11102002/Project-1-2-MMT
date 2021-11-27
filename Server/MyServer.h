#ifndef MYSERVER_H
#define MYSERVER_H

#include<iostream>
#include<string>
#include<thread>
#include<sstream>
#include<WinSock2.h>
#include<WS2tcpip.h>
//#include them cai database header vao nha
#pragma comment (lib,"WS2_32.lib")
using namespace std;

const int MAX_BUFFER_SIZE = 4096;

class Server {
private:
	SOCKET clientSocket;// socket de nhan va ket noi voi client.
	string listenIP;
	int listenPortNum;

public:
	Server(string IP, int portnumber) {
		this->listenIP = IP;
		this->listenPortNum = portnumber;
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

		clientSocket = socket(AF_INET, SOCK_STREAM, 0);

		if (clientSocket != INVALID_SOCKET) {

			sockaddr_in hint;
			hint.sin_family = AF_INET;
			hint.sin_port = htons(listenPortNum);
			inet_pton(AF_INET, listenIP.c_str(), &hint.sin_addr);
			int bindCheck = bind(clientSocket, (sockaddr*)&hint, sizeof(hint));

			if (bindCheck != SOCKET_ERROR) {//If bind OK:

				int listenCheck = listen(clientSocket, SOMAXCONN);	//Tell the socket is for listening. 
				if (listenCheck == SOCKET_ERROR) {
					cerr << "Can't listen from client.\n";
					closesocket(clientSocket);
					WSACleanup();
					exit(-1);
				}
			}
			else {
				cerr << "Can't bind the socket.\n";
				closesocket(clientSocket);
				WSACleanup();
				exit(-1);
			}

		}
		else {
			cout << "Error: can't create socket in server." << endl;
			WSACleanup();
			exit(-1);
		}

	}

	void Send() {// hàm gửi đến một client cụ thể, hàm chưa hoàn chỉnh

	}

	~Server() {
		closesocket(clientSocket);
		WSACleanup();
	}

};

#endif
