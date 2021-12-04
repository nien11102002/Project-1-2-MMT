#include"MyClient.h"

int main() {
	Client hexgate;
	string msg, username;

	cout << "Enter your username." << endl;
	getline(cin, username);

	if (hexgate.initSocket()) {

		hexgate.ConnectSocket();

		while (true) {
			cout << "> ";
			getline(cin, msg);
			string messageToSend = msg;

			hexgate.Sending(messageToSend);
			string rec = hexgate.Receive();
			if (rec != "")
			{
				cout << rec << endl;
			}
			Sleep(5);
		}
	}
	return 0;
}