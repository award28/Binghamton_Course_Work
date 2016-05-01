#include <iostream>
#include "MovieChart.h"
using namespace std;

int main() {
	MovieChart* movieChart = new MovieChart();
	bool quit = false;
	string choice = "";
	
    while(!quit) {
		cout << "Please enter a command (Create, Update, View, Login, Logout, Close, List, or Quit):";
		cin >> choice;
	    cout << endl;
        cout << choice << endl;

		if(choice == "Create") {
		    movieChart->create();
            cout << endl;
        }
		else if(choice == "Update") {
		    movieChart->update();
            cout << endl;
        }
		else if(choice == "View") {
		    movieChart->view();
            cout << endl;
        }
		else if(choice == "Login") {
		    movieChart->login();
            cout << endl;
        }
		else if(choice == "Logout") {
            movieChart->logout();
            cout << endl;
        }
 		else if(choice == "List") {
            movieChart->list();
            cout << endl;
        }
  		else if(choice == "Close") {
            movieChart->close();
            cout << endl;
        }
        else if(choice == "Quit") {
			quit = true;
		}
		else {
			cout << "INVALID COMMAND" << endl;
            cout << endl;
		}
	}	
    //delete movieChart;
}
