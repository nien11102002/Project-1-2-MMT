#include"Game.h"
int x[4] = { -1, 0, 1, 0 };
int y[4] = { 0, 1, 0, -1 };

int Random() {
	srand((unsigned)time(0));
	int randomNumber = rand() % 2 + 1;
	return randomNumber;
}

void RunGame(vector<vector<char>>& map1, vector<vector<char>>& map2,
	vector<vector<char>>& stat1, vector<vector<char>>& stat2,string Directive) {
	int number = Random();

	cout << "\nPlayer #" << number << " go first.\n";
	do {
		bool flag = true;

		if (number == 1)
		{
			int temp = number + 1;
			do {
				cout << "\nPlayer #" << number << " turn.\n";
				Attack(map1, stat1, stat2, flag, number,Directive);
			} while (flag);

			flag = true;

			do {
				cout << "\nPlayer #" << temp << " turn.\n";
				Attack(map2, stat2, stat1, flag, temp,Directive);
			} while (flag);
		}

		if (number == 2)
		{
			int temp = number - 1;
			do {
				cout << "\nPlayer #" << number << " turn.\n";
				Attack(map2, stat2, stat1, flag, number,Directive);
			} while (flag);

			flag = true;

			do {
				cout << "\nPlayer #" << temp << " turn.\n";
				Attack(map1, stat1, stat2, flag, temp,Directive);
			} while (flag);
		}

	} while (!game_over);
}

void Attack(vector<vector<char>>& map, vector<vector<char>>& allystat,
	vector<vector<char>>& enemystat, bool& flag, int player, string Directive)
{
	PrintPlayBoard(map, enemystat);

	cout << ">>";
	getline(cin, Directive);
	int a = Directive.find_last_of(" ") - Directive.find_first_of(" ")-1;
	int x = stoi(Directive.substr(12,a ));
	int y = stoi(Directive.substr(13 + a, Directive.size() - Directive.find_last_of(" ") - 1));
	x--; y--;
	if (x < 1 || x > 20 || y < 1 || y > 20 || enemystat[x][y] == 'o')
	{
		cout << "Stat is not available. Re-input: " << endl;
		getline(cin, Directive);
		return;
	}
	
	if (enemystat[x][y] == 'x') {
		cout << "\n\nYou have hit enemy  ship.\n";
		enemystat[x][y] = 'o';
		map[x][y] = 'O';
		int army = count(enemystat);
		if (army < quantity)
			cout << "\nYou have destroy" << quantity - army << " enemy ship(s).\n";
		if (army == 0) {
			cout << "Game over! Player #" << player << " win the game." << endl;
			game_over = true;
		}

	}
	else
	{
		cout << "Miss the target.\n";
		map[x][y] = 'X';
		enemystat[x][y] = '~';
		flag = false;
	}
}

int count(vector<vector<char>>enemystat) {
	int count = 0;
	vector<vector<bool>> visited(20, vector<bool>(20, false));


	for (int i = 0; i < enemystat.size(); i++)
	{
		for (int j = 0; j < enemystat[i].size(); j++)
			if (enemystat[i][j] == 'x' && !visited[i][j])
			{
				count++;
				DFS(enemystat, i, j, enemystat.size(), visited);
			}
	}

	return count;
}

void DFS(vector<vector<char>>enemystat, int i, int j, int n, vector<vector<bool>>& visited)
{
	if (i < 0 || j < 0 || i > n - 1 || j > n - 1 || visited[i][j] || enemystat[i][j] == '*' || enemystat[i][j] == 'o')
		return;
	visited[i][j] = true;
	for (int k = 0; k < 4; k++)
		DFS(enemystat, i + x[k], j + y[k], n, visited);
}
