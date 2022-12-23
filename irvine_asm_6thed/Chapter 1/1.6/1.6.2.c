/*

Write a function that receives a string containing a 32-bit hexadecimal integer. The function
must return the decimal integer value of the hexadecimal integer.


*/

#include <stdio.h>
#include <stdlib.h>

int hex32str_to_dec(char * str);

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

  printf("%d\n", hex32str_to_dec(argv[1]));
}

// e.g. 0x12341234
int hex32str_to_dec(char * str)
{
  return 0;
}