#include"MyClient.h"
#include "Game.h"

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
					cout << ">> ";
					getline(cin, msg); // nhập tin nhắn muốn gửi
					messageToSend = msg;
				} while (msg == "");
				hexgate.Sending(messageToSend); // gửi gói tin cho server

				int SpaceIndex = msg.find_first_of(" ");
				if (SpaceIndex != -1)
					msg = msg.substr(0, SpaceIndex);

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

				do {
					cout << ">> ";
					getline(cin, msg); // nhập tin nhắn muốn gửi
					messageToSend = msg;
				} while (msg == "");
				hexgate.Sending(messageToSend); // gửi gói tin cho server

				int SpaceIndex = msg.find_first_of(" ");
				if (SpaceIndex != -1)
					msg = msg.substr(0, SpaceIndex);

				if (msg == "change_password")
					ChangePasswordHandle(hexgate, messageToSend);
				else if (msg == "start_game")
				{
					int flag = 0;
					CreateRoomHandle(hexgate, messageToSend, flag);
					while (flag == 1)
					{
						do {
							cout << ">> ";
							getline(cin, msg); // nhập tin nhắn muốn gửi
							messageToSend = msg;
						} while (msg == "");
						hexgate.Sending(messageToSend);

						vector<vector<char>> map, stat;

						int SpaceIndex = msg.find_first_of(" ");
						if (SpaceIndex != -1)
							msg = msg.substr(0, SpaceIndex);
						if (msg == "upload_file")
						{
							UploadFileHandle(hexgate, messageToSend, map, stat);
							PrintPlayBoard(stat, map);
							string msg = hexgate.Receive();
							string msgtosend;
							if (msg == "Game begin")
							{
								do
								{
									cout << ">> ";
									getline(cin, msgtosend);
									hexgate.Sending(msgtosend);
								} while (true);
							}
						}
						
					}
				}
			}

			Sleep(5); // hàm này dùng để dồng bộ giữa thời gian chạy giữa client và server để tránh lệch 
		}
	}


	return 0;
}
	
