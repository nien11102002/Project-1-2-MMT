#include "DataCore.h"

void Register(unordered_map<Account*, Player*>& hashmap,string Command)
{
	int firstSpace = Command.find_first_of(" ") + 1;
	string username = Command.substr(firstSpace, Command.length() - firstSpace);
	if (!isAvailableUsername(hashmap, username))
	{
		cout << "This username isn't available!!!\n";
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
	} while (answer == 'Y' || answer == 'N');
	bool encr = 0;
	if (answer == 'Y')
	{
		encr = 1;
		cout << "Register successfully and Message was encrypted\n";
	}
	else cout << "Register successfullyand Message wasn’t encrypted\n";

	hashmap.insert(make_pair(new Account(username,encr,pass),new Player()));
}

bool isAvailableUsername(unordered_map<Account*, Player*>& hashmap, string S)
{
	bool result = true;
	for (auto i = hashmap.begin(); i != hashmap.end(); i++)
	{
		if (i->first->Account_name() == S)
		{
			result = false;
			break;
		}
	}

	return result;
}
