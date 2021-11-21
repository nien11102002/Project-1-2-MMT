﻿#include"DataCore.h"

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
	check_user_menu(hashmap);
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
		if(isValid_getline(opt))
			getline(cin, opt);
		else{
		if(getoption(opt) == 0){
			cout << "Error: invalid option! Please re-enter:";
			getline(cin, opt);
	}
		else{
			cout << "Wrong input format! Please re-enter:";
			getline(cin, opt);
	}	
	}
	} while(!isValid_getline(opt));
	int option = getoption(opt);
	string username = getname(opt);
	dispatch(hashmap, option, username);
}

bool isValid_getline(string opt){
	bool result = 0;
	regex input_pattern("-(\\w+_?\\w+)\\s(\\w+(\\s?\\w+)*)");
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
	string user_string;
	smatch match;
	regex user_pattern("\\s(\\w+(\\s?\\w+)*)");
	regex_search(opt,match,user_pattern);
	user_string = match[1];
	return user_string;
}




void dispatch(unordered_map<Account*, Player*> &hashmap, int option, string username){
	const int find_name = 1;
	const int check_online = 2;
	const int show_dob = 3;
	const int show_fullname = 4;
	const int show_note = 5;
	const int show_all = 6;
	const int show_point = 7;
	switch (option)
	{
	case find_name:
		if(find_Name(hashmap, username)) cout << "Player " << username << " exists!";
		else cout << "Player " << username << " does not exist!";
		break;
	case check_online:
		if(check_Online(hashmap, username)) cout << "Player " << username << " is online";
		else if(!find_Name(hashmap, username)) cout << "Player " << username << " does not exist!";
		else cout << "Player " <<username << " is not online!";
		break;
	case show_dob:
		show_DOB(hashmap, username);
		break;
	case show_fullname:
		show_Fullname(hashmap, username);
		break;
	case show_note:

		break;
	case show_all:
	
		break;
	case show_point:
	
		break;
	default:
		break;
	}
}

bool find_Name(unordered_map<Account*, Player*> &hashmap, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username) return true;		
	return false;
}

bool check_Online(unordered_map<Account*, Player*> &hashmap, string username) {
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username)
			if(it->second->Online()) return true;		
	return false;
}

void show_DOB(unordered_map<Account*, Player*> &hashmap, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username)
			cout << "Player " << username << "'s date of birth is: " << it->second->Birthday();
	if(!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!";	
}

void show_Fullname(unordered_map<Account*, Player*> &hashmap, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username)
			cout << "Player " << username << "'s fullname is: " << it->second->Name();
	if(!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!";	
}

void show_Note(unordered_map<Account*, Player*> &hashmap, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username)
			cout << "Player " << username << "as no note";
	if(!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!";	
}

void show_All(unordered_map<Account*, Player*> &hashmap, string username){
	cout << "All information about Player: " << username << endl;
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username){
			cout << "Fullname: " << it->second->Name();
			cout << "Status: " << it->second->Online();
			cout << "Date of Birth: " << it->second->Birthday();
			cout << "Win: " << it->second->Win();
			cout << "Loss: " << it->second->Loss();		
		}
	if(!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!";	
}

void show_Point(unordered_map<Account*, Player*> &hashmap, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username)
			cout << "Player " << username << "'s point: W: " << it->second->Win() << " L: " << it->second->Loss();
	if(!find_Name(hashmap, username))
		cout << "Player " << username << " does not exist!";
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
