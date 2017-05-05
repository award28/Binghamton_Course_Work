#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#include "ssfs.hpp"

using std::string;
using std::cout;
using std::endl;

disk_op::disk_op(string f_name, std::queue<op> &buf) {
    std::ifstream in;
    in.open(f_name);
    if (in.fail()) {
        std::cerr << "Error: " << strerror(errno);
    }
    string line;
    while (std::getline(in, line)) {
        op curr_op;
        curr_op.data = (char *)malloc(sizeof(char));
        curr_op.data[0] = '\0';
        parse(curr_op, line);
        // print op
        cout << "line: " << line << endl;
        cout << "~~~~~~~~ op struct ~~~~~~~~~~" << endl;
        cout << curr_op.cmd << endl;
        cout << curr_op.name << endl;
        cout << curr_op.start << endl;
        cout << curr_op.size << endl;
        cout << curr_op.data << endl;
        cout << curr_op.pid << endl << endl;
    }
}

void disk_op::parse(op &curr_op, string line) {
    // curr_op.pid = getpid();
    // curr_op.cmd = line.substr(0, line.find(' '));
    // if (string("CREATE").compare(curr_op.cmd) == 0) {
    //     curr_op.name = line.substr(line.find(' ') + 1);
    // }
    // if (string("IMPORT").compare(curr_op.cmd) == 0) {
    //     curr_op.name = line.substr(line.find(' ') + 1, line.find(' ', line.find(' ')));
    //     string t = line.substr(line.find(' ', line.find(' ')) + 1).c_str();
    //     curr_op.data = (char *)malloc(sizeof(char)*t.length() + 1);
    //     for (int i = 0; i < t.length(); i++) {
    //         curr_op.data[i] = t[i];
    //     }
    // }
    // if (string("CAT").compare(curr_op.cmd) == 0) {
    //     curr_op.name = line.substr(line.find(' ') + 1);
    // }
    // if (string("DELETE").compare(curr_op.cmd) == 0) {
    //     curr_op.name = line.substr(line.find(' ') + 1);
    // }
    // if (string("WRITE").compare(curr_op.cmd) == 0) {
    //     size_t t = line.find(' ') + 1;
    //     curr_op.name = line.substr(t, line.find(' ', t));
    //     t = line.find(' ', t) + 1;
    //     curr_op.data = (char *)malloc(sizeof(char)*2);
    //     curr_op.data[0] = line[t];
    //     curr_op.data[1] = '\0';
    //     t = line.find(' ', t) + 1;
    //     curr_op.start = atoi(line.substr(t, line.find(' ', t)).c_str());
    //     t = line.find(' ', t) + 1;
    //     curr_op.size = atoi(line.substr(t, line.find(' ', t)).c_str());
    // }
    // if (string("READ").compare(curr_op.cmd) == 0) {
    //     size_t t = line.find(' ') + 1;
    //     curr_op.name = line.substr(t, line.find(' ', t));
    //     t = line.find(' ', t) + 1;
    //     curr_op.start = atoi(line.substr(t, line.find(' ', t)).c_str());
    //     t = line.find(' ', t) + 1;
    //     curr_op.size = atoi(line.substr(t, line.find(' ', t)).c_str());
    // }
    // if (string("LIST").compare(curr_op.cmd) == 0) {
    // }
    // if (string("SHUTDOWN").compare(curr_op.cmd) == 0) {
    // }


    std::stringstream ss;
    ss << line;
    curr_op.pid = getpid();
    ss >> curr_op.cmd;
    if (string("CREATE").compare(curr_op.cmd) == 0) {
        ss >> curr_op.name;
    }
    if (string("IMPORT").compare(curr_op.cmd) == 0) {
        ss >> curr_op.name;
        string t;
        ss >> t;
        curr_op.data = (char *)malloc(sizeof(char)*t.length() + 1);
        for (int i = 0; i < t.length(); i++) {
            curr_op.data[i] = t[i];
        }
    }
    if (string("CAT").compare(curr_op.cmd) == 0) {
        ss >> curr_op.name;
    }
    if (string("DELETE").compare(curr_op.cmd) == 0) {
        ss >> curr_op.name;
    }
    if (string("WRITE").compare(curr_op.cmd) == 0) {
        ss >> curr_op.name;
        string t;
        ss >> t;
        curr_op.data = (char *)malloc(sizeof(char)*2);
        curr_op.data[0] = t[0];
        curr_op.data[1] = '\0';
        ss >> t;
        curr_op.start = atoi(t.c_str());
        ss >> t;
        curr_op.size = atoi(t.c_str());
    }
    if (string("READ").compare(curr_op.cmd) == 0) {
        ss >> curr_op.name;
        string t;
        ss >> t;
        curr_op.start = atoi(t.c_str());
        ss >> t;
        curr_op.size = atoi(t.c_str());
    }
    if (string("LIST").compare(curr_op.cmd) == 0) {
    }
    if (string("SHUTDOWN").compare(curr_op.cmd) == 0) {
    }
}
