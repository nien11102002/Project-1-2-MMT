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
#pragma comment (lib,"WS2_32.lib")
using namespace std;


class Server {
private:
	SOCKET clientSocket;// socket de nhan va ket noi voi client.
	sockaddr_in hint;
	string listenIP;
	int listenPortNum;
	char buffer[1024] = { '\0' };

public:

	struct client_table {
		bool connected;
		SOCKET client_gate;
		bool logged;
		string account;
		string pass;
		string re_confirm;
		Player citizen;
	};

	unordered_map<Account*, Player*> hashmap;
	fstream jav, editor;
	vector<client_table> socialcredit;

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
							cout << "Client " << socialcredit[cs].client_gate << " data received : " << buffer << endl;
							if (!socialcredit[cs].logged) {
								string m = string(buffer);
								auto first = m.find_first_of(' ');

								string type, content;
								if (first != -1)
								{
									type = m.substr(0, first);
									content = m.substr(first + 1, m.size() - first - 1);
								}
								else type = m;

								if (type == "login" || type == "Login") {
									bool flag = false;
									Login(hashmap, socialcredit[cs], flag, content);
									socialcredit[cs].logged = flag;
								}
								else if (type == "register" || type == "Register") {
									Register(hashmap, socialcredit[cs], content);
								}
								else if (type == "change_password" || type == "Change_password")
								{
									ChangePassword(hashmap, socialcredit[cs]);
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
		if (msg == "Logout" || msg == "logout") {
			return true;
		}
		return false;
	}

	void Login(unordered_map<Account*, Player*> hashmap, client_table& the_wok, bool& flag, string content)
	{
		the_wok.account = content;

		string sendmsg = "Password: ";
		SendTo(the_wok.client_gate, sendmsg);
		string var = ReceiveFrom(the_wok.client_gate);
		if (var == "Error in recv msg") {
			cout << var << endl;
			return;
		}

		the_wok.pass = var;

		if (isMatch(hashmap, the_wok.account, the_wok.pass, the_wok.citizen))
		{
			sendmsg = "\nLogin successfully!\n";
			Sleep(500);
			SendTo(the_wok.client_gate, sendmsg);
			flag = true;
		}
		else
		{
			sendmsg = "Error, do not match any username.";
			Sleep(500);
			SendTo(the_wok.client_gate, sendmsg);
		}

	}

	void Register(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string content)
	{
		string sendmsg, var;
		if (isAvailableUsername(hashmap, content) == true)
		{
			sendmsg = "\nThis username is already exist!!!\n";
			Sleep(500);
			SendTo(the_wok.client_gate, sendmsg);
			return;
		}

		the_wok.account = content;

		sendmsg = "Password: ";
		SendTo(the_wok.client_gate, sendmsg);
		var = ReceiveFrom(the_wok.client_gate);
		if (var == "Error in recv msg") {
			cout << var << endl;
			return;
		}

		the_wok.pass = var;

		sendmsg = "Do you want to encrypt your message before sending?";
		SendTo(the_wok.client_gate, sendmsg);
		var = ReceiveFrom(the_wok.client_gate);
		if (var == "Error in recv msg") {
			cout << var << endl;
			return;
		}

		int encrypted = 0;
		if (var == "Y")
		{
			encrypted = 1; sendmsg = "Register successfully and Message was encrypted.";
			Sleep(100);
			SendTo(the_wok.client_gate, sendmsg);
		}
		else
		{
			encrypted = 0; sendmsg = "Register successfully and Message was not encrypted.";
			Sleep(100);
			SendTo(the_wok.client_gate, sendmsg);
		}

		// Dien thong tin nguoi dung luc moi dang ky.
		Player C;

		sendmsg = "What is your fullname: ";
		SendTo(the_wok.client_gate, sendmsg);
		var = ReceiveFrom(the_wok.client_gate);
		if (var == "Error in recv msg") {
			cout << var << endl;
			return;
		}
		C.setName(var);

		sendmsg = "What is your Date of Birth: ";
		SendTo(the_wok.client_gate, sendmsg);
		var = ReceiveFrom(the_wok.client_gate);
		if (var == "Error in recv msg") {
			cout << var << endl;
			return;
		}
		C.setBirthday(var);
		C.setWin(0); C.setLoss(0);

		Account A(the_wok.account, encrypted, the_wok.pass);
		writeAtBottomOfNewOne(C, A);

		hashmap.insert(make_pair(new Account(the_wok.account, encrypted, the_wok.pass),
			new Player(C.Name(), 0, 0, C.Birthday())));

		sendmsg = "Registered successfully.\n"; Sleep(500);
		SendTo(the_wok.client_gate, sendmsg);
	}

	void ChangePassword(unordered_map<Account*, Player*> hashmap, client_table& the_wok)
	{
		string sendmsg = "password: ";
		SendTo(the_wok.client_gate, sendmsg);
		string var;
		do
		{
			var = ReceiveFrom(the_wok.client_gate);
			if (var == "Error in recv msg") {
				cout << var << endl;
				return;
			}

			if (var != the_wok.pass)
			{
				string rep = "password: ";
				SendTo(the_wok.client_gate, rep);
			}
		} while (var != the_wok.pass);
		sendmsg = "Do you want to encrypt your message before sending?";
		SendTo(the_wok.client_gate, sendmsg);

		var = ReceiveFrom(the_wok.client_gate);
		if (var == "Error in recv msg") {
			cout << var << endl;
			return;
		}
		string flag = var;

		sendmsg = "new password: ";
		SendTo(the_wok.client_gate, sendmsg);
		
		var = ReceiveFrom(the_wok.client_gate);
		if (var == "Error in recv msg") {
			cout << var << endl;
			return;
		}

		the_wok.pass = var;

		if (flag == "Y")
			sendmsg = "Changepassword successfully and Message was encrypted.";
		else sendmsg = "Changepassword successfully and Message wasn't encrypted.";
		SendTo(the_wok.client_gate, sendmsg);

		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		{
			if (it->first->Account_name() == the_wok.account)
			{
				if (flag == "Y")
					it->first->setPassword(the_wok.pass, 1);
				else it->first->setPassword(the_wok.pass, 0);
				break;
			}
		}
	}

	
	void Server_CreateRoom(unordered_map<Account*, Player*> hashmap, client_table the_wok, vector<client_table> socialcredit,
		string message)
	{
		CheckValidRoomID(hashmap, the_wok, socialcredit, message);
		string var;
		int SpaceIndex = message.find_last_of(" ");
		string OpponentName = message.substr(SpaceIndex + 1, message.length() - SpaceIndex - 1);
		int isOnline = 0;
		client_table Opponent;
		FindUser(OpponentName, socialcredit, isOnline, Opponent);
		stringstream builder;
		if (isOnline == 1)//1 la online, 0 la offline, 2 la không tồn tại username
		{
			builder << "Invitation User " + the_wok.account + " has sent you an invitation to a match.\n";
			builder << "";
			string reply = builder.str();

			SendTo(Opponent.client_gate, reply);
			var = ReceiveFrom(Opponent.client_gate);
			if (var == "Error in recv msg") {
				cout << var << endl;
				return;
			}

			message = var;
			do {
				if (message == "Y")
				{
					string reply = "Game start";
					SendTo(the_wok.client_gate, reply);

					SendTo(Opponent.client_gate, reply);
				}
				else if (message == "N")
				{
					string reply = "Opponent refuse to play.";
					SendTo(the_wok.client_gate, reply);

					string reply = "Has sent your refuse.";
					SendTo(Opponent.client_gate, reply);
				}
				else
				{
					string reply = "Invitation Invalid answer!!! Please correctly resend!!!";
					SendTo(Opponent.client_gate, reply);
				}
			} while (message != "Y" || message != "N");
		}
		else if (isOnline == 0)
		{
			string reply = "Username is offline.";
			SendTo(the_wok.client_gate, reply);
		}
		else
		{
			string reply = "Wrong username.";
			SendTo(the_wok.client_gate, reply);
		}
	}

	void FindUser(string name, vector<client_table> socialcredit, int& isOnline, client_table& c)
	{
		for (auto i = 0; i < socialcredit.size(); i++)
		{
			if (socialcredit[i].account == name)
			{
				c = socialcredit[i];
				isOnline = c.logged;
				return;
			}
		}
		isOnline = 2;
	}

	void CheckValidRoomID(unordered_map<Account*, Player*> hashmap, client_table the_wok, vector<client_table> socialcredit,
		string message)
	{
		string tmp = message.substr(12, message.length() - 12);
		int SpaceIndex = tmp.find_first_of(" ");
		int a = stoi("1" + tmp.substr(0, SpaceIndex));
		int index = log10(a) + 1;
		int RoomID = a / pow(10, index - 1);
		if (log10(RoomID) + 1 != tmp.substr(0, SpaceIndex).length() || RoomID != 0)
		{
			string reply = "Invalid Room ID.";

			int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
			if (rep == SOCKET_ERROR)
				cout << "Error to send.\n";
		}
	}

	void StartGame(client_table the_wok,client_table opponent)
	{
		string var1, var2;
		bool flag = 1;
		do
		{
			var1 = ReceiveFrom(the_wok.client_gate);
			var2 = ReceiveFrom(opponent.client_gate);

			string tmp1 = var1.substr(0, var1.find(" "));
			string tmp2 = var2.substr(0, var2.find(" "));
			if (tmp1 == "upload_file" && tmp2 == "upload_file")
			{
				string rep = "Game begin";
				SendTo(the_wok.client_gate, rep);
				SendTo(opponent.client_gate, rep);
				flag = 0;
			}
			else
			{
				if (tmp1 != "upload_file")
				{
					string rep = "Wrong format";
					SendTo(the_wok.client_gate, rep);
				}
				if (tmp2 != "upload_file")
				{
					string rep = "Wrong format";
					SendTo(opponent.client_gate, rep);
				}
			}
		} while (flag);
	}

	void GameHandle(bool& game_over, client_table the_wok, client_table opponent, string cmd)
	{
		do
		{
			SendTo(opponent.client_gate, cmd);
			string var = ReceiveFrom(opponent.client_gate);//receive "hit" or "miss" or "game over"
			
			game_over = isGameOver(var);
			SendTo(the_wok.client_gate, var);
			if (var == "hit")
			{
				var = ReceiveFrom(the_wok.client_gate);
				continue;
			}
			else if (var == "miss")
			{
				var = ReceiveFrom(opponent.client_gate);
			}
		} while (!game_over);
	}




	string ReceiveFrom(SOCKET sock_id) {
		ZeroMemory(buffer, 1024);
		while (recv(sock_id, buffer, 1024, 0) == -1) {
			Sleep(100);
		}
		string response = string(buffer);
		return response;
	}

	void SendTo(SOCKET sock_id, string package) {
		send(sock_id, package.c_str(), package.size(), 0);
	}

	~Server() {
		WriteFile(hashmap, jav, editor);
		CleanHashmap(hashmap);
		closesocket(clientSocket);
		WSACleanup();
	}

};
#endif
