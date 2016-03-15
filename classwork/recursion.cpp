#include <iostream>

using namespace std;

int countDown(int num);
int main() {
    int num;

    cout << "Give me a numba: ";
    cin >> num;

    countDown(num);
}

int countDown(int num) {
    cout << num << endl;
    if(num == 0) {
        return num;
    }
    (num>0)? num--: num++;
    num = countDown(num);
    return num;
}
    
