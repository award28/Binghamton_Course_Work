#ifndef LCS_HPP
#define LCS_HPP
#include <iostream>
#include <fstream>
#include <string>

class LenLCS {
    public:
        LenLCS() {}
        void execute(const std::string &x, const std::string &y, const std::string &outfile);
};

class TopDownLCS {
    public:
        TopDownLCS() {}
        void lcs(const std::string &x, const std::string &y, const std::string &outfile);
    private:
        int execute(const std::string &x, const std::string &y, int curX, int lenX, int curY, int lenY);
};

class Memoization {
    public:
        Memoization() {}
        void lcs(const std::string &x, const std::string &y, const std::string &outfile);
    private:
        int execute(const std::string &x, const std::string &y, int curX, int lenX, int curY, int lenY, int *arr);
};
#endif
