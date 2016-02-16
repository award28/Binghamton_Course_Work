#include <iostream>
#include "User.h"
using namespace std;

int main() {
	User *u1 = new User();
	bool quit = false;
	string choice = "";

	while(!quit) {
		cout << "Please enter a command (Create, Update, View, Favorites, or Quit): ";
		cin >> choice;
		
		if(choice == "Create") {
			u1->create(*u1);
		}
		else if(choice == "Update") {
			u1->update(*u1);
		}
		else if(choice == "View") {
			u1->view(*u1);
		}
		else if(choice == "Favorites") {
			u1->favorites(*u1);
		}
		else if(choice == "Quit") {
			quit = true;
		}
		else {
			cout << "INVALID COMMAND" << endl;
		}
	}	
}
