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
		else if (recvmsg == "\nLogin successfully!\n") {
			cout << recvmsg;
			run = false;
		}
		else {
			cout << "\nInvalid user.\n";
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
	cout << endl;
}

void RegisterHandle(Client& hexgate, string& messagetosend)
{
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
		else if (recvmsg == "Do you want to encrypt your message before sending?") {
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
		else if (recvmsg == "What is your fullname: ") {
			cout << recvmsg;
			string name;
			cin.ignore();
			getline(cin, name);
			hexgate.Sending(name);
		}
		else if (recvmsg == "What is your Date of Birth: ") {
			cout << recvmsg;
			string DOB;
			getline(cin, DOB);
			hexgate.Sending(DOB);
		}
		else if (recvmsg == "Registered successfully.\n") {
			cout << recvmsg;
			run = false;
		}
		else {
			cout << recvmsg << endl;
		}
	}
}