#include"DataCore.h"
void Readfile(unordered_map<Account*, Player*>& hashmap, fstream& jav, fstream& editor) {
	while (!(jav.eof() && editor.eof())) {
		string name_acc, password, player_name, DOB;
		int victory = 0, loss = 0, enflag = 0;

		getline(editor, name_acc); getline(jav, player_name);
		getline(jav, DOB);

		editor >> enflag; jav >> victory;

		editor.ignore();

		getline(editor, password); jav >> loss;

		editor.ignore(); jav.ignore(); jav.ignore();

		hashmap.insert(make_pair(new Account(name_acc,enflag,password), 
			new Player(player_name,victory,loss,DOB)));
	}
}

void Display(unordered_map<Account*, Player*> hashmap) {
	unordered_map<Account*, Player*>::iterator itr;
	cout << "\nAll Elements : \n";
	for (itr = hashmap.begin(); itr != hashmap.end(); itr++){
		cout << itr->first->ToString() << " " << itr->second->ToString() << endl << endl;
	}
}