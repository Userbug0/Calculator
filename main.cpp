#include "error.h"
#include "lex_analyzer.h"
#include "table.h"

extern Table table;
extern token_value curr_token;
int iserror = 0;

int main()
{
    cout << "Hello! Welcome to Calculator.\n" <<
        "Here you can do math operations(+, -, *, /, ^) and create variables.\n" << 
        "For example:\n" <<
        "a=2; b=3; a*b (returns 6)\n"<<
        "Also there is predefined constants:\n" <<
        "2*(pi+1) (returns 8.28...)\n" <<
        "To leave just print exit\n\n";
    table.insert("pi")-> value = 3.1415926535897932385;
    table.insert("e")-> value = 2.7182818284590452354;
    while (1) {
        //cout << "Curr_token: " << curr_token << endl;
        get_token();
        if (curr_token == SPACE) continue;
        double result = expr();
        if (iserror) {
            iserror = 0;
            continue;
        } 
        cout << "Result: " << result << endl;
    }
    return 0;
}
