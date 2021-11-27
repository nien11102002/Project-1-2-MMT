#include"MyClient.h"

int main() {
	Client hexgate;
	string msg, username;

	cout << "Enter your username." << endl;
	getline(cin, username);

	if (hexgate.initSocket()) {

		hexgate.ConnectSocket();

		hexgate.recvThread = thread([&] { hexgate.ThreadRecv(); });

		while (true) {
			getline(cin, msg);
			string messageToSend;
			if (hexgate.joinChat == false) {
				std::ostringstream ss;
				ss << username << ": " << msg;
				messageToSend = ss.str();
			}
			else if (hexgate.joinChat == true) {
				std::ostringstream ss;
				ss << username << " joined the chat!";
				messageToSend = ss.str();
				hexgate.joinChat = false;
			}
			hexgate.Sending(messageToSend);
		}
	}
	return 0;
}