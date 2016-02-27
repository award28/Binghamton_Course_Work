#include <iostream>
#include "User.h"
using namespace std;

int main() {
	User *u1 = new User();
	bool quit = false;
	string choice = "";
    cout << endl; 
	
    while(!quit) {
		cout << "Please enter a command (Create, Update, View, Favorites, or Quit):";
		cin >> choice;
	    cout << endl;

		if(choice == "Create") {
			create(*u1);
		}
		else if(choice == "Update") {
			update(*u1);
		}
		else if(choice == "View") {
			view(*u1);
		}
		else if(choice == "Favorites") {
			favorites(*u1);
			view(*u1);
		}
		else if(choice == "Quit") {
			quit = true;
		}
		else {
			cout << "INVALID COMMAND" << endl << endl;
		}
	}	
}
