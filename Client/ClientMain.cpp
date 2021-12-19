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
					LoginHandle(hexgate, messageToSend,logged);
					logged = true;
				}
				else if (msg == "Register" || msg == "register")
					RegisterHandle(hexgate, messageToSend);
			}
			else {
				// da login
				/*Sleep(50);
				cout << "### Welcome to BattleShip Online! ###\n";
				// làm các hàm check user sau khi login tại đây.
				cout << "> What do you want to do?" << endl;
				cout << "> 1. Check the status of other players: check_user [-option] [username]" << endl;
				cout << "> 2. Change your personal information: setup_info [-option] [element]" << endl;
				cout << "> NOTE: If you need help, just type: /help [funciton]" << endl << endl;
				string option;
				int flag = 0;
				bool running = true;

				do 
				{
					Sleep(100);
					string var = hexgate.Receive();
					if (var != "none") {
						// moi vo game
					}

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
					{
						hexgate.Sending(option);
						string res = hexgate.Receive();
						cout << res;
					}
					break;
					case 2:
					{
						hexgate.Sending(option);
						string res = hexgate.Receive();
						cout << res;
					}
					break;
					case 3:
						show_help_checkuser();
						break;
					case 4:
						show_help_setup();
						break;
					case -1: {
						cout << "Logging out! See you next time.";
						exit(0);
					}

					default:
						break;
					}
					flag = 0;
				} while (running);*/
				
				/// //////////
				do {
					cout << ">> ";
					getline(cin, msg);
					messageToSend = msg;
				} while (msg == "");
				hexgate.Sending(messageToSend);
				
				int SpaceIndex = msg.find_first_of(" ");
				if (SpaceIndex != -1)
					msg = msg.substr(0, SpaceIndex);

				if (msg == "change_password")
					ChangePasswordHandle(hexgate, messageToSend);
				else if (msg == "start_game")
				{
					int flag = 0; int turn = 0;
					CreateRoomHandle(hexgate, messageToSend, flag);
					while (flag == 1)
					{
						do {
							cout << ">> ";
							getline(cin, msg);
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
							string msg = hexgate.Receive();
							string msgtosend;
							if (msg == "Your turn")
							{
								cout << "Your turn" << endl;
								Attack(hexgate, messageToSend, 0, map, stat);
							}
							else if (msg == "Next turn")
							{
								cout << "Next turn" << endl;
								Attack(hexgate, messageToSend, 1, map, stat);
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
	
