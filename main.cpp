#include <iostream>
#include <unistd.h>
#include <assert.h>

#include "ssfs.hpp"

using namespace std;

void* controller(void *arg) {
    Controller*controller = (Controller*)arg;

    char *res = controller->read(0, 0);
    cout << res << endl;

    return NULL;
}
    
int main(int argc, char *argv[]) {
    char *disk = argv[1];

    Controller *cntlr = new Controller(disk);
    std::queue<op> buffer;

    pthread_t cThread;

    int result_code = pthread_create(&cThread, NULL, &controller, cntlr);
    assert(!result_code);

    result_code = pthread_join(cThread, NULL );
    assert( !result_code );

    string text;

    cin >> text;
    while(text != "stop") {
        
        cin >> text;
    }

    return 0;
}
