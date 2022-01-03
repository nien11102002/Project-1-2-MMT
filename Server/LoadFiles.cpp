#include"DataBase.h"
#include"MyServer.h"

void LoadData(fstream& editor, fstream& jav, unordered_map<Account*, Player*>& hashmap) {
	editor.open("Acc and Pass.txt", ios::in);
	jav.open("Player.txt", ios::in);


	if (!editor.is_open() && !jav.is_open()) {
		cerr << "Can't open file.\n";
		jav.close(); editor.close();
		return;
	}
	else
		Readfile(hashmap, jav, editor);
	jav.close(); editor.close();
}

void Readfile(unordered_map<Account*, Player*>& hashmap, fstream& jav, fstream& editor) {
	while (!(jav.eof() && editor.eof())) {
		string name_acc, password, player_name, DOB;
		int victory = 0, loss = 0;

		getline(editor, name_acc); getline(editor, password);
		editor.ignore();
		
		getline(jav, player_name); getline(jav, DOB);
		jav >> victory; jav >> loss;
		jav.ignore(); jav.ignore();

		hashmap.insert(make_pair(new Account(name_acc, password),
			new Player(player_name, victory, loss, DOB)));
	}
}