#include"Game.h"

int main() {
	ifstream file;
	vector<vector<char>> map1, map2, stat1,stat2;
	file.open("map.txt", ios::out);
	if (!file.is_open())
		cerr << "Error" << endl;
	else
		ReadMap(file, map1, map2);
	file.close();

	Read(file, stat1, stat2);

	cout << "Map Client 1:\n";
	PrintMap(map1);
	cout << "\nMap Client 2:\n";
	PrintMap(map2);

	cout << "\nTable cloth 1:\n";
	PrintTableCloth(stat1);
	cout << "\nTable cloth 2:\n";
	PrintTableCloth(stat2);

	return 0;
}