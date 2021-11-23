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
	system("cls");
	cout << "Welcome to BattleShip Online.\n";
	cout<<user.ToString();
	// làm các hàm check user sau khi login tại đây.
	cout << "What do you want to do?" << endl;
	cout << "1. Check the status of other players: check_user [-option] [username]" << endl;
	cout << "2. Change your personal information: setup_info [-option] [element]" << endl;
	cout << "NOTE: If you need help, just type: /help [funciton]" << endl << endl;
	string gura;
	int flag = 0;
	do{	
		if(get_gura(gura) == 0 && flag != 0) 
			cout << "Function unrecognized! Please re-enter";
		else cout << "Your choice: "; 
		cin >> gura;
		flag++;
	} while (get_gura(gura) == 0);
	
	switch (get_gura(gura))
	{
	case 1:
		check_user_menu(hashmap, gura);
		break;
	case 2:
		setup_info_menu(hashmap, gura, account);
		break;
	case 3:
		show_help_checkuser();
		break;
	case 4:
		show_help_setup();
		break;
	case -1:
		cout << "Quitting";
		break;
	default:
		break;
	}
	flag = 0;
}
//hàm lấy lựa chọn từ người dùng nhập ở trên
int get_gura(string input){
	const regex quit_pattern("[Qq][Uu][Ii][Tt]");
	if(regex_match(input, quit_pattern)) return -1;
	string gura_choice = input.substr(0, input.find_first_of(' '));
	if(gura_choice == "check_user") return 1;
	else if(gura_choice == "setup_info") return 2;
	else if(gura_choice == "/help"){
		string function_string = input.substr(input.find_first_of(' ') + 1, input.size() - (input.find_first_of(' ') + 1));
		if(function_string == "check_user") return 3;
		else if(function_string == "setup_info") return 4;
	}
	return 0;
}
// 2 hàm xuất ra bảng menu
void show_help_checkuser(){
	cout << "=== Checking the status of another player ===" << endl;
	cout << "Choose one(1) of the option below:" << endl;
	cout << "1. Find: -find" << endl;
	cout << "2. Check online status: -online" << endl;
	cout << "3. Show b-day: -show_date" << endl;
	cout << "4. Show fullname: -show_fullname" << endl;
	cout << "5. Show note: -show_note" << endl;
	cout << "6. Show all information: -show_all" << endl;
	cout << "7. Show point: -show_point" << endl;
}

void show_help_setup(){
	cout << "=== Change your personal information ===" << endl;
	cout << "Choose one(1) of the option below:" << endl;
	cout << "1. Change your fullname: -fullname" << endl;
	cout << "2. Change your date of birth: -date" << endl;
	cout << "3. Change your note: -note" << endl;
}

//hàm check_user
void check_user_menu(unordered_map<Account*, Player*>& hashmap, string opt){	
	int option = getoption(opt);
	string username = getname(opt);
	dispatch(hashmap, option, username);
}


// 2 hàm trích lựa chọn từ chuỗi người dùng nhập và chuyển thành lựa chọn
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

// hàm dispatch đưa lựa chọn đến các option khác nhau
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
		show_Note(hashmap, username);
		break;
	case show_all:
		show_All(hashmap, username);
		break;
	case show_point:
		show_Point(hashmap, username);
		break;
	default:
		break;
	}
}

// các hàm con
bool find_Name(unordered_map<Account*, Player*> &hashmap, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username) return true;		
	return false;
}

bool check_Online(unordered_map<Account*, Player*> &hashmap, string username){
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
			cout << "Player " << username << "'s note: " << it->second->getNote();
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

void setup_info_menu(unordered_map<Account*, Player*>& hashmap, string opt_setup, string username){
	int option = getoption_setup(opt_setup);
	string element = getelement_setup(opt_setup);
	dispatch_setup(hashmap, option, element, username);
}


//hàm lấy lựa chọn từ chuỗi người dùng như trên
int getoption_setup(string opt){
	const string opt1 = "fullname";
	const string opt2 = "date";
	const string opt3 = "note";
	regex option_pattern("-(\\w+)");
	smatch match;
	string option_string;
	regex_search(opt, match, option_pattern);
	option_string = match[1];
	if(option_string == opt1) return 1;
	else if(option_string == opt2) return 2;
	else if(option_string == opt3) return 3;
	else return 0;
}

//hàm lấy nội dung thay đổi 
string getelement_setup(string opt){
	string element_string;
	smatch match;
	regex user_pattern("\\s(\\w+(\\s?\\w+)*)");
	regex_search(opt,match,user_pattern);
	element_string = match[1];
	return element_string;
}

// hàm dispatch như trên
void dispatch_setup(unordered_map<Account*, Player*> &hashmap, int option, string element, string username){
	const int change_fullname = 1;
	const int change_dob = 2;
	const int change_note = 3;
	switch (option)
	{
	case change_fullname:
		change_Fullname(hashmap, option, element, username);
		break;
	case change_dob:
		change_Dob(hashmap, option, element, username);
		break;
	case change_note:
		change_Note(hashmap, option, element, username);
		break;
	default:
		break;
	}
}

//các hàm con
void change_Fullname(unordered_map<Account*, Player*> &hashmap, int option, string element, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username){
			it->second->setName(element);
			cout << "Name of player " << username << " has been changed to" << it->second->Name();
		}	
}

void change_Dob(unordered_map<Account*, Player*> &hashmap, int option, string element, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username){
			it->second->setBirthday(element);
			cout << "Birthday of player " << username << " has been changed to" << it->second->Name();
		}
}

void change_Note(unordered_map<Account*, Player*> &hashmap, int option, string element, string username){
	for (auto it = hashmap.begin(); it != hashmap.end(); it++) 
		if (it->first->Account_name() == username){
			it->second->setBirthday(element);
			cout << "Birthday of player " << username << " has been changed to" << it->second->Name();
		}
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
