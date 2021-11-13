void GameOperations() {// Hàm để chạy game, để tạm thời, nếu muốn chạy thì cứ dán vô 
	// project mới và include file Game.h để chạy, chừa hàm main để xây dựng Server và Client.
	// Note từ Mạnh Hùng 13-11-2021.
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

		RunGame(map1, map2, stat1, stat2, Directive);

		cout << "Continue?(Y/N)\n";
		cin >> rep1;
		cin >> rep2;
		rep1 = toupper(rep1);
		rep2 = toupper(rep2);

	} while (rep1 == 'Y' && rep2 == 'Y');
}