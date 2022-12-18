#ifndef CALC_H
#define CALC_H

#include <stdbool.h>

typedef enum token_type{
  INTEGER_LITERAL,
  FLOATING_POINT_LITERAL,
  OP_MULT,
  OP_ADD,
  OP_SUB,
  OP_DIV,
  CLOSE_PARENTH,
  OPEN_PARENTH
} token_type;

typedef struct token
{
  char * tok;
  double val;
  token_type type;
} token;

int lex_expr(char * expr, token * list, unsigned int * list_len);

token_type parse_token(char * token);

bool is_number(char * str);
#endif /* CALC_H */