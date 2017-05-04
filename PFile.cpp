// Struct for a file object, delete this file after integration into the header

struct p_file {
    char name[33];
    int size; // in bytes
    int dbp[12];
    int *ibp;
    int **dibp;
};
