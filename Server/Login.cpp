#include"DataBase.h"
#include"MyServer.h"

void Login(unordered_map<Account*, Player*> hashmap, SOCKET client, char buffer[]) 
{
	string t = "Account: ";
	if (send(client, t.c_str(), t.size(), 0) == SOCKET_ERROR) {
		cout << "Error in Login Functions.\n";
		return;
	}
	
	ZeroMemory(buffer, 1024);
	if (recv(client, buffer, 1024, 0) == SOCKET_ERROR) {
		cout << "Error in recv Login Functions.\n";
		return;
	}
	string account = string(buffer);

	t = "Password: ";
	if (send(client, t.c_str(), t.size(), 0) == SOCKET_ERROR) {
		cout << "Error in Password Login Functions.\n";
		return;
	}

	ZeroMemory(buffer, 1024);
	if (recv(client, buffer, 1024, 0) == SOCKET_ERROR) {
		cout << "Error in recv password Login Functions.\n";
		return;
	}
	string password = string(buffer);

}