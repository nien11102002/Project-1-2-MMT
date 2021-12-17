﻿#include"MyClient.h"

int main() {
	Client hexgate;
	string msg, username;

	if (hexgate.initSocket()) {

		hexgate.ConnectSocket();

		bool logged = false;

		while (true)
		{
			regex input_login("[Ll][Oo][Gg][Ii][Nn]");
			regex input_logout("[Ll][Oo][Gg][Oo][Uu][Tt]");
			regex input_register("[Rr][Ee][Gg][Ii][Ss][Tt][Ee]Rr]");
			string messageToSend;
			if (!logged) {
				do {
					cout << "> ";
					getline(cin, msg); // nhập tin nhắn muốn gửi
					messageToSend = msg;
				} while (msg == "");
				hexgate.Sending(messageToSend); // gửi gói tin cho server

				int pos = messageToSend.find_first_of(' ');
				msg = messageToSend.substr(0, pos);

				if (regex_match(msg,input_logout)) {
					cout << "See you next time.\n";
					break;
				}
				else if (regex_match(msg,input_login)) {
					LoginHandle(hexgate, messageToSend);
					logged = true;
				}
				else if (regex_match(msg,input_register))
					RegisterHandle(hexgate, messageToSend);
			}
			else {
				// da login
				Sleep(50);
				cout << "### Welcome to BattleShip Online! ###\n";
				// làm các hàm check user sau khi login tại đây.
				cout << "> What do you want to do?" << endl;
				cout << "> 1. Check the status of other players: check_user [-option] [username]" << endl;
				cout << "> 2. Change your personal information: setup_info [-option] [element]" << endl;
				cout << "> NOTE: If you need help, just type: /help [funciton]" << endl << endl;
				string option;
				int flag = 0;
				do {

					do {
						if (get_option(option) == 0 && flag != 0) 
							cout << "> Function unrecognized! Please re-enter";	
						cout << "> Your choice: ";
						getline(cin, option);
						cout << endl;
						flag++;
					} while (get_option(option) == 0);

					switch (get_option(option))
					{
					case 1:
						hexgate.Sending(option);
						break;
					case 2:
						hexgate.Sending(option);
						break;
					case 3:
						show_help_checkuser();
						break;
					case 4:
						show_help_setup();
						break;
					case -1:
						cout << "Logging out! See you next time.";
						break;
					default:
						break;
					}
					flag = 0;
				} while (true);
			}

			Sleep(5); // hàm này dùng để dồng bộ giữa thời gian chạy giữa client và server để tránh lệch 
		}
	}
	return 0;
}