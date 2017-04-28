#include "ssfs.hpp"
#include <iostream>

PFile:PFile (char name[33], int size, int _bdp[12], int *_ibp, int **_dibp) {
    *f_name = name;
    f_size = size;
    bdp = _bdp;
    ibp = _ibp;
    dibp = _dibp;
}
