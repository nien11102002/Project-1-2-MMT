#ifndef DATACORE_H
#define DATACORE_H

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

class Player {
private:
	string name;
	long win;
	long loss;
	bool online;
	string DOB;

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

	string Name() { return name; }
	long Win() { return win; }
	long Loss() { return loss; }
	string Birthday() { return DOB; }

	Player() {
		name = "";
		DOB = "";
		win = 0;
		loss = 0;
		online = false;
	}

	string ToString() {
		stringstream builder;
		builder << name << "\n" << "Win: " << win << "\tLoss: " << loss << "\n";
		builder << "Birthday: " << DOB << endl;
		string onl = (online == true) ? "Online.\n" : "Offline.\n";
		builder << "Status: " << onl;
		string stream =  builder.str();
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

void Readfile(unordered_map<Account*, Player*>& hashmap, fstream& jav, fstream& editor);
void Login(unordered_map<Account*, Player*> hashmap);
bool isMatch(unordered_map<Account*, Player*>& hashmap, string account, string password, Player& user);
#endif