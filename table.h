#include <iostream>

using namespace std;

const int TBLSZ = 32;

struct name {
    char* string;
    name* next;   // uses when elements have same hash-codes
    double value;
};

struct Table {
    name* array[TBLSZ];
    name* look(const char* p, int ins = 0);
    inline name* insert(const char* s) { return look(s, 1); }
};

extern Table table;