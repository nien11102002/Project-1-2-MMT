#include"DataCore.h"

void WriteFile(unordered_map<Account*, Player*> hashmap, fstream& jav, fstream& editor) {
	editor.open("Acc and Pass.txt", ios::out);
	jav.open("Player.txt", ios::out);


	if (!editor.is_open() && !jav.is_open()) {
		cerr << "Can't open file.\n";
		jav.close(); editor.close();
		return;
	}
	else {
		for (auto it = hashmap.begin(); it != hashmap.end(); it++)
		{
			editor << it->first->Account_name() << endl;
			editor << it->first->encryption() << endl;
			editor << it->first->Pass() << endl << endl;

			jav << it->second->Name() << endl;
			jav << it->second->Birthday() << endl;
			jav << it->second->Win() << endl;
			jav << it->second->Loss() << endl << endl;
		}
	}
}


void CleanHashmap(unordered_map<Account*, Player*>& hashmap) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++)
	{
		delete it->first; 
		delete it->second;
		hashmap.erase(it);
	}
}