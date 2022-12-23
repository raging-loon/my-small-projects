/*

Write a function that receives a string containing a 32-bit hexadecimal integer. The function
must return the decimal integer value of the hexadecimal integer.


*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned int hexdig_to_int(char dig);
unsigned int hex32str_to_dec(char * str);

int main(int argc, char ** argv)
{
  if(argc == 1)
  {
    printf("Usage: ./%s <hex-number>\n",argv[0]);
    exit(0);
  }

  if(strlen(argv[1]) != 8){
    printf("Hex number must be 32 bit\n");
    exit(1);
  }

  printf("%lu\n", hex32str_to_dec(argv[1]));
}

// e.g. 0x12341234
unsigned int hex32str_to_dec(char * str)
{
  unsigned int result = 0;
  unsigned int n = 7;
  for(int i = 0; i < strlen(str); i++)
    result += (hexdig_to_int(str[i]) * pow(16,n--));

  return result;
}

unsigned int hexdig_to_int(char dig)
{
  switch(dig)
  {
    case 'F':
    case 'f': return 0xf;
    case 'E':
    case 'e': return 0xe;
    case 'd':
    case 'D': return 0xd;
    case 'c':
    case 'C': return 0xc;
    case 'B':
    case 'b': return 0xb;
    case 'a':
    case 'A': return 0xa;
    default:
      return dig-'0';
  }
}