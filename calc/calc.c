#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libcalc.h"
#include <ctype.h>




int main(int argc, char ** argv)
{
  if(!token_list)
  {
    token_list = (token*)malloc(sizeof(token));
    memset(token_list, 0, sizeof(token));
    current = token_list;
  }
  char expr[256];

  for(int i = 1; i < argc; i++)
  {
    strcat(expr, argv[i]);
    strcat(expr, " ");
  }

  printf("%s\n",expr);
  // may go unused
  char digit_buffer[16];
  unsigned int digit_buffer_len = 0;
  memset(digit_buffer, 0, 16);
  
// bin((0xffffffff >> (32- 25)) << (32 - 25))

  for(int i = 0; i < strlen(expr); i++)
  {
    token_t current_token;
    if(isdigit(expr[i])){
      current_token = TOKEN_INTEGER_LITERAL;
      // printf("Integer literal: %c\n",expr[i]);
    }

    else if(expr[i] == '+')
      // printf("Operator add: %c\n",expr[i]);
      current_token = TOKEN_ADD;
    
    else if(expr[i] == '-')
      // printf("Operator sub: %c\n",expr[i]);
      current_token = TOKEN_SUB;

    else if(expr[i] == '/')
      current_token = TOKEN_DIV;
      // printf("Operator div: %c\n",expr[i]);

    else if(expr[i] == '*')
      current_token = TOKEN_MULT;
      // printf("Operator mul: %c\n",expr[i]);

    else if(expr[i] == '(')
      // printf("Open parenthesis: %c\n",expr[i]);
      current_token = TOKEN_OPEN_PAR;
    else if(expr[i] == ')')
      current_token = TOKEN_CLOSE_PAR;
      // printf("Closed parenthesis: %c\n",expr[i]);


    insert_token(current_token, &expr[i]);
  }

  reverse_list(&head);
  debug_print_list();

  if(token_list) free(token_list);
}