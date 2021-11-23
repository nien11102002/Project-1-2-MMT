#include "DataCore.h"

void Register(unordered_map<Account*, Player*>& hashmap, string Command)
{
	int firstSpace = Command.find_first_of(" ") + 1;
	string username = Command.substr(firstSpace, Command.length() - firstSpace);
	if (isAvailableUsername(hashmap, username) == true)
	{
		cout << "This username is already exist!!!\n";
		return;
	}
	cout << ">> Password: ";
	string pass;
	getline(cin, pass);
	cout << "Do you want to encrypt your message before sending?\n";

	char answer;
	do
	{
		cout << "(Y/N): ";
		cin >> answer;
		answer = toupper(answer);

	} while (answer != 'Y' && answer != 'N');

	bool encr = 0;
	if (answer == 'Y')
	{
		encr = 1;
		cout << "Register successfully and Message was encrypted\n";
	}
	else cout << "Register successfullyand Message wasn’t encrypted\n";

	cin.ignore();
	string name, DOB;
	int d, m, y;
	cout << "What is your fullname: ";
	getline(cin, name);
	cout << "\nWhat is your Date of Birth: \n";
	cout << "Day: "; cin >> d;
	cout << "Month: "; cin >> m;
	cout << "Year: "; cin >> y;
	stringstream builder;
	builder << d << "/" << m << "/" << y;
	DOB = builder.str();

	Player P(name, 0, 0, DOB);
	Account A(username, encr, pass);
	writeAtBottomOfNewOne(P, A);

	hashmap.insert(make_pair(new Account(username, encr, pass), new Player(name, 0, 0, DOB)));
	cin.ignore();
}

bool isAvailableUsername(unordered_map<Account*, Player*>& hashmap, string S)
{
	bool result = false;
	for (auto i = hashmap.begin(); i != hashmap.end(); i++)
	{
		if (i->first->Account_name() == S)
		{
			result = true;
			return result;
		}
	}

	return result;
}

void writeAtBottomOfNewOne(Player P, Account A)
{
	fstream f;
	f.open("Acc and Pass.txt", ios::out | ios::app);
	f << endl;
	f << A.Account_name() << endl;;
	f << A.encryption() << endl;
	f << A.Pass() << endl;
	f.close();

	f.open("Player.txt", ios::out | ios::app);
	f << endl;
	f << P.Name() << endl;
	f << P.Birthday() << endl;
	f << P.Win() << endl;
	f << P.Loss() << endl;
	f.close();
}
