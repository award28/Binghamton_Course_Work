#include "MovieChart.h"
#include <iostream>
#include <fstream>
using namespace std;

MovieChart::MovieChart() {
    string username, first, last, password, movie;
    int age;
    ifstream fin;
    
    fin.open("users.txt");
    if(fin.good()) {
        while(!fin.eof()) {
            LinkedList<string> *movies = new LinkedList<string>();
            fin >> username;
            fin >> first;
            fin >> last;
            fin >> age;
            fin >> password;

            fin.ignore(1000, '\n');
            getline(fin, movie);
            while(movie != "" && movie != "\n") {
                movies->insert(movie);
                getline(fin, movie);
            }
            users->insert(User(first, last, age, username, password, movies));
        }
    }
    fin.close();
}

MovieChart::~MovieChart() {
    ofstream fout;
    User *user;
    LinkedList<string> *tempMovies;
    fout.open("User.txt");
    if(fout.good()) {
        users->reset();
        while(users->get()){
            user = users->get();
            fout << user->getUsername() << endl;
            fout << user->firstName << endl;
            fout << user->lastName << endl;
            fout << user->age << endl;
            fout << user->password << endl;
            tempMovies = new LinkedList<string>(user->movieList());
            tempMovies->reset();
            fout << *tempMovies->get() << endl;
            while(tempMovies->next()) fout << *tempMovies->get() << endl;
            users->next();
            if(users->get()) fout << endl;
        }
        delete tempMovies;    
    }
    delete users;
    fout.close();
}

bool MovieChart::login() {
    string username, password;
    bool loggedIn = false;
    users->reset();
    cout << "Please enter your username: ";
    cin >> username;
    cout << username << endl;
    cout << "Please enter your password: ";
    cin >> password;
    cout << password << endl;
    while(users->get()) {
        if(username == users->get()->getUsername()) {
            if(users->get()->authenticate(password)) {
                current_user = users->get();
                loggedIn = true;
            }
        }
        users->next();
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
    LinkedList<string> *temp = new LinkedList<string>();
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

    users->insert(User(fname, lname, age, username, password, temp));
}

void MovieChart::update() {
    string choice;
    string password;
    
    if(current_user == NULL) cout << "Please login before continuing." << endl;
    else {
        cout << "Please enter which attribute to update (Add, Remove, Password): ";
        cin >> choice;
        cout << choice << endl;
        if(choice == "Password") {
            cout << "Please input your new password" << endl;
            cin >> password;
            cout << password << endl;
            current_user->setPassword(password);
        }
        else if(choice == "Remove") {
            cout << "Please input your Favorite Movies (Quit to exit)"  << endl;
            cin.ignore(256, '\n');
            getline(cin, choice);
            while(choice != "Quit") {
                current_user->removeMovie(choice);
                getline(cin, choice);
                cout << choice;
                cout << endl;
            }
        }
         else if(choice == "Add") {
            cout << "Please input your Favorite Movies (Quit to exit)"  << endl;
            cin.ignore(256, '\n');
            getline(cin, choice);
            while(choice != "Quit") {
                current_user->addMovie(choice);
                getline(cin, choice);
                cout << choice;
                cout << endl;
            }
        }
        else cout << "INVALID COMMAND" << endl;
    }
}

void MovieChart::view() {
    LinkedList<string>* tempMovies;
    if(current_user == NULL) cout << "Please login before continuing." << endl;
    else {
        cout << "First name:" << current_user->firstName << endl;
        cout << "Last name:" << current_user->lastName << endl;
        cout << "Age:" << current_user->age << endl;
        cout << "Username:" << current_user->getUsername()  << endl;
        cout << "Favorite Movies" << endl << endl;
        tempMovies = new LinkedList<string>(current_user->movieList());
        tempMovies->reset();
        cout << *tempMovies->get() << endl;
        while(tempMovies->next()) cout << *tempMovies->get() << endl;
    }
}
}
void MovieChart::close() {
    if(current_user == NULL) cout << "Please login before continuing." << endl;
    else {
        users->reset();
        while(current_user != users->get()){users->next();}
        users->remove();
    }
}

void MovieChart::list() {
    users->reset();
    User* user = users->get();
    while(user != NULL) {
        LinkedList<string>* tempMovies;
        tempMovies = new LinkedList<string>(user->movieList());
        cout << "Username:" << user->getUsername()  << endl;
        cout << "Favorite Movies" << endl << endl;
        tempMovies->reset();
        cout << *tempMovies->get() << endl;
        while(tempMovies->next()) cout << *tempMovies->get() << endl;
        cout << endl;
        users->next();
        user = users->get();
    }
}
