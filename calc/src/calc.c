#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "calc.h"

static void get_input(char * out, int outlen);
static void print_syntax_error(const char * expr, int loc);


token token_list[32];
unsigned int list_len = 0;



int main(int argc, char ** argv){

  char exprbuffer[128] = {0};
  
  while(true)
  {
    int lex_res = 0;
    memset(&token_list,0, sizeof(token_list));
    printf("> ");
    
    get_input(exprbuffer, sizeof(exprbuffer));
    
    if(strcmp(exprbuffer,"exit") == 0){
      printf("Exiting....\n");
      exit(0);
    }

    printf("%s\n", exprbuffer);
    if((lex_res = lex_expr(exprbuffer, &token_list, &list_len)) < 0)
    {
      print_syntax_error(exprbuffer, abs(lex_res));
      continue;
    }
    
  }

  

}

void get_input(char * out, int outlen)
{
  memset(out, 0, outlen);
  fgets(out, outlen, stdin);
  out[strcspn(out,"\n")] = 0;
}

int lex_expr(char * expr, token * list, unsigned int * list_len)
{
  
}


static void print_syntax_error(const char * expr, int loc)
{
  printf("%s\n",expr);
  for(int i = 0; i < loc-1; i++) printf("~");
  printf("^\n");
}