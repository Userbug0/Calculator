#include "error.h"


void error(const char* str) {
	cout << "Error: " << str << endl;
	iserror = 1;
}
