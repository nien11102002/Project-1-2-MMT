#include"Game.h"
void Read(ifstream& file, vector<vector<char>>& stat1, vector<vector<char>>& stat2) {
	file.open("tablecloth.txt", ios::out);
	if (!file.is_open())
		cerr << "Error" << endl;
	else
		ReadData(file, stat1);
	file.close();

	file.open("tablecloth 2.txt", ios::out);
	if (!file.is_open())
		cerr << "Error" << endl;
	else
		ReadData(file, stat2);
	file.close();
}