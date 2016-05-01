#include <string>
#include <iostream>
#include <cassert>
#include <list>
#include <vector>
#include "Map.hpp"
#include "City.hpp"
using namespace std;

void printAdj(list<City *> adjacency){
	for(auto it:adjacency) 
		cerr << it->getName() << " --- [x]: " << it->getXCoor() << " [y]: " << it->getYCoor() << endl;
}

void printPath(vector<City *> path){
	//print list
	if (!path.empty()) {
		auto it = path.begin();
		cout << "Your Starting City is:\t" << (*it)->getName() << endl;
		
		for (; it != path.end(); it++){
			City * c = (*it); 
			if (it+1 == path.end()) {
				cout << "Your Destination City is:\t" << c->getName() << endl;
				//cout << "\tDistance from the last node: " << step->distanceFromOptimalPrevious() << endl;
				cout << "\tThe (x,y) coordinates are: (" << c->getXCoor() << ", " << c->getYCoor() << ")" << endl;
			}else{
				cout << "The next city is: " << c->getName() << endl;
				cout << "\tThe (x,y) coordinates are: (" << c->getXCoor() << ", " << c->getYCoor() << ")" << endl;
			}
		}
	}	
}

int main(int argc, char *argv[]){

	cerr << "\n\tTEST #1: Read file a list of Cities and their locations" << endl;	
	Map map("townlist.txt");
	assert(map.findByName("binghamton") != NULL);
	assert(map.findByName("fairbanks") != NULL);
	assert(map.findByName("cypress") != NULL);
	assert(map.findByName("victorville") != NULL);
	assert(map.findByName("laguna") != NULL);
	assert(map.findByName("anaheim") != NULL);
	assert(map.findByName("bend") != NULL);
	assert(map.findByName("rialto") != NULL);
	assert(map.findByName("kathmandu") == NULL);
	assert(map.findByName("bend")->getXCoor() == 6 && map.findByName("bend")->getYCoor() == 7);
	assert(map.findByName("rialto")->getXCoor() == 4 && map.findByName("rialto")->getYCoor() == 7);

	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #2: Test Adjacencies" << endl;	

	list<City*> adj, test;
	test = map.findByName("bend")->getAdjacent();
	test.sort();
	adj.push_back(map.findByName("rialto"));
	adj.push_back(map.findByName("victorville"));
	adj.sort();
	assert(adj == test);

	test = map.findByName("rialto")->getAdjacent();
	test.sort();
	adj.clear();
	adj.push_back(map.findByName("bend"));
	adj.push_back(map.findByName("anaheim"));
	adj.sort();
	assert(adj == test);

	test = map.findByName("fairbanks")->getAdjacent();
	test.sort();
	adj.clear();
	adj.push_back(map.findByName("binghamton"));
	adj.push_back(map.findByName("anaheim"));
	adj.sort();
	assert(adj == test);

	test = map.findByName("cypress")->getAdjacent();
	test.sort();
	adj.clear();
	adj.push_back(map.findByName("binghamton"));
	adj.push_back(map.findByName("anaheim"));
	adj.push_back(map.findByName("victorville"));
	adj.sort();
	assert(adj == test);

	test = map.findByName("anaheim")->getAdjacent();
	test.sort();
	adj.clear();
	adj.push_back(map.findByName("rialto"));
	adj.push_back(map.findByName("fairbanks"));
	adj.push_back(map.findByName("cypress"));
	adj.sort();
	assert(adj == test);

	test = map.findByName("victorville")->getAdjacent();
	test.sort();
	adj.clear();
	adj.push_back(map.findByName("bend"));
	adj.push_back(map.findByName("laguna"));
	adj.push_back(map.findByName("cypress"));
	adj.sort();
	assert(adj == test);

	test = map.findByName("laguna")->getAdjacent();
	test.sort();
	adj.clear();
	adj.push_back(map.findByName("victorville"));
	adj.sort();
	assert(adj == test);

	adj.clear();
	assert(adj != test);
	cerr << "\n\t========================PASS========================\n" << endl;

/*
	cerr << "\n\tTEST #3: Simple Shortest Path" << endl;

	City * start = map.findByName("bend");
	City * dest = map.findByName("rialto");

	vector<City *> route = map.shortestPath(start, dest);
	assert(route.front()->getName() == "bend");
	assert(route.back()->getName() == "rialto");
	assert(route.size() == 2);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #4: Less Simple Shortest Path" << endl;

	start = map.findByName("rialto");
	dest = map.findByName("fairbanks");

	route = map.shortestPath(start, dest);
	assert(route.size() == 3);
	assert(route.back()->getName() == "fairbanks");
	route.pop_back();
	assert(route.back()->getName() == "anaheim");
	route.pop_back();
	assert(route.back()->getName() == "rialto");
	route.pop_back();
	assert(route.empty());

	cerr << "\n\t========================PASS========================\n" << endl;
*/	
	/********more tests TBD***********/
	return 0;
	
}
