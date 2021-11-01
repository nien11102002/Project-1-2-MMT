#include"Game.h"
int x[4] = { -1, 0, 1, 0 };
int y[4] = { 0, 1, 0, -1 };

int Random() {
	srand((unsigned)time(0));
	int randomNumber = rand() % 2 + 1;
	return randomNumber;
}

void RunGame(vector<vector<char>>& map1, vector<vector<char>>& map2, 
vector<vector<char>>& stat1, vector<vector<char>>& stat2) {
	int number = Random();
	
	cout << "\nPlayer #" << number << " go first.\n";
	do {
		bool flag = true;

		if (number == 1) 
		{
			int temp = number + 1;
			do {
				cout << "\nPlayer #" << number << " turn.\n";
				Attack(map1, stat1, stat2, flag, number);
			} while (flag);

			flag = true;

			do {
				cout << "\nPlayer #" << number + 1 << " turn.\n";
				Attack(map2, stat2, stat1, flag, temp);
			} while (flag);
		}

		if(number == 2)
		{
			int temp = number - 1;
			do {
				cout << "\nPlayer #" << number << " turn.\n";
				Attack(map2, stat2, stat1, flag, number);
			} while (flag);

			flag = true;

			do {
				cout << "\nPlayer #" << temp << " turn.\n";
				Attack(map1, stat1, stat2, flag, temp);
			} while (flag);
		}

	} while (!game_over);
}

void Attack(vector<vector<char>>& map, vector<vector<char>>& allystat, 
	vector<vector<char>>& enermystat, bool &flag, int player)
{
	cout << "Map:\n";
	PrintMap(map);
	cout << "\nCrewState:\n";
	PrintTableCloth(allystat);
	int x, y;
	do {
		cout << "Attack at:\n";
		cout << "Row: "; cin >> x;
		cout << "Collum: "; cin >> y;
	} while (x < 1 || x > 20 || y < 1 || y > 20 || enermystat[x][y]=='o');
	x--; y--;

	if (enermystat[x][y] == 'x') {
		cout << "\n\nYou have hit enermy ship.\n";
		enermystat[x][y] = 'o';
		map[x][y] = 'O';
		int army = count(enermystat);
		if (army < quantity)
			cout << "\nYou have destroy" << quantity - army << " enermy ship(s).\n";
		if (army == 0) {
			cout << "Game over! Player #" << player << " win the game." << endl;
			game_over = true;
		}
			
	}
	else
	{
		cout << "Miss the target.\n";
		map[x][y] = 'X';
		enermystat[x][y] = '~';
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
	if (i < 0 || j < 0 || i > n - 1 || j > n - 1 || visited[i][j] || enermystat[i][j] == '*' || enermystat[i][j] == 'o')
		return;
	visited[i][j] = true;
	for (int k = 0; k < 4; k++)
		DFS(enermystat, i + x[k], j + y[k], n, visited);
}