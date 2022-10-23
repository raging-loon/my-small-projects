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
  

  for(int i = 0; i < strlen(expr); i++)
  {
    add_new_token(1,"h");
    

    
  }

  if(token_list) free(token_list);
}