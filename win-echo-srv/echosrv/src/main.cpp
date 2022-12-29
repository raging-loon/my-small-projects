#include <stdio.h>
#include "echosrv.h"


int main(){
  echosrv * myServer = new echosrv(12345);

  if(myServer->init() != ServerError::OK){
    printf("Failed to init server with error: %d. %s\n",myServer->get_error_code(), myServer->get_err_msg());
    return 1;
  }
 
  printf("Successfully initialized echo server\n");
  while(true){}
  delete myServer;
}