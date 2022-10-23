#ifndef LIBCALC_H
#define LIBCALC_H

#define NUM_TOKENS 7

double parse_expession(const char * expr);

typedef enum{
  TOKEN_ADD,
  TOKEN_SUB,
  TOKEN_DIV,
  TOKEN_MULT,
  TOKEN_OPEN_PAR,
  TOKEN_CLOSE_PAR,
  TOKEN_EXPONENT,
  TOKEN_INTEGER_LITERAL = 90,
  TOKEN_FLOATING_POINT
} token_t;


typedef struct token
{
  token_t type;
  struct token * next;
  double value;  
} token;

extern token * token_list;
extern token * head;
extern token * current;

void insert_token(token_t tok, const char * val);

int get_length();

void reverse_list(token ** head_ref);

void free_token_list();

void debug_print_list();

#endif // LIBCALC_H