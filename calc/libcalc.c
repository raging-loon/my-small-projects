#include "libcalc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
token * token_list;
token * head;
token * current;


void add_new_token(token_t tok, const char * val)
{
  current = (token *)malloc(sizeof(token));

  current->type = tok;
  strcpy(current->value, val);

  head->next = current;
  head = current;



}