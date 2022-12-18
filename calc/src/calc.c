#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
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
  bool is_parsing_num = false;
  char parse_num[16] = {0};
  int num_len = 0; // so we don't have to use strlen
  int expr_len = strlen(expr);
  int parse_tok_res = 0; 
  for(int i = 0; i < expr_len;)
  {
    char c = expr[i];
    if(isdigit(c)){
      parse_num[num_len++] = c;
      is_parsing_num = true;

      if(i == expr_len-1){
        parse_token(parse_num);
        break;
      }
    } else {
      
      if(is_parsing_num == true){
        
        is_parsing_num = false;

        if((parse_tok_res = parse_token(parse_num)) == -1)
          break;
        memset(parse_num, 0, 16);
        
        num_len = 0;
        continue;
      
      
      } else {
        parse_num[0] = c;
        if((parse_tok_res = parse_token(parse_num)) == -1)
          break;
        memset(parse_num, 0, 16);

      }
    }
    
    i++;
  }
  return parse_tok_res;
}


static void print_syntax_error(const char * expr, int loc)
{
  printf("%s\n",expr);
  for(int i = 0; i < loc-1; i++) printf("~");
  printf("^\n");
}

bool is_number(char * str)
{
  for(int i = 0; i < strlen(str); i++)
  {
    if(isdigit(str[i]) == false) return false;
  }
  return true;
}



token_type parse_token(char * token)
{
  
  if(is_number(token)) 
  {
    printf("INTEGER_LITERAL\n");
    return INTEGER_LITERAL;
  }
  // after this, only one character should have been used
  switch(token[0])
  {
    case '+':
      printf("OP_ADD\n");
      return OP_ADD;
    case '-':
      printf("OP_SUB\n");
      return OP_SUB;
    case '*':
      printf("OP_MULT\n");
      return OP_MULT;
    case '/':
      printf("OP_DIV\n");
      return OP_DIV;
    case '(':
      printf("OPEN_PARENTH\n");
      return OPEN_PARENTH;
    case ')':
      printf("CLOSE_PARENTH\n");
      return CLOSE_PARENTH;
    default:
      printf("INVALID\n");
      return -1;      
  }

}