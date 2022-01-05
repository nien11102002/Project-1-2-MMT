#include "MyClient.h"

int main() {
	Client hexgate;
	string msg, username;

	bool flag1 = false;
	do
	{
		string tmp;
		cout << ">> ";
		getline(cin, tmp);
		msg = tmp;
		int SpaceIndex = msg.find_first_of(" ");
		if (SpaceIndex != -1)
			msg = msg.substr(0, SpaceIndex);
		if (msg == "connect")
		{
			string sub = tmp.substr(SpaceIndex + 1, tmp.length() - SpaceIndex - 1);
			SpaceIndex = sub.find_first_of(" ");
			string ip = sub.substr(0, SpaceIndex);

			SpaceIndex = sub.find_last_of(" ");
			int port = stoi(sub.substr(SpaceIndex + 1, sub.length() - SpaceIndex - 1));
			hexgate.setPortNumber(port);
			hexgate.setServerIP(ip);
			if (hexgate.initSocket())
				flag1 = true;
			else cout << "Invalid Server IP or Port number.\n";
		}
		else if (msg == "close")
			exit(0);
		else cout << "Invalid command.\n";
	} while (!flag1);

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
					Sleep(1);
					cout << hexgate.Receive() << endl;
					break;
				}
				else if (msg == "Login" || msg == "login") {
					LoginHandle(hexgate, messageToSend, logged);
				}
				else if (msg == "Register" || msg == "register")
					RegisterHandle(hexgate, messageToSend);
				else
					cout << "Not Match any types.\n";

			}
			else {
				// da login
				bool operation = true;
				while (operation) {
					Sleep(500);
					system("cls");
					cout << "### Welcome to BattleShip Online! ###\n";
					// làm các hàm check user sau khi login tại đây.
					cout << "> What do you want to do?" << endl;
					cout << "> 1. Check the status of other players and Change your personal information" << endl;
					cout << "> 2. Start_game" << endl;
					cout << "> 3. Change pass.\n";
					cout << "> 4. Exit" << endl;
					cout << "> NOTE: type search to check status and change information. " << endl
						<< "OR type start_game to play game." << endl
						<< "change_password to change pass." << endl;
					cout << "Type exit to loggout.\n";
					string option;
					int flag = 0;
					cout << ">Your Choice: ";
					getline(cin, option);

					if (option == "search")
					{
						cout << "> What do you want to do?" << endl;
						cout << "> 1. Check the status of other players: check_user [-option] [username]" << endl;
						cout << "> 2. Change your personal information: setup_info [-option] [element]" << endl;
						cout << "> NOTE: If you need help, just type: /help [function]" << endl << endl;
						bool running = true;
						string opt;
						do
						{

							do {
								if (get_option(opt) == 0 && flag != 0)
									cout << "> Function unrecognized! Please re-enter";
								cout << "> Your choice: ";
								getline(cin, opt);
								cout << endl;
								flag++;
							} while (get_option(opt) == 0);

							switch (get_option(opt))
							{
							case 1:
							{
								hexgate.Sending(opt);
								string res = hexgate.Receive();
								cout << res;
							}
							break;
							case 2:
							{
								hexgate.Sending(opt);
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
							case 5:
								break;
							case -1: {
								cout << "Quiting";
								running = false;
								break;
							}

							default:
								break;
							}
							flag = 0; // create_room [id] with [username]
						} while (running);
					}
					else if (option == "start_game")
					{
						hexgate.Sending(option);
						messageToSend = option;
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
							if (msg == "upload_file")// thg moi gui trc.
							{
								UploadFileHandle(hexgate, messageToSend, map, stat);
								string msg = hexgate.Receive();
								string msgtosend;
								if (msg == "Your turn")
								{
									cout << "Your turn" << endl;
									Attack(hexgate, messageToSend, 0, map, stat,flag);
								}
								else if (msg == "Next turn")
								{
									cout << "Next turn" << endl;
									Attack(hexgate, messageToSend, 1, map, stat,flag);
								}
							}

						}
					}
					else if (option == "change_password") {
						hexgate.Sending(option);
						ChangePasswordHandle(hexgate, messageToSend);
					}
					else if (option == "exit" || option == "Exit") {
						hexgate.Sending(option);
						Sleep(1);
						cout << hexgate.Receive() << endl;
						exit(0);
					}
				}

			}

			Sleep(5); // hàm này dùng để dồng bộ giữa thời gian chạy giữa client và server để tránh lệch 
		}
	}


	return 0;
}
