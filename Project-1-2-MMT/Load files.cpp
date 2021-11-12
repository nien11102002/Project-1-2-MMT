#include"DataCore.h"

void Readfile(map<Account, Player>& hashmap, fstream& jav, fstream& editor) {
	while (!editor.eof() && !jav.eof()) {
		Account info;
		Player pvp;

		string t; int num;

		getline(editor, t);
		info.setName(t);
		editor >> num;
		info.setEnNum(num);
		editor.ignore();
		getline(editor, t);
		info.EncryptPass(t);
		editor.ignore();

		getline(jav, t);
		pvp.setName(t);
		jav >> num;
		pvp.setWin(num);
		jav >> num;
		pvp.setLoss(num);
		jav.ignore();
		jav.ignore();

		hashmap[info] = pvp;
	}
}

void Display(map<Account, Player> hashmap)
{
}
