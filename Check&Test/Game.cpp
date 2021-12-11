#include "DataBase.h"
#include "MyServer.h"

//Mục đích để xử lí chung cho các yêu cầu của user
// Phân biệt như Operator này chỉ xử lí cái yêu cầu khi đã đăng nhập, không có trong khi chơi game
bool Operator(unordered_map<Account*, Player*> hashmap, client_table& the_wok, char buffer[],
				vector<client_table> socialcredit)
{
	ZeroMemory(buffer, 1024);
	if (recv(the_wok.client_gate, buffer, 1024, 0) == SOCKET_ERROR) {
		cout << "Error in recv.\n";
		return 0;
	}

	string message = string(buffer);
	string cmd = message.substr(0, message.find_first_of(" "));
	if (cmd == "start_game")
	{
		string reply = PrintOnlinePlayers(hashmap);
		int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
		if (rep == SOCKET_ERROR)
			cout << "Error to send.\n";
	}

	if (cmd == "create_room")
	{
		Server_CreateRoom(hashmap, the_wok, socialcredit, message);
	}

	if(cmd=="change_password")
	{ }

	if(cmd=="check_user")
	{ }

	if(cmd=="setup_info")
	{ }
}

string PrintOnlinePlayers(unordered_map<Account*, Player*> hashmap)
{
	stringstream builder;
	builder << "List users are online: ";
	for (auto i = hashmap.begin(); i != hashmap.end(); i++)
	{
		if (i->second->Online() == true)
		{
			builder << i->second->Name() << ",";
		}
	}

	string result = builder.str();
	return result;
}

void FindUser(string name, vector<client_table> socialcredit,int& isOnline,client_table& c)
{
	for (auto i = 0; i < socialcredit.size(); i++)
	{
		if (socialcredit[i].account == name)
		{
			c = socialcredit[i];
			isOnline = c.logged;
			return;
		}
	}
	isOnline = 2;
}

//Hàm của Server để xử lí về create_room khi user gọi
void Server_CreateRoom(unordered_map<Account*, Player*> hashmap, client_table the_wok,vector<client_table> socialcredit,
							string message)
{
	//Kiểm tra RoomID, tại t quy room ID chỉ là số nên kiểm tra nếu user có nhập sai j hay k
	CheckValidRoomID(hashmap, the_wok, socialcredit, message);

	int SpaceIndex = message.find_last_of(" ");
	string OpponentName = message.substr(SpaceIndex + 1, message.length() - SpaceIndex - 1);
	int isOnline = 0;
	client_table Opponent;
	FindUser(OpponentName, socialcredit, isOnline, Opponent);
	stringstream builder;
	if (isOnline == 1)//1 la online, 0 la offline, 2 la không tồn tại username
	{
		builder << "Player " + the_wok.account + " has sent you an invitation to a match!!!\n";
		builder << "Do you want to join game ? (Y / N)";
		string reply = builder.str();

		//Gửi lời mời cho User khác
		int rep = send(Opponent.client_gate, reply.c_str(), reply.size(), 0);
		if (rep == SOCKET_ERROR)
			cout << "Error to send.\n";

		char buffer[100];//Nhận tin nhắn của User được mời chơi
		if (recv(Opponent.client_gate, buffer, 1024, 0) == SOCKET_ERROR) {
			cout << "Error in recv.\n";
			return;
		}
		message = string(buffer);
		do {// Check Y/N hay sai cú pháp rồi rep lại
			if (message == "Y")
			{
				string reply = "Game start";
				int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
				if (rep == SOCKET_ERROR)
					cout << "Error to send.\n";

				int rep = send(Opponent.client_gate, reply.c_str(), reply.size(), 0);
				if (rep == SOCKET_ERROR)
					cout << "Error to send.\n";
			}
			else if (message == "N")
			{
				string reply = "Opponent refuse to play.";
				int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
				if (rep == SOCKET_ERROR)
					cout << "Error to send.\n";

				string reply = "Has sent your refuse.";
				int rep = send(Opponent.client_gate, reply.c_str(), reply.size(), 0);
				if (rep == SOCKET_ERROR)
					cout << "Error to send.\n";
			}
			else
			{
				string reply = "Invalid answer!!! Please correctly resend!!!";
				int rep = send(Opponent.client_gate, reply.c_str(), reply.size(), 0);
				if (rep == SOCKET_ERROR)
					cout << "Error to send.\n";
			}
		} while (message != "Y" || message != "N");
	}
	else if (isOnline == 0)
	{
		string reply = "Username is offline.";
		int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
		if (rep == SOCKET_ERROR)
			cout << "Error to send.\n";
	}
	else
	{
		string reply = "Wrong username.";
		int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
		if (rep == SOCKET_ERROR)
			cout << "Error to send.\n";
	}
}

void CheckValidRoomID(unordered_map<Account*, Player*> hashmap, client_table the_wok, vector<client_table> socialcredit,
	string message)
{
	string tmp = message.substr(12, message.length() - 12);
	int SpaceIndex = tmp.find_first_of(" ");
	int a = stoi("1" + tmp.substr(0, SpaceIndex));
	int index = log10(a) + 1;
	int RoomID = a / pow(10, index - 1);
	if (log10(RoomID) + 1 != tmp.substr(0, SpaceIndex).length() || RoomID != 0)
	{
		string reply ="Invalid Room ID.";

		int rep = send(the_wok.client_gate, reply.c_str(), reply.size(), 0);
		if (rep == SOCKET_ERROR)
			cout << "Error to send.\n";
	}
}
