#ifndef DATACORE_H
#define DATACORE_H

#include<iostream>
#include<fstream>
#include<map>
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
	void setName(string str) { name = str; }
	void setWin(long victory) { win = victory; }
	void setLoss(long defeat) { loss = defeat; }

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

	void setEnNum(int num) { encrypted = num; }
	int encryption() { return encrypted; }

	void setName(string acc) {account_name = acc;}
	string Account_name() { return account_name; }


	void EncryptPass(const string &in) {
		string temp;
		if (encrypted != 0) {
			for (int i = 0; i < in.length(); i++)
				temp += in[i] + 3;
			pass = temp;
		}
		else
			pass = in;
	}

	string Pass() { return pass; }

	string ToString() {
		string result;
		if (encrypted == 1) {
			for (int i = 0; i < pass.length(); i++)
				result += pass[i] - 3;
		}
		else
			result = pass;
		stringstream todo;
		todo << "Acc name: " << account_name << ", Password: " << result;
		return todo.str();
	}
};

void Readfile(map<Account, Player>& hashmap, fstream& jav, fstream& editor);
void Display(map<Account, Player> mp);
#endif