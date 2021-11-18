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

void check_user_menu(unordered_map<Account*, Player*>& hashmap){
	cout << "Checking the status of another character: " << endl;
	cout << "Choose one(1) of the option below:" << endl;
	cout << "1. Find: -find" << endl;
	cout << "2. Check online status: -online" << endl;
	cout << "3. Show b-day: -show_date" << endl;
	cout << "4. Show fullname: -show_fullname" << endl;
	cout << "5. Show note: -show_note" << endl;
	cout << "6. Show all information: -show_all" << endl;
	cout << "7. Show point: -show_point" << endl;
	cout << endl << "Answer format should be: check_user [-option] [username]" << endl;
	cout << "Your choice:\n\tcheck_user ";
	string opt = "-NULL NULL";
	do{
	if(isValid_getline(opt)){
		getline(cin, opt);
		int option = getoption(opt);
		string name = getname(opt);
	}
	else{
		if(!isValid_getline(opt))
		cout << "Wrong input format, please re-enter:";
		else if(getoption(opt) == 0)
		cout << "Error: option is invalid! Please re-enter";
	}
	} while(!isValid_getline(opt));
	

}

bool isValid_getline(string opt){
	bool result = 0;
	regex input_pattern("-(\\w+_?\\w+)");
	if(regex_match(opt,input_pattern))
	result = 1;
	return result;
}

int getoption(string opt){
	const string opt1 = "find";
	const string opt2 = "online";
	const string opt3 = "show_date";
	const string opt4 = "show_fullname";
	const string opt5 = "show_note";
	const string opt6 = "show_all";
	const string opt7 = "show_point";
	regex option_pattern("-(\\w+_?\\w+)");
	smatch match;
	string option_string;
	regex_search(opt, match, option_pattern);
	option_string = match[1];
	if(option_string == opt1) return 1;
	else if(option_string == opt2) return 2;
	else if(option_string == opt3) return 3;
	else if(option_string == opt4) return 4;
	else if(option_string == opt5) return 5;
	else if(option_string == opt6) return 6;
	else if(option_string == opt7) return 7;
	else return 0;
}

string getname(string opt){
	string name_string;
	smatch match;
	regex name_pattern("\\s(\\w+\\s?\\w+)");
	regex_search(opt,match,name_pattern);
	name_string = match[1];
	return name_string;
}

bool isValid();

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
