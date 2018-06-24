#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <utility>

#include "predictors.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc != 3) {
        cerr << "You have an incorrect number of arguments." << endl;
        exit(0);
    }

  // Temporary variables
  unsigned long long addr;
  string behavior, line;

  std::vector<std::pair<unsigned long long, string> > branches;

  // Open file for reading
  ifstream infile(argv[1]);
  ofstream outfile;
  outfile.open(argv[2]);

  // The following loop will read a line at a time
  while(getline(infile, line)) {
    stringstream s(line);
    s >> std::hex >> addr >> behavior;
    branches.push_back(std::pair<unsigned long long, string>(addr, behavior));
  }
    Taken *taken = new Taken();
    NotTaken *notTaken = new NotTaken();
    SingleBimodal *single = new SingleBimodal();
    SaturatingBimodal *saturating = new SaturatingBimodal();
    GShare *gShare = new GShare();
    Tournament *tournament = new Tournament();

    //Always taken
    outfile << taken->prediction(branches) << endl;
    //Always not taken
    outfile << notTaken->prediction(branches) << endl;
    //Single bimodal
    outfile << single->prediction(branches, 4) << " ";
    outfile << single->prediction(branches, 5);
    for(int i = 7; i < 12; i++)
        outfile  << " " << single->prediction(branches, i);
    outfile << endl;
    //Two bit bimodal
    outfile << saturating->prediction(branches, 4) << " ";
    outfile << saturating->prediction(branches, 5);
    for(int i = 7; i < 12; i++)
        outfile << " " << saturating->prediction(branches, i);
    outfile << endl;
    //GShare
    for(int i = 3; i < 12; i++) {
        if(i == 3)
            outfile << gShare->prediction(branches, i);
        else 
            outfile << " " << gShare->prediction(branches, i);
    }
    outfile << endl;
    //Tournament
    outfile << tournament->prediction(branches) << endl;

    infile.close();
    outfile.close();
  return 0;
}
