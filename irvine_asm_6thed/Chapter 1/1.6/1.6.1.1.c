/*

Write a function that receives a string containing a 16-bit binary integer. The function must
return the decimal integer value of the binary integer.

*/


#include <stdio.h>
#include <stdlib.h>

int binstr16_to_dec(const char * binstr);


int main(int argc, char ** argv)
{
  if(argc == 1){
    printf("Usage: ./%s <binary>\n",argv[0]);
    exit(0);
  }
  if(strlen(argv[1]) != 16){
    printf("Binary input must be 16 characters\n");
    exit(1);
  }
  printf("%d\n",binstr16_to_dec(argv[1]));


}

int binstr16_to_dec(const char * binstr)
{
  int res = 0;
  
  int bd = 0;

  for(int i = strlen(binstr)-1; i >= 0; i--)
  {
    res |= (binstr[i] == '1' ? (1 << bd) : 0);
    bd++;
  }
  return res; 
   
}