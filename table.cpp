#include "table.h"
#include "error.h"

extern Table table = Table();
extern const int TBLSZ;
extern int iserror;

name* Table::look(const char* p, int ins) {  // if (ins = 1) the *p will be written in the table(0 if already in the table) 
    int ii = 0;     // hash-code
    const char* pp = p;
    while (*pp) ii += *pp++;
    if (ii < 0) ii = -ii;
    ii %= TBLSZ;
    for (name* n = array[ii]; n; n->next) {
        if (strcmp(p, n->string) == 0) return n;
    }
    if (ins == 0) {
        error("Variable wasn't find");
        return 0;
    }
    name* nn = new name;
    nn->string = new char[strlen(p) + 1];
    strcpy_s(nn->string, strlen(p) + 1, p);
    nn->value = 0;
    nn->next = array[ii];
    array[ii] = nn;
    return nn;
}
