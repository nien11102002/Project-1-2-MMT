#include"Backup.h"
#include"MyClient.h"

void show_help_checkuser() {
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

void show_help_setup() {
	cout << "=== Change your personal information ===" << endl;
	cout << "Choose one(1) of the option below:" << endl;
	cout << "1. Change your fullname: -fullname" << endl;
	cout << "2. Change your date of birth: -date" << endl;
	cout << "3. Change your note: -note" << endl;
}