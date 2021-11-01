#include"Game.h"
int x[4] = { -1, 0, 1, 0 };
int y[4] = { 0, 1, 0, -1 };

int Random() {
	srand(time(NULL));
	int number = rand() % 2 + 1;
	return number;
}

void RunGame(vector<vector<char>>& map1, vector<vector<char>>& map2, 
vector<vector<char>>& stat1, vector<vector<char>>& stat2) {
	int number = Random();
	cout << "Player #" << number << " go first.\n";
	bool flag = true;
	if (number == 1) {
		do {
			cout << "Player #" << number << "turn.\n";
			Attack(map1, stat1, stat2, flag);
		} while (flag);
	}
}

void Attack(vector<vector<char>>& map, vector<vector<char>>& allystat, 
	vector<vector<char>>& enermystat, bool &flag)
{
	cout << "Map:\n";
	PrintMap(map);
	cout << "\nCrewState:\n";
	PrintTableCloth(allystat);
	int x, y;
	do {
		cout << "Attack at: ";
		cout << "Row: "; cin >> x;
		cout << "Collum: "; cin >> y;
	} while (x < 1 || x > 20 || y < 1 || y > 20);
	x--; y--;

	if (enermystat[x][y] == 'x') {
		cout << "You have hit enermy ship.\n";
		enermystat[x][y] = 'o';
		map[x][y] = 'O';
		int army = count(enermystat);
		if (army < quantity)
			cout << "You have destroy one enermy ship.\n";
	}
	else
	{
		cout << "Miss the target.\n";
		map[x][y] = 'X';
		flag = false;
	}
}

int count(vector<vector<char>>enermystat) {
	int count = 0;
	vector<vector<bool>> visited(20,vector<bool>(20,false));
	

	for (int i = 0; i < enermystat.size(); i++)
	{
		for (int j = 0; j < enermystat[i].size(); j++)
			if (enermystat[i][j] == 'x' && !visited[i][j])
			{
				count++;
				DFS(enermystat, i, j, enermystat.size(), visited);
			}
	}

	return count;
}

void DFS(vector<vector<char>>enermystat, int i, int j, int n, vector<vector<bool>> &visited)
{
	if (i < 0 || j < 0 || i > n - 1 || j > n - 1 || visited[i][j] || enermystat[i][j] == 0)
		return;
	visited[i][j] = true;
	for (int k = 0; k < 4; k++)
		DFS(enermystat, i + x[k], j + y[k], n, visited);
}