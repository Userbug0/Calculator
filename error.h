#include <iostream>

using namespace std;

extern int iserror;    // 1 if there was an error in the program due to the user
extern void error(const char* str);  // prints errors, then make "iserror" = 1

