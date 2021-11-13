void DataOperation() {// Hàm để chạy DataBase, để tạm thời, nếu muốn chạy thì cứ dán vô 
	// project mới và include file DataCore.h để chạy, chừa hàm main để xây dựng Server và Client.
	// Note từ Mạnh Hùng 13-11-2021.

	fstream editor, jav;
	editor.open("Acc and Pass.txt", ios::in);
	jav.open("Player.txt", ios::in);

	unordered_map<Account*, Player*> hashmap;

	if (!editor.is_open() && !jav.is_open()) {
		cerr << "Can't open file.\n";
		return 0;
	}
	else {
		Readfile(hashmap, jav, editor);
	}
	Display(hashmap);
}
