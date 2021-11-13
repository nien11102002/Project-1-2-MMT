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

public:
	Player(string name, long vic, long los) {
		this->name = name;
		this->win = vic;
		this->loss = los;
	}

	string Name() { return name; }
	long Win() { return win; }
	long Loss() { return loss; }

	Player() {
		name = "";
		win = 0;
		loss = 0;
	}

	string ToString() {
		stringstream builder;
		builder << name << "\n" << "Win: " << win << "\tLoss: " << loss;
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

	Account(string acc_name, int encrypt, string password) {
		this->account_name = acc_name;
		this->encrypted = encrypt;
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
void Display(unordered_map<Account*, Player*> hashmap);
#endif