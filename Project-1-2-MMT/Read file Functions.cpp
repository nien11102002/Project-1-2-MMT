#include"Game.h"
void ReadMap(ifstream& file, vector<vector<char>>& map1, vector<vector<char>>& map2) {
	string line;
	while (getline(file, line)) {
		vector<char>tempest;
		for (int i = 0; i < line.size(); i++)
			tempest.push_back(line[i]);
		map1.push_back(tempest);
		map2.push_back(tempest);
	}
}

void ReadData(ifstream& file, vector<vector<char>>& stat) {
	string line;
	while (getline(file, line)) {
		vector<char>tempest;
		for (int i = 0; i < line.size(); i++)
			tempest.push_back(line[i]);
		stat.push_back(tempest);
	}
}


void PrintMap(vector<vector<char>>map) {
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
			cout << map[i][j];
		cout << endl;
	}
}

void PrintTableCloth(vector<vector<char>>stat) {
	for (int i = 0; i < stat.size(); i++)
	{
		for (int j = 0; j < stat[i].size(); j++)
			cout << stat[i][j];
		cout << endl;
	}
}

void PrintPlayBoard(vector<vector<char>> cloth, vector<vector<char>> map)
{
	cout << setw(25) << "Your Field"<<setw(50)<<"Enemy's Field";

	cout << setw(3);
	for (int i = 1; i <= 15; i++)
		cout<< setw(3) << i ;
	cout << " || " << setw(3);
	for (int i = 1; i <= 15; i++)
		cout << setw(3) << i;

	for (int i = 0; i < 15; i++)
	{
		cout << left << setw(5) << i+1;
		for(int j=0;j<15;j++)
			cout << setw(3) << cloth[i][j];
		cout << " || ";
		cout << left << setw(5) << i + 1;
		for (int j = 1; j <= 15; j++)
			cout << setw(3) << map[i][j];
		cout << endl;
	}
}
