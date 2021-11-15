void DataOperation() {// Hàm để chạy DataBase, để tạm thời, nếu muốn chạy thì cứ dán vô 
	// project mới và include file DataCore.h để chạy, chừa hàm main để xây dựng Server và Client.
	// Note từ Mạnh Hùng 13-11-2021.

	fstream editor, jav;
	unordered_map<Account*, Player*> hashmap;

	editor.open("Acc and Pass.txt", ios::in);
	jav.open("Player.txt", ios::in);
		

	if (!editor.is_open() && !jav.is_open()) {
		cerr << "Can't open file.\n";
		return 0;
	}
	else {
		Readfile(hashmap, jav, editor);
	}
	
	jav.close(); editor.close();
	string command;

	do {
		cout << ">> ";
		getline(cin, command);
		
		if (command == "log in")
			Login(hashmap);
		else if (command == "change password")
			ChangePass(hashmap);
		else if (command == "register") {

		}
		else if (command == "log out") {
			cout << "Bye bye! Have a nice day.\n";
			break;
		}
		else
			cout << "Not match any results. Please enter again.\n" << endl;

	} while (true);
}
