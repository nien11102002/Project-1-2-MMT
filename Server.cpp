#include"Server Header.h"

int main() {
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}

	// Create a socket
	SOCKET hexcore = socket(AF_INET, SOCK_STREAM, 0);
	if (hexcore == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Exit program" << endl;
		return 0;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hexa;
	hexa.sin_family = AF_INET;
	hexa.sin_port = htons(stoi(port));
	hexa.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(hexcore, (sockaddr*)&hexa, sizeof(hexa));

	return 0;
}