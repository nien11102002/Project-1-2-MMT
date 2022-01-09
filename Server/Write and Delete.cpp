#include"DataBase.h"
#include"MyServer.h"

void WriteFile(map<Account*, Player*> hashmap, fstream& jav, fstream& editor) {
	editor.open("Acc and Pass.txt", ios::out);
	jav.open("Player.txt", ios::out);


	if (!editor.is_open() && !jav.is_open()) {
		cerr << "Can't open file.\n";
		jav.close(); editor.close();
		return;
	}
	else {
		auto flag = hashmap.rbegin();
		for (auto it = begin(hashmap); it != end(hashmap); it++)
		{
			editor << it->first->Account_name() << endl;
			editor << it->first->Pass();
			if (*it != *flag)
				editor << endl;

			jav << it->second->Name() << endl;
			jav << it->second->Birthday() << endl;
			jav << it->second->Win() << endl;
			jav << it->second->Loss();
			if (*it != *flag)
				jav << endl;
			
		}
	}
	jav.close(); editor.close();
}


void CleanHashmap(map<Account*, Player*>& hashmap) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
	{
		delete it->first;
		delete it->second;
		hashmap.erase(it);
	}
}
