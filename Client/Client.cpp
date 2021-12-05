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
			getline(cin, msg); // nhập tin nhắn muốn gửi
			string messageToSend = msg;

			hexgate.Sending(messageToSend); // gửi gói tin cho server
			string rec = hexgate.Receive(); // nhận gói tin từ server
			if (rec != "")
			{
				cout << rec << endl;
			}
			Sleep(5); // hàm này dùng để dồng bộ giữa thời gian chạy giữa client và server để tránh lệch 
		}
	}
	return 0;
}
