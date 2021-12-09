#ifndef MYSERVER_H
#define MYSERVER_H

#define WIN32_LEAN_AND_MEAN
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include"DataBase.h"
//#include"Function Header.h"
#pragma comment (lib,"WS2_32.lib")
using namespace std;

struct client_table {
	bool connected;
	SOCKET client_gate;
	bool logged;
	string account;
	string pass;
	string re_confirm;
	Player citizen;
};

void Login(unordered_map<Account*, Player*> hashmap, client_table& the_wok, char buffer[]);
bool isMatch(unordered_map<Account*, Player*> hashmap, string account, string password, Player& user);
void Send_Request(client_table& the_wok, int signal);
bool Recieve_Info(unordered_map<Account*, Player*> hashmap, client_table& the_wok, char buffer[]);

class Server {
private:
	SOCKET clientSocket;// socket de nhan va ket noi voi client.
	sockaddr_in hint;
	string listenIP;
	int listenPortNum;
	char buffer[1024] = { '\0' };

public:
	unordered_map<Account*, Player*> hashmap;
	fstream jav, editor;

	Server(string IP, int portnumber) {
		this->listenIP = IP;
		this->listenPortNum = portnumber;
		LoadData(editor, jav, hashmap);
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

		int i = 1;
		clientSocket = socket(AF_INET, SOCK_STREAM, 0);

		if (clientSocket != INVALID_SOCKET) {

			setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&i, sizeof(i));


			hint.sin_family = AF_INET;
			hint.sin_port = htons(listenPortNum);
			inet_pton(AF_INET, listenIP.c_str(), &hint.sin_addr);


			int bindCheck = bind(clientSocket, (sockaddr*)&hint, sizeof(hint));

			if (bindCheck != SOCKET_ERROR) {//If bind OK:

				int listenCheck = listen(clientSocket, SOMAXCONN);	//Tell the socket is for listening. 
				unsigned long b = 1;
				ioctlsocket(clientSocket, FIONBIO, &b);

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
			closesocket(clientSocket);
			WSACleanup();
			exit(-1);
		}

	}

	void Run() {
		CreateSocket();
		vector<client_table> socialcredit;

		while (true) {
			int len = sizeof(hint);
			SOCKET connectionline = accept(clientSocket, (sockaddr*)&hint, &len);

			if (connectionline != INVALID_SOCKET)
			{
				client_table temp;

				temp.client_gate = connectionline;
				temp.connected = true;
				temp.logged = false;

				socialcredit.push_back(temp);
				cout << "New client: " << connectionline << endl;
				cout << "Online client(s): " << socialcredit.size() << endl;
			}

			Sleep(1);

			if (socialcredit.size() > 0) {// there are connected clients available.

				for (int cs = 0; cs < socialcredit.size(); cs++) {

					ZeroMemory(buffer, 1024);// reset buffer.

					if (socialcredit[cs].connected == true) {

						int receivers = recv(socialcredit[cs].client_gate, buffer, 1024, 0);

						// closing a client connection.
						if (Exit(buffer))
						{
							cout << "An ally has disconnected.\n";
							socialcredit[cs].connected = false;
							socialcredit[cs].logged = false;
							auto iter = socialcredit.begin() + cs;
							socialcredit.erase(iter);
						}
						else if (receivers > 0)
						{
							cout << "Client data received: " << buffer << endl;
							if (!socialcredit[cs].logged) {
								string type = string(buffer);
								if (type == "login" || type == "Login")
									Login(hashmap, socialcredit[cs], buffer);
								else if (type == "register" || type == "Register") {

								}
								else {
									string warning = "not match any type.\n";
									int rep = send(socialcredit[cs].client_gate, warning.c_str(), warning.size(), 0);
									if (rep == SOCKET_ERROR)
										cout << "Loi.\n";
								}
							}
							else {

							}
						}

					}

				}

			}
		}
	}

	bool Exit(char buffer[]) {
		string msg = string(buffer);
		if (msg == "Logout"|| msg == "logout") {
			return true;
		}
		return false;
	}

	~Server() {
		WriteFile(hashmap, jav, editor);
		CleanHashmap(hashmap);
		closesocket(clientSocket);
		WSACleanup();
	}

};


#endif
