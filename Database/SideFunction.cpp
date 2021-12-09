#include "DataCore.h"

void PrintOnlinePlayers(unordered_map<Account*, Player*> hashmap)
{
	cout << "List users are online: ";
	for (auto i = hashmap.begin(); i != hashmap.end(); i++)
	{
		if (i->second->Online() == true)
		{
			cout << i->second->Name() << ",";
		}
	}
}
