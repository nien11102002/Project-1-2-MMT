#include "MyClient.h"
#include "Backup.h"

void CreateRoomHandle(Client& hexgate, string& messagetosend,int& flag)
{
	bool run = true;
	while (run)
	{
		string send;
		string recvmsg = hexgate.Receive();
		int SpaceIndex = recvmsg.find_first_of(" ");
		string tmp = recvmsg.substr(0, SpaceIndex);

		if (tmp != "Invitation")
			tmp == recvmsg;
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
		else if (tmp == "Game start")
		{
			run = false;
			flag = 1;
		}
		else {
			cout << recvmsg << endl;
			cout << ">> ";
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