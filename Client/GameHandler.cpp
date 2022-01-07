#include "MyClient.h"

void CreateRoomHandle(Client& hexgate, string& messagetosend,int& flag)
{
	bool run = true;
	string send;
	while (run)
	{
		string recvmsg = hexgate.Receive();
		int SpaceIndex = recvmsg.find_first_of(" ");
		string tmp = recvmsg.substr(0, SpaceIndex);

		if (tmp == "") {
			cout << "Error in recv msg";
			send = "Error in recv msg";
			hexgate.Sending(send);
			run = false;
		}
		else if (tmp == "Invitation") {
			cout << recvmsg << endl;
			char letter;
			do {
				cout << "(Y/N): ";
				cin >> letter;
				letter = toupper(letter);
			} while (letter != 'Y' && letter != 'N');
			send = ""; send += letter;
			hexgate.Sending(send);
		}
		else if (tmp == "Game")
		{
			cout << "Game begin" << endl;
			run = false;
			flag = 1;
		}
		else {
			cout << recvmsg << endl;
			if (tmp == "List")
			{
				cout << ">> ";
				getline(cin, send);
				hexgate.Sending(send);
			}

		}
	}
}

void UploadFileHandle(Client& hexgate, string& messagetosend,vector<vector<char>>& map, vector<vector<char>>& stat)
{
	int pos = messagetosend.find(" ");
	string tmp = messagetosend.substr(pos+1,messagetosend.length()-pos-1);

	ifstream file;
	file.open("map.txt", ios::out);
	if (!file.is_open())
		cerr << "Error" << endl;
	else
		ReadMap(file, map);
	file.close();
	file.open(tmp, ios::out);
	if (!file.is_open())
		cerr << "Error" << endl;
	else
		ReadData(file, stat);
}

void Attack(Client& hexgate, string& messagetosend,int turn,vector<vector<char>> map, vector<vector<char>> stat,int& flag)
{
	string tmp,var;
	int SHIP = 1;
	game_over = false;
	if (turn != 0)//0 means go first
	{
		getAttacked(hexgate, stat,map, SHIP);
	}

	do
	{
		int x, y;
		do
		{
			PrintPlayBoard(stat, map);
			
			do
			{
				cout << ">>";
				getline(cin, tmp);
				int a = tmp.find_last_of(" ") - tmp.find_first_of(" ") - 1;
				x = stoi(tmp.substr(12, a));
				y = stoi(tmp.substr(13 + a, tmp.size() - tmp.find_last_of(" ") - 1));
				x--; y--;
			} while (x < 0 || x > 20 || y < 0 || y > 20 || map[x][y] == 'o'||map[x][y]=='~');
			hexgate.Sending(tmp);
			var = hexgate.Receive();
			if (var == "hit")
			{
				cout << "\n\nYou have hit enemy ship.\n";
				map[x][y] = 'o';
			}
		} while (var == "hit");
		if (var == "miss")
		{
			map[x][y] = '~';
			getAttacked(hexgate, stat,map, SHIP);
		}
		else if (var == "game over")
		{
			game_over = true;
			cout << "You win" << endl;
		}
	} while (!game_over);

	char letter;
	do {
		cout << "Do you want to play again (Y/N): ";
		cin >> letter;
		letter = toupper(letter);
	} while (letter != 'Y' && letter != 'N');
	var = ""; var += letter;
	hexgate.Sending(var);
	var=hexgate.Receive();
	if (var == "Play again")
		flag = 1;
	else flag = 0;
	cout << "[Server] "<<var << endl;
}

void getAttacked(Client& hexgate, vector<vector<char>>& stat, vector<vector<char>>& map,int& SHIP)
{
	string msg;
	do
	{
		string tmp = hexgate.Receive();
		if (tmp == "game over")
		{
			cout << "You win." << endl;
			game_over = true;
			return;
		}
		cout << "Enemy " << tmp << endl;
		int a = tmp.find_last_of(" ") - tmp.find_first_of(" ") - 1;
		int x = stoi(tmp.substr(12, a));
		int y = stoi(tmp.substr(13 + a, tmp.size() - tmp.find_last_of(" ") - 1));
		x--; y--;

		if (stat[x][y] == 'x')
		{
			SHIP--;
			stat[x][y] = 'o';
			if (SHIP == 0)
			{
				msg = game_over;
				hexgate.Sending("game over");
				cout << "You lose";
				game_over = true;
			}
			else
			{
				msg = "hit";
				cout << msg;
				hexgate.Sending("hit");
			}
		}
		else
		{
			msg = "miss";
			stat[x][y] = '~';
			cout << msg;
			hexgate.Sending("miss");
		}
		PrintPlayBoard(stat, map);
	} while (msg == "hit");
}
