#include "error.h"
#include "lex_analyzer.h"
#include "table.h"
#include <math.h>

double number_value = NULL;
char* name_string = new char[16];
token_value curr_token = SPACE;
extern Table table;
extern int iserror;


token_value get_token() {
    char ch;
    do {
        if (!cin.get(ch)) return curr_token = SPACE;
    } while (ch != '\n' && isspace(ch));
    switch (ch) {
    case ';':
    case '\n':
        return curr_token = SPACE;
    case '+': case '-': case '*': case '/': case '^':
    case '//': case '=': case '(': case ')':
        return curr_token = token_value(ch);
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        cin.putback(ch);
        cin >> number_value;
        return curr_token = NUMBER;
    default:
        if (isalpha(ch)) {
            char* p = name_string;
            *p++ = ch;
            while (cin.get(ch) && isalpha(ch)) {
                *p++ = ch;
            }
            cin.putback(ch);
            *p = 0;
            if (strcmp(name_string, "exit") == 0) exit(0);
            return curr_token = NAME;
        }
        error("Incorrect variable name");
        return curr_token = SPACE;
    }
}

double expr() {
    if (iserror) return 0;
    double left = prim();
    double temp;
    while (1) {
        switch (curr_token) {
        case PLUS:
            get_token();
            temp = prim();
            if (curr_token == PLUS || curr_token == MINUS) return left + temp + expr();
            return left + temp;
        case MINUS:
            get_token();
            temp = prim();
            if (curr_token == PLUS || curr_token == MINUS) return left - temp + expr();
            return left - temp;
        case MUL:
            get_token();
            return left * prim();
        case DIV:
        {
            get_token();
            double d = prim();
            if (iserror) return 0;
            if (d == 0) {
                error("Division by zero");
            }
            return left / d;
        }
        case POW:
        {
            get_token();
            double d = prim();
            if (iserror) return 0;
            if (d == 0 && left == 0) {
                error("Zero to power of zero");
            }
            return pow(left, d);
        }
        default:
            return left;
        }
    }

}

double prim() {
    if (iserror) return 0;
    switch (curr_token) {
    case NUMBER:
        get_token();
        return number_value;
    case NAME:
    {
        get_token();
        if (curr_token == ASSIGN) {
            name* n = table.insert(name_string);
            get_token();
            //n->value = expr();
            double temp = expr();
            if (iserror) return 0;
            n->value = temp;
            return n->value;
        }
        name* n = table.look(name_string);
        if (n != 0) return n->value;
        return 0;
    }
    case MINUS:
        get_token();
        return -prim();
    case LP:
    {
        get_token();
        double e = expr();
        if (curr_token != RP) {
            error("Necessary )");
        }
        get_token();
        return e;
    }
    default:
        return 0;
    }
}
