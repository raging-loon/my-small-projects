/*

Write a function that receives an integer. The function must return a string containing the
hexadecimal representation of the integer.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



#define IS_DIGIT(x) (x >= '0' && x <= '9')

bool isnumber(char * str);
void int32_to_hexstr(unsigned int num, char * outstr);
char int_to_hexchar(int val);

int main(int argc, char ** argv)
{
  if(argc == 1)
  {
    printf("Usage: ./%s <integer>\n", argv[0]);
    exit(0);
  }

  if(!isnumber(argv[1])){
    printf("Please enter an integer\n");
    exit(EXIT_FAILURE);
  }

  char hexstr[64];
  memset(hexstr, 0, sizeof(hexstr));

  int32_to_hexstr(strtoul(argv[1], NULL, 10), hexstr);

  printf("0x%s\n",hexstr);

  return 0;
}

bool isnumber(char * str){
  for(int i = 0; i < strlen(str); i++)
  {
    if(!IS_DIGIT(str[i])) return false;
  }
  return true;
}



void int32_to_hexstr(unsigned int num, char * outstr)
{
  unsigned int outlen = 0;

  while(num != 0)
  {
    int rem = num%16;
    num/=16;
    outstr[outlen++] = int_to_hexchar(rem);
  }
  strrev(outstr);
}

char int_to_hexchar(int val)
{
  if(val < 10) return val+'0';
  else{
    switch(val){
      case 10: return 'a';
      case 11: return 'b';
      case 12: return 'c';
      case 13: return 'd';
      case 14: return 'e';
      case 15: return 'f';
      default: return '?'; 
    }
  }
}

