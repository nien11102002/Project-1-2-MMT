#include"MyClient.h"

void LoginHandle(Client& hexgate, string& messagetosend, bool& logged) {
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
		else if (recvmsg == "Password: ") {
			cout << recvmsg;
			inputMaskedPassword(send);
			hexgate.Sending(send);
		}
		else if (recvmsg == "Do you want to encrypt your password?") {
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
		else if (recvmsg == "\nLogin successfully!\n") {
			cout << recvmsg;
			logged = true;
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


void ChangePasswordHandle(Client& hexgate, string& messagetosend)
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
		else if (recvmsg == "password: " || recvmsg == "new password: ") {
			cout << ">>" << recvmsg;
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
		else {
			cout << recvmsg << endl;
			run = false;
		}
	}
}

int get_option(string input) {
	const regex quit_pattern("[Qq][Uu][Ii][Tt]");
	if (regex_match(input, quit_pattern)) return -1;
	string gura_choice = input.substr(0, input.find_first_of(' '));
	if (gura_choice == "check_user") return 1;
	else if (gura_choice == "setup_info") return 2;
	else if (gura_choice == "/help") {
		string function_string = input.substr(input.find_first_of(' ') + 1, input.size() - (input.find_first_of(' ') + 1));
		if (function_string == "check_user") return 3;
		else if (function_string == "setup_info") return 4;
	}
	return 0;
}