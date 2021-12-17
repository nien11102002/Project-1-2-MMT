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
							cout << "Client "<<socialcredit[cs].client_gate << " data received : " << buffer << endl;
							if (!socialcredit[cs].logged) {
								string m = string(buffer);
								auto first = m.find_first_of(' ');

								string type = m.substr(0, first);
								string content = m.substr(first + 1, m.size() - first - 1);
								if (type == "login" || type == "Login") {
									bool flag = false;
									
									Login(hashmap, socialcredit[cs],flag, content);
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
									check_user_menu(hashmap, mess);
								}
								else if (option == "setup_info"){
									setup_info_menu(hashmap, mess, );
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

	bool Exit(char buffer[]) {
		string msg = string(buffer);
		if (msg == "Logout" || msg == "logout") {
			return true;
		}
		return false;
	}

	void Login(unordered_map<Account*, Player*> hashmap, client_table& the_wok, bool& flag, string content, string& user)
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
			new Player(C.Name(),0,0,C.Birthday())));

		sendmsg = "Registered successfully.\n"; Sleep(500);
		SendTo(the_wok.client_gate, sendmsg);
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

void check_user_menu(unordered_map<Account*, Player*>& hashmap, string opt) {
	int option = getoption(opt);
	string username = getname(opt);
	dispatch(hashmap, option, username);
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


void dispatch(unordered_map<Account*, Player*>& hashmap, int option, string username) {
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
		if (find_Name(hashmap, username)) cout << "Player " << username << " exists!\n\n";
		else cout << "Player " << username << " does not exist!\n\n";
		break;
	case check_online:
		if (check_Online(hashmap, username)) cout << "Player " << username << " is online\n\n";
		else if (!find_Name(hashmap, username)) cout << "Player " << username << " does not exist!\n\n";
		else cout << "Player " << username << " is not online!\n\n";
		break;
	case show_dob:
		show_DOB(hashmap, username);
		break;
	case show_fullname:
		show_Fullname(hashmap, username);
		break;
	case show_note:
		show_Note(hashmap, username);
		break;
	case show_all:
		show_All(hashmap, username);
		break;
	case show_point:
		show_Point(hashmap, username);
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

bool check_Online(unordered_map<Account*, Player*>& hashmap, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == username)
			if (it->second->Online()) return true;
	return false;
}

void show_DOB(unordered_map<Account*, Player*>& hashmap, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == username)
			cout << "Player " << username << "'s date of birth is: " << it->second->Birthday() << endl << endl;
	if (!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!\n\n";
}

void show_Fullname(unordered_map<Account*, Player*>& hashmap, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == username)
			cout << "Player " << username << "'s fullname is: " << it->second->Name() << endl << endl;
	if (!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!\n\n";
}

void show_Note(unordered_map<Account*, Player*>& hashmap, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == username)
			cout << "Player " << username << "'s note: " << it->second->getNote() << endl << endl;
	if (!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!\n\n";
}

void show_All(unordered_map<Account*, Player*>& hashmap, string username) {
	cout << "All information about Player: " << username << endl;
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == username) {
			cout << "Fullname: " << it->second->Name() << endl;
			cout << "Status: " << it->second->Online() << endl;
			cout << "Date of Birth: " << it->second->Birthday() << endl;
			cout << "Win: " << it->second->Win() << endl;
			cout << "Loss: " << it->second->Loss() << endl << endl;
		}
	if (!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!\n\n";
}

void show_Point(unordered_map<Account*, Player*>& hashmap, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == username)
			cout << "Player " << username << "'s point:\n Victory: " << it->second->Win()
			<< "\nDefeat: " << it->second->Loss() << endl << endl;
	if (!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!\n\n";
}

void setup_info_menu(unordered_map<Account*, Player*>& hashmap, string opt_setup, string username) {
	int option = getoption_setup(opt_setup);
	string element = getelement_setup(opt_setup);
	dispatch_setup(hashmap, option, element, username);
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


void dispatch_setup(unordered_map<Account*, Player*>& hashmap, int option, string element, string username) {
	const int change_fullname = 1;
	const int change_dob = 2;
	const int change_note = 3;
	switch (option)
	{
	case change_fullname:
		change_Fullname(hashmap, option, element, username);
		break;
	case change_dob:
		change_Dob(hashmap, option, element, username);
		break;
	case change_note:
		change_Note(hashmap, option, element, username);
		break;
	default:
		break;
	}
}


void change_Fullname(unordered_map<Account*, Player*>& hashmap, int option, string element, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->second->Name() == username) {
			it->second->setName(element);
			cout << "Name of player " << username << " has been changed to" << it->second->Name() << endl << endl;
		}
}

void change_Dob(unordered_map<Account*, Player*>& hashmap, int option, string element, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->second->Name() == username) {
			it->second->setBirthday(element);
			cout << "Birthday of player " << username << " has been changed to" << it->second->Name() << endl << endl;
		}
}

void change_Note(unordered_map<Account*, Player*>& hashmap, int option, string element, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->second->Name() == username) {
			it->second->setBirthday(element);
			cout << "Birthday of player " << username << " has been changed to" << it->second->Name() << endl << endl;
		}
}
#endif