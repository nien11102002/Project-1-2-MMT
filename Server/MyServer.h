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
		client_table opponent;
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
					Sleep(100);

					if (socialcredit[cs].connected == true) {

						int receivers = recv(socialcredit[cs].client_gate, buffer, 1024, 0);
						string user;
						if (receivers > 0)
						{
							cout << "Client " << socialcredit[cs].client_gate << " data received : " << buffer << endl;
							string flee = string(buffer);
							if (flee == "logout" || flee == "Logout" || flee == "exit" || flee == "Exit") {
								string out = "Bye bye, see u next time";
								SendTo(socialcredit[cs].client_gate, out);
								socialcredit[cs].account = socialcredit[cs].pass = "";
								socialcredit[cs].logged = false;
								socialcredit[cs].connected = false;
								socialcredit[cs].citizen.setOnline(false);
								socialcredit[cs].client_gate = NULL;
								vector<client_table>::iterator it;
								if (socialcredit.size() > 1)
									it = socialcredit.begin() + cs;
								else
									it = socialcredit.begin();
								socialcredit.erase(it);
								cout << "Disconnected.\n";
								break;
							}

							if (!socialcredit[cs].logged) {
								string m = string(buffer);
								auto first = m.find_first_of(' ');

								string type = m.substr(0, first);
								string content = m.substr(first + 1, m.size() - first - 1);
								user = content;
								if (type == "login" || type == "Login") {
									bool flag = false;
									Login(hashmap, socialcredit[cs], flag, content);
									socialcredit[cs].logged = flag;
								}
								else if (type == "register" || type == "Register") {
									Register(hashmap, socialcredit[cs], content);
								}
								else {
									string warning = "not match any type.\n";
									int rep = send(socialcredit[cs].client_gate, warning.c_str(), warning.size(), 0);
									if (rep == SOCKET_ERROR)
										cout << "Loi.\n";
								}
							}
							else {
								string mess = string(buffer);
								int first_space = mess.find_first_of(' ');
								string option = mess.substr(0, first_space);
								if (option == "check_user") {
									check_user_menu(hashmap, socialcredit[cs], mess);
								}
								else if (option == "setup_info") {
									setup_info_menu(hashmap, socialcredit[cs], mess, user);
								}
								else if (option == "change_password" || option == "Change_password")
								{
									ChangePassword(hashmap, socialcredit[cs]);
								}
								else if (option == "start_game")
								{
									string msg = PrintOnlinePlayers(socialcredit, socialcredit[cs]);
									SendTo(socialcredit[cs].client_gate, msg);
								}
								else if (option == "create_room")
								{
									Server_CreateRoom(hashmap, socialcredit[cs], socialcredit, mess, opponent);
								}
								else if (option == "upload_file")
								{
									StartGame(socialcredit[cs], opponent, mess);
									GameHandle(socialcredit[cs], opponent);
								}
								else {
									string warning = "not match any type.\n";
									int rep = send(socialcredit[cs].client_gate, warning.c_str(), warning.size(), 0);
									if (rep == SOCKET_ERROR)
										cout << "Loi.\n";
								}
							}
						}

					}

				}

			}
		}
	}

	int get_option(string input) {
		const regex quit_pattern("[Qq][Uu][Ii][Tt]");
		if (regex_match(input, quit_pattern)) return -1;
		string gura_choice = input.substr(0, input.find_first_of(' '));
		if (gura_choice == "check_user") return 1;
		else if (gura_choice == "setup_info") return 2;
		else if (gura_choice == "/help") {
			string function_string = input.substr(input.find_first_of(' ') + 1, input.size() - (input.find_first_of(' ') + 1));
			if (function_string == "check_user") return 3;
			else if (function_string == "setup_info") return 4;
		}
		return 0;
	}

	bool Exit(string user) {
		if (user == "Logout" || user == "logout" || user=="Exit"||user=="exit")
			return true;
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
		string message, client_table& oppo)
	{
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


			do {
				var = ReceiveFrom(Opponent.client_gate);
				message = var.substr(0, 1);
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

					reply = "Has sent your refuse.";
					SendTo(Opponent.client_gate, reply);
				}
				else
				{
					string reply = "Invitation Invalid answer!!! Please correctly resend!!!";
					SendTo(Opponent.client_gate, reply);
				}
			} while (message != "Y" && message != "N");
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
		oppo = Opponent;
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

	void StartGame(client_table the_wok, client_table opponent, string mess)
	{
		string var1, var2;
		bool flag = 1;
		do
		{
			var1 = mess;
			var2 = ReceiveFrom(opponent.client_gate);

			string tmp1 = var1.substr(0, var1.find(" "));
			string tmp2 = var2.substr(0, var2.find(" "));
			if (tmp1 == "upload_file" && tmp2 == "upload_file")
			{
				string rep = "Your turn";
				SendTo(the_wok.client_gate, rep);
				rep = "Next turn";
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

	void GameHandle(client_table the_wok, client_table opponent)
	{
		string var;
		do
		{
			do
			{
				var = ReceiveFrom(the_wok.client_gate);//receive attack 
				SendTo(opponent.client_gate, var);

				var = ReceiveFrom(opponent.client_gate);//receive "hit" or "miss" or "game over"
				SendTo(the_wok.client_gate, var);
			} while (var == "hit");

			do
			{
				var = ReceiveFrom(opponent.client_gate);
				SendTo(the_wok.client_gate, var);

				var = ReceiveFrom(the_wok.client_gate);
				SendTo(opponent.client_gate, var);
			} while (var == "hit");
		} while (var != "game over");
	}

	string PrintOnlinePlayers(vector<client_table> socialcredit, client_table the_wok)
	{
		stringstream builder;
		builder << "List users are online: ";
		for (int i = 0; i < socialcredit.size(); i++)
		{
			if (socialcredit[i].logged && socialcredit[i].account != the_wok.account)
			{
				builder << socialcredit[i].account << ",";
			}
		}

		string result = builder.str();
		return result;
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

	void check_user_menu(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string opt) {
		int option = getoption(opt);
		string username = getname(opt);
		dispatch(hashmap, the_wok, option, username);
	}

	int getoption(string opt) {
		const string opt1 = "find";
		const string opt2 = "online";
		const string opt3 = "show_date";
		const string opt4 = "show_fullname";
		const string opt5 = "show_note";
		const string opt6 = "show_all";
		const string opt7 = "show_point";
		regex option_pattern("-(\\w+_?\\w+)");
		smatch match;
		string option_string;
		regex_search(opt, match, option_pattern);
		option_string = match[1];
		if (option_string == opt1) return 1;
		else if (option_string == opt2) return 2;
		else if (option_string == opt3) return 3;
		else if (option_string == opt4) return 4;
		else if (option_string == opt5) return 5;
		else if (option_string == opt6) return 6;
		else if (option_string == opt7) return 7;
		else return 0;
	}

	string getname(string opt) {
		string user_string;
		smatch match;
		regex user_pattern("\\s(\\w+(\\s?\\w+)*)");
		regex_search(opt, match, user_pattern);
		user_string = match[1];
		return user_string;
	}

	void dispatch(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, int option, string username) {
		const int find_name = 1;
		const int check_online = 2;
		const int show_dob = 3;
		const int show_fullname = 4;
		const int show_note = 5;
		const int show_all = 6;
		const int show_point = 7;
		switch (option)
		{
		case find_name:
		{
			stringstream builder;
			if (find_Name(hashmap, username)) builder << "Player " << username << " exists!\n\n";
			else builder << "Player " << username << " does not exist!\n\n";
			string mts = builder.str();
			SendTo(the_wok.client_gate, mts);
			break;
		}
		case check_online:
		{
			stringstream builder;
			if (check_Online(socialcredit, username)) builder << "Player " << username << " is online\n\n";
			else if (!find_Name(hashmap, username)) builder << "Player " << username << " does not exist!\n\n";
			else builder << "Player " << username << " is not online!\n\n";
			string mts = builder.str();
			SendTo(the_wok.client_gate, mts);
			break;
		}
		case show_dob:
			show_DOB(hashmap, the_wok, username);
			break;
		case show_fullname:
			show_Fullname(hashmap, the_wok, username);
			break;
		case show_note:
			show_Note(hashmap, the_wok, username);
			break;
		case show_all:
			show_All(hashmap, the_wok, username);
			break;
		case show_point:
			show_Point(hashmap, the_wok, username);
			break;
		default:
			break;
		}
	}

	bool find_Name(unordered_map<Account*, Player*>& hashmap, string username) {
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->first->Account_name() == username) return true;
		return false;
	}

	bool check_Online(vector<client_table> socialcredit, string username) {
		for (int i = 0; i < socialcredit.size(); i++)
			if (socialcredit[i].account== username)
				if (socialcredit[i].citizen.Online()) return true;
		return false;
	}

	void show_DOB(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string username) {
		stringstream builder;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->first->Account_name() == username)
				builder << "Player " << username << "'s date of birth is: " << it->second->Birthday() << endl << endl;
		if (!find_Name(hashmap, username))
			builder << "Player " << username << " does not exist!\n\n";
		string mts = builder.str();
		SendTo(the_wok.client_gate, mts);
	}

	void show_Fullname(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string username) {
		stringstream builder;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->first->Account_name() == username)
				builder << "Player " << username << "'s fullname is: " << it->second->Name() << endl << endl;
		if (!find_Name(hashmap, username))
			builder << "Player " << username << " does not exist!\n\n";
		string mts = builder.str();
		SendTo(the_wok.client_gate, mts);
	}

	void show_Note(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string username) {
		stringstream builder;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->first->Account_name() == username)
				builder << "Player " << username << "'s note: " << it->second->getNote() << endl << endl;
		if (!find_Name(hashmap, username))
			builder << "Player " << username << " does not exist!\n\n";
		string mts = builder.str();
		SendTo(the_wok.client_gate, mts);
	}

	void show_All(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string username) {
		stringstream builder;
		builder << "All information about Player: " << username << endl;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->first->Account_name() == username) {
				builder << "Fullname: " << it->second->Name() << endl;
				builder << "Status: " << it->second->Online() << endl;
				builder << "Date of Birth: " << it->second->Birthday() << endl;
				builder << "Win: " << it->second->Win() << endl;
				builder << "Loss: " << it->second->Loss() << endl << endl;
			}
		if (!find_Name(hashmap, username))
			builder << "Player " << username << " does not exist!\n\n";
		string mts = builder.str();
		SendTo(the_wok.client_gate, mts);
	}

	void show_Point(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string username) {
		stringstream builder;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->first->Account_name() == username)
				builder << "Player " << username << "'s point:\n Victory: " << it->second->Win()
				<< "\nDefeat: " << it->second->Loss() << endl << endl;
		if (!find_Name(hashmap, username))
			builder << "Player " << username << " does not exist!\n\n";
		string mts = builder.str();
		SendTo(the_wok.client_gate, mts);
	}

	void setup_info_menu(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, string opt_setup, string user) {
		int option = getoption_setup(opt_setup);
		string element = getelement_setup(opt_setup);
		dispatch_setup(hashmap, the_wok, option, element, user);
	}

	int getoption_setup(string opt) {
		const string opt1 = "fullname";
		const string opt2 = "date";
		const string opt3 = "note";
		regex option_pattern("-(\\w+)");
		smatch match;
		string option_string;
		regex_search(opt, match, option_pattern);
		option_string = match[1];
		if (option_string == opt1) return 1;
		else if (option_string == opt2) return 2;
		else if (option_string == opt3) return 3;
		else return 0;
	}

	string getelement_setup(string opt) {
		string element_string;
		smatch match;
		regex user_pattern("\\s(\\w+(\\s?\\w+)*)");
		regex_search(opt, match, user_pattern);
		element_string = match[1];
		return element_string;
	}

	void dispatch_setup(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, int option, string element, string username) {
		const int change_fullname = 1;
		const int change_dob = 2;
		const int change_note = 3;
		switch (option)
		{
		case change_fullname:
			change_Fullname(hashmap, the_wok, option, element, username);
			break;
		case change_dob:
			change_Dob(hashmap, the_wok, option, element, username);
			break;
		case change_note:
			change_Note(hashmap, the_wok, option, element, username);
			break;
		default:
			break;
		}
	}

	void change_Fullname(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, int option, string element, string username) {
		stringstream builder;
		string mts;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->second->Name() == username) {
				it->second->setName(element);
				builder << "Name of player " << username << " has been changed to" << it->second->Name() << endl << endl;
				mts = builder.str();
				SendTo(the_wok.client_gate, mts);
			}

	}

	void change_Dob(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, int option, string element, string username) {
		stringstream builder;
		string mts;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->second->Name() == username) {
				it->second->setBirthday(element);
				builder << "Birthday of player " << username << " has been changed to" << it->second->Name() << endl << endl;
				mts = builder.str();
				SendTo(the_wok.client_gate, mts);
			}
	}

	void change_Note(unordered_map<Account*, Player*>& hashmap, client_table& the_wok, int option, string element, string username) {
		stringstream builder;
		string mts;
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
			if (it->second->Name() == username) {
				it->second->setBirthday(element);
				builder << "Birthday of player " << username << " has been changed to" << it->second->Name() << endl << endl;
				mts = builder.str();
				SendTo(the_wok.client_gate, mts);
			}
	}

	~Server() {
		WriteFile(hashmap, jav, editor);
		CleanHashmap(hashmap);
		closesocket(clientSocket);
		WSACleanup();
	}
};
#endif