#include"DataCore.h"

void Login(unordered_map<Account*, Player*> hashmap) {
	string account, password;
	Player user;
	do {
		
		cout << ">>Account: ";
		getline(cin, account);
		cout << ">>Password: ";
		getline(cin, password);
	} while (isMatch(hashmap, account, password, user) != true);
	
	cout << "Welcome to BattleShip Online.\n";
	cout<<user.ToString();
	
	// làm các hàm check user sau khi login tại đây.
}

void check_user_menu(){
	cout << "Checking the status of another character: " << endl;
	cout << "Choose one(1) of the option below:" << endl;
	cout << "1. Find: -find" << endl;
	cout << "2. Check online status: -online" << endl;
	cout << "3. Show b-day: -show_date" << endl;
	cout << "4. Show fullname: -show_fullname" << endl;
	cout << "5. Show note: -show_note" << endl;
	cout << "6. Show all information: -show_all" << endl;
	cout << "7. Show point: -show_point" << endl
	cout << endl << "Answer format should be: ";
}

bool isMatch(unordered_map<Account*, Player*> &hashmap, string account, string password, Player& user) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == account && it->first->Pass() == password) {
			user.setName(it->second->Name());
			user.setBirthday(it->second->Birthday());
			user.setOnline(true);
			user.setWin(it->second->Win());
			user.setLoss(it->second->Loss());

			it->second->setOnline(true);
			return true;
		}
			
	return false;
}
