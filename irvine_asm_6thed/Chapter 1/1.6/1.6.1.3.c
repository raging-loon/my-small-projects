/*

Write a function that receives an integer. The function must return a string containing the
binary representation of the integer

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define IS_DIGIT(x) (x >= '0' && x <= '9')

void int_to_binstr(unsigned int num, char * strout);
bool isnumber(char * str);

int main(int argc, char ** argv)
{
  if(argc == 1)
  {
    printf("Usage: ./%s <integer>\n", argv[0]);
    exit(0);
  }
  if(!isnumber(argv[1]))
  {
    printf("Please enter a number\n");
    exit(1);
  }

  char binstr[64];
  memset(binstr, 0, sizeof(binstr));
  int_to_binstr(strtoul(argv[1], NULL, 10), binstr);

  printf("%s\n",binstr);

}

void int_to_binstr(unsigned int num, char * strout)
{
  int binstr_len = 0;
  for(int i = 31; i >= 0; i--){
    if(num & (1 << i)) strout[binstr_len++] = '1';
    else strout[binstr_len++] = '0';
  }
}

bool isnumber(char * str){
  for(int i = 0; i < strlen(str); i++)
  {
    if(!IS_DIGIT(str[i])) return false;
  }
  return true;
}
