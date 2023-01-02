#include <stdio.h>
#include "echosrv.h"


int main(){
  echosrv * myServer = new echosrv(12345);

  if(myServer->init() != ServerError::OK){
    printf("Failed to init server with error: %d. %s\n",myServer->get_error_code(), myServer->get_err_msg());
    return 1;
  }
 
  if(myServer->setLogging("serverlog.txt", mlog::INCLUDE_TIME) == -1)
    printf("Failed to set up logging, continuing without\n");
  

  printf("Successfully initialized echo server\n");

  myServer->run();

  delete myServer;
}