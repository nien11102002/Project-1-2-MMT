#include"Client Header.h"

int main() {
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0){
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}

	// Create a socket.
	SOCKET hexgate = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hexgate == INVALID_SOCKET){// check if it failed to create.
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	//Complete the core of hexgate 
	sockaddr_in core;
	core.sin_family = AF_INET;
	core.sin_port = htons(stoi(port));
	inet_pton(AF_INET, IP.c_str(), &core.sin_addr);

	// Connect to Server
	if (connect(hexgate, (SOCKADDR*)&core, sizeof(core)) == 0) {
		cout << "Connected!" << endl;
		string mess;

		while (true) {
			cout << "> ";
			getline(cin, mess);

			if (mess.compare("quit")){
				cout << "Break the connection.\n";
				break;
			}

			//message before send
			int iResult = send(hexgate, mess.c_str(), strlen(mess.c_str()), 0);

			if (iResult <= 0)
			{
				cout << "send() failed: " << WSAGetLastError() << endl;
				break;
			}
			
		}
	}
	else {
		cout << "Error Connecting to Host" << endl;
		exit(1);
	}

	//close socket.
	int result = shutdown(hexgate, SD_SEND);
	if (result == SOCKET_ERROR) {
		cout << "shutdown() failed with error: " << WSAGetLastError() << endl;
		closesocket(hexgate);
		WSACleanup();
		return 1;
	}

	closesocket(hexgate);
	WSACleanup();

	return 0;
}
