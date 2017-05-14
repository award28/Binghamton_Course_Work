#ifndef PREDICTORS_HPP
#define PREDICTORS_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using std::string;

typedef std::vector<std::pair<unsigned long long, string> > branches;
typedef std::pair<unsigned long long, string> branch;

class Taken {
    public:
        Taken() {}
        string prediction(const branches &v);
};

class NotTaken {
    public:
        NotTaken() {}
        string prediction(const branches &v);
};

class SingleBimodal {
    public:
        SingleBimodal() {}
        string prediction(const branches &v, int tsize);
};

class SaturatingBimodal {
    public:
        SaturatingBimodal() {}
        string prediction(const branches &v, int tsize);
};

class GShare {
    public:
        GShare() {}
        string prediction(const branches &v, int gsize);
};

class Tournament {
    public:
        Tournament() {}
        string prediction(const branches &v);
    private:
        bool saturatingBimodal(const branch branch, int *table, int index); 
        bool gShare(const branch branch, int *table, int index, int &ghr);
};
#endif
