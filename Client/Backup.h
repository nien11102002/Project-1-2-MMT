#ifndef BACKUP_H
#define BACKUP_H

#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<iomanip>
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

void show_help_checkuser();
void show_help_setup();


#endif