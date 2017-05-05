#include <fstream>
#include <iostream>
#include <ssfs.hpp>
#include <string>
#include <sys/types.h>
#include <unistd.h>

using std::string;

disk_op::disk_op(string f_name, Controller &controller) {
    std::ifstream in;
    in.open(f_name);
    if (in.fail()) {
        std::cerr << "Error: " << strerror(errno);
    }
    op curr_op;
    string line;
    while (in >> line) {
        curr_op.command = line;
        curr_op.pid = getpid();
        std::cout << controller.execute(curr_op) << std::endl;
    }
}
