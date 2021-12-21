#include "MyClient.h"
void ReadMap(ifstream& file, vector<vector<char>>& map1)
{
	string line;
	while (getline(file, line)) {
		vector<char>tempest;
		for (int i = 0; i < line.size(); i++)
			tempest.push_back(line[i]);
		map1.push_back(tempest);
	}
}

void ReadData(ifstream& file, vector<vector<char>>& stat)
{
	string line;
	while (getline(file, line)) {
		vector<char>tempest;
		for (int i = 0; i < line.size(); i++)
			tempest.push_back(line[i]);
		stat.push_back(tempest);
	}
}



void PrintPlayBoard(vector<vector<char>> cloth, vector<vector<char>> map)
{
	cout << setfill(' ') << setw(25) << right << "Your Field" << setfill(' ') << setw(50) << "Enemy's Field" << endl;

	cout << setw(4) << 1;
	for (int i = 2; i <= 15; i++)
		cout << setw(3) << i;
	cout << setw(6) << " || ";
	cout << setw(4) << 1;
	for (int i = 2; i <= 15; i++)
		cout << setw(3) << i;
	cout << endl;
	for (int i = 0; i < 15; i++)
	{
		cout << left << setw(3) << i + 1;
		for (int j = 0; j < 15; j++)
			cout << setw(3) << map[i][j];
		cout << " || ";
		cout << left << setw(3) << i + 1;
		for (int j = 0; j < 15; j++)
			cout << setw(3) << cloth[i][j];
		cout << endl;
	}
}