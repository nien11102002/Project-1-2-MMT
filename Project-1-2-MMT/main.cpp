#include"Game.h"

int main() {
	char rep1, rep2;
	string Directive;
	do {
		ifstream file;
		vector<vector<char>> map1, map2, stat1, stat2;

		file.open("map.txt", ios::out);
		if (!file.is_open())
			cerr << "Error" << endl;
		else
			ReadMap(file, map1, map2);
		file.close();

		Read(file, stat1, stat2);

		RunGame(map1, map2, stat1, stat2,Directive);

		cout << "Continue?(Y/N)\n";
		cin >> rep1;
		cin >> rep2;
		rep1 = toupper(rep1);
		rep2 = toupper(rep2);

	} while (rep1 == 'Y' && rep2 == 'Y');


	return 0;
}
