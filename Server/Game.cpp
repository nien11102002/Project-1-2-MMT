#include "MyServer.h"

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

bool isGameOver(string cmd)
{
	bool result = false;
	if (cmd == "Game over")
		result = true;
	return result;
}