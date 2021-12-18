#ifndef DATACORE_H
#define DATACORE_H

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<sstream>
#include<string>
#include<vector>
#include<conio.h>
#include<regex>

using namespace std;

class Player {
private:
	string name;
	long win;
	long loss;
	bool online;
	string DOB;
	string Note;
public:

	Player(string name, long vic, long los, string birthday) {
		this->name = name;
		this->win = vic;
		this->loss = los;
		this->online = false;
		this->DOB = birthday;
	}

	void setOnline(bool onl) { online = onl; }
	void setName(string str) { name = str; }
	void setWin(long vic) { win = vic; }
	void setLoss(long def) { loss = def; }
	void setBirthday(string ser) { DOB = ser; }
	void setNote(string note) { Note = note; }

	string Name() { return name; }
	long Win() { return win; }
	long Loss() { return loss; }
	bool Online() { return online; }
	string Birthday() { return DOB; }
	string getNote() { return Note; }

	Player() {
		name = "";
		DOB = "";
		win = 0;
		loss = 0;
		online = false;
		Note = "Hello";
	}

	string ToString() {
		stringstream builder;
		builder << name << "\n" << "Win: " << win << "\tLoss: " << loss << "\n";
		builder << "Birthday: " << DOB << endl;
		string onl = (online == true) ? "Online.\n" : "Offline.\n";
		builder << "Status: " << onl << endl;
		builder << "Note: " << Note << endl;
		string stream = builder.str();
		return stream;
	}
};

class EncodeAndDecode {
public:
	string Encode(string in) {
		string temp;
		for (int i = 0; i < in.length(); i++)
			temp += in[i] + 3;
		return temp;
	}

	string Decode(string out) {
		string temp;
		for (int i = 0; i < out.length(); i++)
			temp += out[i] - 3;
		return temp;
	}
};


class Account {
private:
	string pass;
	int encrypted;
	string account_name;
public:
	Account() {
		pass = "";
		encrypted = 0;
		account_name = "";
	}

	Account(string acc_name, int en, string password) {
		this->account_name = acc_name;
		encrypted = en;
		if (encrypted != 0) {
			EncodeAndDecode vpn;
			this->pass = vpn.Encode(password);
		}
		else
			this->pass = password;
	}

	void setPassword(string secret, int t) {
		encrypted = t;
		if (t != 1)
			pass = secret;
		else {
			EncodeAndDecode vpn;
			pass = vpn.Encode(secret);
		}
	}

	int encryption() { return encrypted; }
	string Account_name() { return account_name; }
	string Pass() {
		string temp;
		if (encrypted != 0) {
			EncodeAndDecode vpn;
			temp = vpn.Decode(pass);
		}
		else
			temp = pass;
		return temp;
	}

	string ToString() {
		stringstream builder;
		builder << account_name << " " << Pass() << endl;
		return builder.str();
	}
};

// hàm nạp dữ liệu từ file.
void LoadData(fstream& editor, fstream& jav, unordered_map<Account*, Player*>& hashmap);
void Readfile(unordered_map<Account*, Player*>& hashmap, fstream& jav, fstream& editor);

//hàm ghi đè dữ liệu.
void WriteFile(unordered_map<Account*, Player*> hashmap, fstream& jav, fstream& editor);
void CleanHashmap(unordered_map<Account*, Player*>& hashmap);

// Login and Register.
bool isMatch(unordered_map<Account*, Player*> hashmap, string account, string password, Player& user);
bool isAvailableUsername(unordered_map<Account*, Player*> hashmap, string S);
void writeAtBottomOfNewOne(Player P, Account A);

#endif