#include"DataCore.h"

void ChangePass(unordered_map<Account*, Player*>& hashmap) {
	string str, str2;
	bool check = true;
	int flag;

	do {
		cout << "Account: ";
		getline(cin, str);

		for (auto ptr = hashmap.begin(); ptr != hashmap.end(); ptr++)
			if (ptr->first->Account_name() == str) {
				cout << "New Password: ";
				getline(cin, str);
				cout << "Confirm your new password: ";
				getline(cin, str2);
				while (str != str2) {
					cout << "Error! Do not match. Please confirm your new password: ";
					getline(cin, str2);
				}

				char sign;
				cout << "Do you want to encrypt your password?(Y/N): ";
				cin >> sign;

				if (sign == 'y' || sign == 'Y')
					flag = 1;
				else
					flag = 0;

				cout << "Your password has been changed successfully.\n";
				ptr->first->setPassword(str,flag);
				check = false;
				cin.ignore();
			}

	} while (check);
	
}