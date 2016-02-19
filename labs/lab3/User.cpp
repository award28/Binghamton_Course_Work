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

    if(password == this->password) {
            cout << "Password is correct" << endl;
            loggedIn = true;
    }
    else {
            cout << "Password is incorrect" << endl;
    } 
    
    return loggedIn;
}

string User::getUsername() {
    return this->username;
}

void User::setPassword(string new_password) {
    this->password = new_password;
}

string * User::movieList() {
 return favoriteMovie;
}

//Creates a name and age for the user
void create(User &user) {
	cout << "Please enter first name: ";
	cin >> user.firstName;
	cout << endl;
	cout << "Please enter last name: ";
	cin >> user.lastName;
	cout << endl;
	cout << "Please enter age: ";
	cin >> user.age;
	cout << endl << endl;

}

//Updates specified attribute first, last or age 
void update(User &user) {
	string choice;
	
	cout << "Please enter which attribute to update (First, Last, Age): ";
	cin >> choice;
	cout << endl;	
	if(choice == "First") {
		cout << "Please enter the new value: ";
		cin >> user.firstName;
		cout << endl;	
	}
	else if(choice == "Last") {
		cout << "Please enter the new value: ";
		cin >> user.lastName;
		cout << endl;	
	}
	else if(choice == "Age") {
		cout << "Please enter the new value: ";
		cin >> user.age;
		cout << endl;	
	}
	else {
		cout << "INVALID COMMAND" << endl;
		cout << endl;	
	}	
	cout << endl;	
}

//View the current information the user has entered
void view(User &user) {
	cout << "First name:" << user.firstName << endl;
	cout << "Last name:" << user.lastName << endl;
	cout << "Age:" << user.age << endl;
	cout << "Favorite Movies" << endl << endl;;

	for(int i = 0; i <= sizeof(user.favoriteMovie[0])/sizeof(user.favoriteMovie); i++) {
		cout << user.favoriteMovie[i] << endl;
	}	
	cout << endl;	
}

//Input user's top 5 favorite movies
void favorites(User &user) {
	cout << "Please input your new 5 Favorite Movies" << endl;
	cin.ignore(256, '\n');

	for(int i = 0; i < 5; i++) {
		getline(cin, user.favoriteMovie[i]);
	}	
	cout << endl;	
}
