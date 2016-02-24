#include "MovieChart.h"
#include <iostream>
using namespace std;

MovieChart::MovieChart() {
     users = new User::users[255];
     num_users = 0;
     current_user = NULL;
}

bool MovieChart::login() {
    string username, password;
    bool loggedIn = false;

    cout << "Please enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;

    for(int i = 0; i < 255 && !loggedIn; i++) {
        if(username == users[i]->username) {
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
    cout << "Please enter last name: ";
    cin >> lname;
    cout << "Please enter age: ";
    cin >> age;
    cout << "Please enter username: ";
    cin >> username;
    cout << "Please enter password ";
    cin >> password;

    users[num_users] = new User(fname, lname, age, username, password);
    num_users++;
}

void update() {
    string choice;
    string password;
    string movies[5];

    cout << "Please enter which attribute to update (Password, Favorites): ";
    cin >> choice;

    if(current_user == NULL) cout << "Please login before continuing" << endl;
    else if(choice == "Password") {
        cout << "Please input your new password" << endl;
        cin >> password;
        current_user->setPassword(password);
    }
    else if(choice == "Favorites") {
        cout << "Please input your new 5 Favorite Movies"  << endl;
        movies = current_user->*movieList();
        cout << endl;

        for(int i = 0; i < 5; i++) cout << 
    }
    else cout << "INVALID COMMAND" << endl;
}

void view() {
    cout << "First name:" << current_user->firstName << endl;
    cout << "Last name:" << current_user->lastName << endl;
    cout << "Age:" << current_user->age << endl;
    cout << "Username:" << current_user->username  << endl;
    cout << "Favorite Movies" << endl;

    for(int i = 0; i < 5; i++) {
           cout << current_user->*favoriteMovie[i] << endl; 
    }
}
