#include"MyClient.h"

void LoginHandle(Client& hexgate, string& messagetosend) {
	bool run = true;
	while (run) 
	{
		string send;
		string recvmsg = hexgate.Receive();
		if (recvmsg == "") {
			cout << "Error in recv msg";
			send = "Error in recv msg";
			hexgate.Sending(send);
			run = false;
		}
		else if (recvmsg == "Account: ") {
			cout << recvmsg;
			getline(cin, send);
			hexgate.Sending(send);
		}
		else if (recvmsg == "Password: ") {
			cout << recvmsg;
			inputMaskedPassword(send);
			hexgate.Sending(send);
		}
		else if (recvmsg == "Login successfully.") {
			cout << recvmsg;
			run = false;
		}
		else {
			cout << "Invalid user.\n";
			run = false;
		}
	}
}

void inputMaskedPassword(string& pass)
{
	pass = "";
	char ch;
	ch = _getch();
	while (ch != 13)
	{
		if (ch == '\b')
		{
			if (pass.size() != 0)
			{
				cout << "\b \b";
				pass.erase(pass.size() - 1, 1);
			}
		}
		else
		{
			pass.push_back(ch);
			cout << "*";
		}
		ch = _getch();
	}
	cout<<endl;
} 
