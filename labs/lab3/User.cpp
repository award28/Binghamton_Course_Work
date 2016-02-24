#include "User.h"
#include <iostream>
using namespace std;

User::User(string fname, string lname, int age, string username, string password) {
    this->firstName = fname;
    this->lastName = lname;
    this->age = age;
    this->username = username;
    this->password = password;
}    

bool User::authenticate(string password) {
    bool loggedIn = false;

    if(password == this->password) loggedIn = true;
    
    return loggedIn;
}

string User::getUsername() {
    return this->username;
}

void User::setPassword(string new_password) {
    this->password = new_password;
}

string * User::movieList() {
	cout << "Please input your new 5 Favorite Movies" << endl;
	cin.ignore(256, '\n');

	for(int i = 0; i < 5; i++) {
		getline(cin, user.favoriteMovie[i]);
	}	
	cout << endl;	

	for(int i = 0; i <= sizeof(user.favoriteMovie[0])/sizeof(user.favoriteMovie); i++) {
		cout << user.favoriteMovie[i] << endl;
	}	
	cout << endl;	

    return this->favoriteMovie;
}
