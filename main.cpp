#include <iostream>

#include "ssfs.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    Controller *controller = new Controller();

    char *res = controller->read();

    cout << res << endl;

    string text;

    cin >> text;
    while(text != "stop")
        cin >> text;

    return 0;
}
