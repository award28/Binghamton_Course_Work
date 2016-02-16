#include <iostream>

using namespace std;

int main() {

}

void quickSearch() {
	int current = 50;
	while(checkValue(current) != 0) {
		if(checkValue(current) == -1) {current -= current/2;}
		else if(checkValue(current) == 1) {current += current/2;}
		else {break;}
	}
	cout << "Your number is " << current << endl;
	
}

void hisQuickSearch() {
	int x = 50;
	while(checkValue(x) != 0) {
		if(checkValue(x) == 1) {x/=2;}
		else{x += (x/2);}
	}
	cout << x << endl;
}
