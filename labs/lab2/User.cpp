#include "User.h"
#include <iostream>
using namespace std;

void User::test() {
	cout << "test" << endl;
}

void User::create(User &user) {
	cout << "Please enter first name: ";
	cin >> user.firstName;
	cout << "Please enter last name: ";
	cin >> user.lastName;
	cout << "Please enter age: ";
	cin >> user.age;
}
void User::update(User &user) {
	string choice;
	
	cout << "Enter which attribute to update (First, Last, Age): ";
	cin >> choice;
	
	if(choice == "First") {
		cout << "Please enter the new value: ";
		cin >> user.firstName;
	}
	else if(choice == "Last") {
		cout << "Please enter the new value: ";
		cin >> user.lastName;
	}
	else if(choice == "Age") {
		cout << "Please enter the new value: ";
		cin >> user.age;
	}
	else {
		cout << "INVALID COMMAND" << endl;
	}		
}
void User::view(User &user) {
	cout << "First name: " << user.firstName << endl;
	cout << "Last name: " << user.lastName << endl;
	cout << "Age: " << user.age << endl;
	cout << "Favorite movies:" << endl;

	for(int i = 0; i <= sizeof(user.favoriteMovie[0])/sizeof(user.favoriteMovie); i++) {
		cout << user.favoriteMovie[i] << endl;
	}	
}
void User::favorites(User &user) {
	cout << "Please input your new 5 Favorite Movies" << endl;
	for(int i = 0; i <= sizeof(user.favoriteMovie[0])/sizeof(user.favoriteMovie); i++) {
		cout << "Enter #" << i+1 << " here: ";
		cin >> user.favoriteMovie[i];
	}	
}
