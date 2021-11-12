#include"DataCore.h"

int main() {
	fstream editor, jav;
	editor.open("Acc and Pass.txt", ios::in);
	jav.open("Player data.txt", ios::in);
	map<Account, Player> hashmap;
	if (!editor.is_open() && !jav.is_open()) {
		cerr << "Can't open file.\n";
		return 0;
	}
	else {
		Readfile(hashmap, jav, editor);
		jav.close();
		editor.close();
	}
		

	return 0;
}