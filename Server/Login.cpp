#include"DataBase.h"
#include"MyServer.h"

void Login(unordered_map<Account*, Player*> hashmap, client_table& the_wok, char buffer[]) 
{
	int signal = 1;
	while (signal <= 2) 
	{
		Send_Request(the_wok, signal);
		if (!Recieve_Info(hashmap, the_wok, buffer))
			return;
	}

}

bool Recieve_Info(unordered_map<Account*, Player*> hashmap, client_table& the_wok, char buffer[]) {

	ZeroMemory(buffer, 1024);
	if (recv(the_wok.client_gate, buffer, 1024, 0) == SOCKET_ERROR) {
		cout << "Error in recv Login Functions.\n";
			return false;
	}

	string message = string(buffer);
	auto index = message.find_first_of(" ");
	string elo = message.substr(0, index - 1);
	string temp = message.substr(index + 1, message.size() - index);

	if (elo == "account") {
		the_wok.account = temp;
	}
	else if (elo == "password") {
		the_wok.pass = temp;
	}
	
	if (the_wok.account != "" && the_wok.pass != "") {
		if (!isMatch(hashmap, the_wok.account, the_wok.pass, the_wok.citizen)) {
			string reply = "Invalid user.\n";
			the_wok.account = the_wok.pass = "\0";
			int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
			if (rep == SOCKET_ERROR) {
				cout << "Error to send invalid user.\n";
				return false;
			}
				
		}
		else {
			the_wok.logged = true;
			string success = "Login successfully.\n";
			int result = send(the_wok.client_gate, success.c_str(), success.size(), 0);
			if (result == SOCKET_ERROR) {
				cout << "Error to send successfully login.\n";
				return false;
			}
		}
	}
		
	return true;
}

void Send_Request(client_table& the_wok, int signal) {

	if (signal == 1) {
		string request = "Account: ";
		
		int rep = send(the_wok.client_gate, request.c_str(), request.size(),0);
		if (rep == SOCKET_ERROR)
			cout << "Error to send.\n";
	}
	else if (signal == 2) {
		string request = "Password: ";

		int rep = send(the_wok.client_gate, request.c_str(), request.size(),0);
		if (rep == SOCKET_ERROR)
			cout << "Error to send.\n";
	}

}

bool isMatch(unordered_map<Account*, Player*> hashmap, string account, string password, Player& user) 
{
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == account && it->first->Pass() == password) {
			user.setName(it->second->Name());
			user.setBirthday(it->second->Birthday());
			user.setOnline(true);
			user.setWin(it->second->Win());
			user.setLoss(it->second->Loss());
			it->second->setOnline(true);
			return true;
		}

	return false;
}