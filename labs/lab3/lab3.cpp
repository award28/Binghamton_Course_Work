#include <iostream>
#include "MovieChart.h"
using namespace std;

int main() {
	MovieChart* movieChart = new MovieChart();
	bool quit = false;
	string choice = "";
    cout << endl; 
	
    while(!quit) {
		cout << "Please enter a command (Create, Update, View, Login, Logout, or Quit):";
		cin >> choice;
	    cout << endl;

		if(choice == "Create") {
		    movieChart->create();
        }
		else if(choice == "Update") {
		    movieChart->update();
        }
		else if(choice == "View") {
		    movieChart->view();
        }
		else if(choice == "Login") {
		    movieChart->login();
        }
		else if(choice == "Logout") {
        }
        else if(choice == "Quit") {
			quit = true;
		}
		else {
			cout << "INVALID COMMAND" << endl << endl;
		}
	}	
}
