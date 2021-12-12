#include"MyClient.h"

int main() {
	Client hexgate;
	string msg, username;

	if (hexgate.initSocket()) {

		hexgate.ConnectSocket();
		
		bool logged = false;

		while (true)
		{
			
			string messageToSend;
			if (!logged) {
				do {
					cout << "> ";
					getline(cin, msg); // nhập tin nhắn muốn gửi
					messageToSend = msg;
				} while (msg == "");
				hexgate.Sending(messageToSend); // gửi gói tin cho server

				if (msg == "Logout" || msg == "logout") {
					cout << "See you next time.\n";
					break;
				}
				else if (msg == "Login" || msg == "login") {
					LoginHandle(hexgate, messageToSend);
					logged = true;
				}
				else if (msg == "Register" || msg == "register")
					RegisterHandle(hexgate, messageToSend);
			}
			else {
				// da login
				cout << "da login thanh cong.\n";
			}
			

			Sleep(5); // hàm này dùng để dồng bộ giữa thời gian chạy giữa client và server để tránh lệch 
		}
	}
	return 0;
}
