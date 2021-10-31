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

void ReadData1(ifstream& file, vector<vector<char>>& stat1) {
	string line;
	while (getline(file, line)) {
		vector<char>tempest;
		for (int i = 0; i < line.size(); i++)
			tempest.push_back(line[i]);
		stat1.push_back(tempest);
	}
}

void ReadData2(ifstream& file, vector<vector<char>>& stat2) {
	string line;
	while (getline(file, line)) {
		vector<char>tempest;
		for (int i = 0; i < line.size(); i++)
			tempest.push_back(line[i]);
		stat2.push_back(tempest);
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
