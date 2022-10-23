#include "libcalc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
token * token_list;
token * head;
token * current;

void insert_token(token_t tok, const char * val)
{
  token * newnode = (token *)malloc(sizeof(token));

  newnode->type = tok;
  if(tok == TOKEN_INTEGER_LITERAL)
  {
    sscanf(val, "%lf", &newnode->value);
  }
  newnode->next = head;

  head = newnode;
  
}

int get_length()
{
  token * head_ptr = head;
  int len = 0;
  while(head_ptr != NULL)
    len++;

  return len;
}

void reverse_list(token ** head_ref)
{
  token * prev = NULL;
  token * current = *head_ref;
  token * next;

  while(current != NULL)
  {
    next = current->next;
    current->next = prev;

    prev = current;
    current = next;
  }

  *head_ref = prev;
}

void free_token_list();


void debug_print_list()
{
  token * current = head;
  while(current != NULL)
  {
    switch(current->type)
    {
      case TOKEN_ADD:
        printf("TOKEN ADD\n");
        break;
      case TOKEN_CLOSE_PAR:
        printf("TOKEN CLOSE_PARENTH\n");
        break;
      case TOKEN_OPEN_PAR:
        printf("TOKEN OPEN PARENTH\n");
        break;
      case TOKEN_DIV:
        printf("TOKEN DIV\n");
        break;
      case TOKEN_MULT:
        printf("TOKEN MULT\n");
        break;
      case TOKEN_EXPONENT:
        printf("TOKEN EXPONENT\n");
        break;
      case TOKEN_INTEGER_LITERAL:
        printf("LITERAL: %lf\n",current->value);
        break;
      default:
        printf("Unknown token: %d\n",current->type);
        break;
    }
    current = current->next;
  }

  printf("\n");
}