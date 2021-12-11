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
			it->second->setOnline(true);
			return true;
		}

	return false;
}