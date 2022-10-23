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
  char value[16];
  struct token * next;
} token;

extern token * token_list;
extern token * head;
extern token * current;

void add_new_token(token_t tok, const char * val);



#endif // LIBCALC_H