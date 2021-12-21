#include"DataBase.h"
#include"MyServer.h"

bool isMatch(unordered_map<Account*, Player*> hashmap, string account, string password, Player& user)
{
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		if (it->first->Account_name() == account && it->first->Pass() == password) {
			user.setName(it->second->Name());
			user.setBirthday(it->second->Birthday());
			user.setOnline(true);
			user.setWin(it->second->Win());
			user.setLoss(it->second->Loss());
			return true;
		}

	return false;
}

bool isAvailableUsername(unordered_map<Account*, Player*> hashmap, string S)
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