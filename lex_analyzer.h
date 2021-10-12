extern double number_value;  // last number
extern char* name_string;    // last variable

extern double expr();   // perform math operatrions
extern double prim();   // perform other operations('=', '(', '-variable')

enum token_value {
    SPACE, NUMBER, NAME, PRINT,
    PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
    DIVINT = '//', RP = ')', LP = '(', ASSIGN = '=',
    POW = '^'
};

extern token_value curr_token;
extern token_value get_token();  // scanner(1 by 1 char)
