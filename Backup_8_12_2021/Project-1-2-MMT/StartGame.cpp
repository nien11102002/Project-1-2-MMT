#include "Game.h"

void StartGame(int& ID,string& Player2)
{
	cout << ">>";
	int RoomID = 0;
	string OpponentName;
	string str,tmp;
	getline(cin, str);
	//Server se PrintOnlinePlayers ben Database cho Player 1;
	tmp = str.substr(0, 12);
	
	if (tmp == "create_room ")
	{
		tmp = str.substr(12, str.length() - 12);
		int SpaceIndex = tmp.find_first_of(" ");
		int a = stoi("1"+tmp.substr(0, SpaceIndex));
		int index = log10(a) + 1;
		RoomID = a / pow(10, index - 1);
		if (log10(RoomID)+1 != tmp.substr(0, SpaceIndex).length()||RoomID!=0)
		{
			cout << "Invalid Format Room ID!!!" << endl;
			return;
		}
		SpaceIndex = tmp.find_last_of(" ");
		OpponentName = tmp.substr(SpaceIndex + 1, tmp.length() - SpaceIndex - 1);
	}
}

void SendInvite(bool& choice) //server gửi lời mời từ player1 cho player 2
{
	cout << "Player ... has sent you an invitation to a match!!!";//Trích tên Player1 nhưng t chưa bk làm sao
	char answer = ' ';
	do 
	{
		cout << "Do you want to join game? (Y/N)\n";
		cin >> answer;

	} while (answer != 'Y' && answer != 'N');
	if (answer == 'Y')
		choice = true;
	else choice = false;
}