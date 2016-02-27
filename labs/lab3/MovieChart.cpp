#include "MovieChart.h"
#include <iostream>
using namespace std;

bool MovieChart::login() {
    string username, password;
    bool loggedIn = false;

    cout << "Please enter your username: ";
    cin >> username;
    cout << username << endl;
    cout << "Please enter your password: ";
    cin >> password;
    cout << password << endl;
    for(int i = 0; i < num_users && !loggedIn; i++) {
        if(username == users[i]->getUsername()) {
            if(users[i]->authenticate(password)) {
                current_user = users[i];
                loggedIn = true;
            }
        }
    }
    if(!loggedIn) cout << "Invalid username/password combination" << endl;

    return loggedIn;
}

void MovieChart::create() {
    string fname;
    string lname;
    int age;
    string username;
    string password;

    cout << "Please enter first name: ";
    cin >> fname;
    cout << fname << endl;
    cout << "Please enter last name: ";
    cin >> lname;
    cout << lname << endl;
    cout << "Please enter age: ";
    cin >> age;
    cout << age << endl;
    cout << "Please enter username: ";
    cin >> username;
    cout << username << endl;
    cout << "Please enter password: ";
    cin >> password;
    cout << password << endl;

    users[num_users] = new User(fname, lname, age, username, password);
    num_users++;
}

void MovieChart::update() {
    string choice;
    string password;
    
    if(current_user == NULL) cout << "Please login before continuing." << endl;
    else {
        cout << "Please enter which attribute to update (Password, Favorites): ";
        cin >> choice;
        cout << choice << endl;
        if(current_user == NULL) cout << "Please login before continuing." << endl;
        else if(choice == "Password") {
            cout << "Please input your new password" << endl;
            cin >> password;
            cout << password << endl;
            current_user->setPassword(password);
        }
        else if(choice == "Favorites") {
            cout << "Please input your new 5 Favorite Movies"  << endl;
            string* list = current_user->movieList();
            cin.ignore(256, '\n');
            for(int i = 0; i < 5; i++) {
                getline(cin, list[i]);
            }
            cout << endl;
            for(int i = 0; i < 5; i++) {
                cout << list[i] << endl;
            }
        }
        else cout << "INVALID COMMAND" << endl;
    }
}

void MovieChart::view() {
    if(current_user == NULL) cout << "Please login before continuing." << endl;
    else {
        cout << "First name:" << current_user->firstName << endl;
        cout << "Last name:" << current_user->lastName << endl;
        cout << "Age:" << current_user->age << endl;
        cout << "Username:" << current_user->getUsername()  << endl;
        cout << "Favorite Movies" << endl << endl;
        
        string* list = current_user->movieList();
        for(int i = 0; i < 5; i++) {
               cout << list[i] << endl; 
        }
    }
}
