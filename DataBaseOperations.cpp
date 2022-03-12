void DataOperation() {// Hàm để chạy DataBase, để tạm thời, nếu muốn chạy thì cứ dán vô 
	// project mới và include file DataCore.h để chạy, chừa hàm main để xây dựng Server và Client.
	// Note từ Mạnh Hùng 13-11-2021. Đồ án thành công 10 điểm.

	fstream editor, jav;
	unordered_map<Account*, Player*> hashmap;

	LoadData(editor, jav, hashmap);
	
	string command;

	do {
		cout << ">> ";
		getline(cin, command);
		
		if (command == "log in")
			Login(hashmap);
		else if (command == "change password")
			ChangePass(hashmap);
		else if (command == "register") {
		    	cout << "> ";
			getline(cin, command);
			Register(hashmap, command);
		}
		else if (command == "log out") {
			cout << "Bye bye! Have a nice day.\n";
			break;
		}
		else
			cout << "Not match any results. Please enter again.\n" << endl;

	} while (true);

}
