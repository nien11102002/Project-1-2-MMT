#ifndef MYSERVER_H
#define MYSERVER_H

#define WIN32_LEAN_AND_MEAN
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<WinSock2.h> // thư viện cho socket
#include<WS2tcpip.h> // thư viện cho socket loại 
//#include them cai database header vao nha
#pragma comment (lib,"WS2_32.lib")
using namespace std;

struct client_table {
	bool connected;
	SOCKET client_gate;
};

class Server {
private:
	SOCKET clientSocket;// socket de nhan va ket noi voi client.
	sockaddr_in hint; // lõsocketsocket
	string listenIP;
	int listenPortNum;
	char buffer[1024] = { '\0' }; // buffer nhận tin nhắn từ Client

public:
	Server(string IP, int portnumber) {
		this->listenIP = IP;
		this->listenPortNum = portnumber;
	}

	bool initSocket() {  // giống hàm khởi tạo socket của Client
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
		clientSocket = socket(AF_INET, SOCK_STREAM, 0); // tạo socket

		if (clientSocket != INVALID_SOCKET) {

			setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&i, sizeof(i)); // setup loại socket

			
			hint.sin_family = AF_INET; // gán IPv4
			hint.sin_port = htons(listenPortNum); // gán số port
			inet_pton(AF_INET, listenIP.c_str(), &hint.sin_addr); // hoàn chỉnh nội dung


			int bindCheck = bind(clientSocket, (sockaddr*)&hint, sizeof(hint)); // bind socket.
 
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
		vector<client_table> socialcredit; // mảng các client đang kết nối với server

		while (true) {
			int len = sizeof(hint);
			SOCKET connectionline = accept(clientSocket, (sockaddr*)&hint, &len); // tiếp nhận các socket muốn kết nối server

			if (connectionline != INVALID_SOCKET) // add vào mảng các client mới đã kết nối với server
			{
				client_table temp;

				temp.client_gate = connectionline;
				temp.connected = true;
			
				socialcredit.push_back(temp);
				cout << "New client: " << connectionline << endl;
				cout << "Online client(s): " << socialcredit.size() << endl;
			}

			Sleep(1);

			if (socialcredit.size() > 0) {// there are connected clients available.

				for (int cs = 0; cs < socialcredit.size(); cs++) {

					ZeroMemory(buffer, 1024);// reset buffer.

					if (socialcredit[cs].connected == true) { // kiểm tra coi nó có kết nối k? trường hợp rớt mạng

						int receivers = recv(socialcredit[cs].client_gate, buffer, 1024, 0); // nhận tin từ client

						// closing a client connection.
						if (Exit(buffer)) 
						{
							cout << "An ally has disconnected.\n";
							socialcredit[cs].connected = false;
							auto iter = socialcredit.begin() + cs;
							socialcredit.erase(iter);
						}
						else if (receivers > 0) // kiểm tra xem nó có nhận được tin từ client k?
						{
							cout << "<Client> " << buffer << endl;
								//sending to others client in a chat server
							Sleep(10);
							string msg;
							string messagetosend;
							do {
								cout << "> ";
								getline(cin, msg); // nhập tin nhắn muốn gửi
								messagetosend = msg;
							} while (msg == "");

							for (int i = 0; i < socialcredit.size(); i++) 
							{
								if (/*i != cs && ? t chưa hiểu sao phải khác cs ?*/ socialcredit[i].connected) // gửi tin nhắn cho các client đang kết nối, như ứng dụng chat
								{	
									int rep = send(socialcredit[i].client_gate, messagetosend.c_str(), 1024, 0);
									if (rep == SOCKET_ERROR) // kiểm tra xem có gửi cho client được không?
										cout << "LOI\n";
									
								}
							}
																					
						}
							
					}

				}

			}
		}
	}

	bool Exit(char buffer[]) {
		string msg = string(buffer);
		if (msg=="disconnected") { // nếu có chữ disconnect thì 
			return true;
		}
		return false;
	}

	~Server() {
		closesocket(clientSocket);
		WSACleanup();
	}

};

#endif
