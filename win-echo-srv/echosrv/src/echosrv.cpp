#include "echosrv.h"

// this cannot be used any where else
// more readable way of setting error codes
#define SET_ERROR_CODES(errcode, server_error_code) error_code = errcode; last_server_error = server_error_code;

echosrv::echosrv(unsigned int lport = 48876) : port(lport)
{

}

ServerError echosrv::init()
{ 
  int ires;

  if((ires = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
  {
    SET_ERROR_CODES(ires, ServerError::WSASTARTUP_ERROR)
    return ServerError::WSASTARTUP_ERROR;
  }






  return ServerError::OK;
}


char * echosrv::get_err_msg()
{
  switch(last_server_error){
    case ServerError::OK: return "OK";
    case ServerError::FAILED_TO_BIND: return "FAILED_TO_BIND";
    case ServerError::WSASTARTUP_ERROR: return "WSASTARTUP_ERROR";
    case ServerError::FAILED_TO_LISTEN: return "FAILED_TO_LISTEN";
    case ServerError::FAILED_TO_CREATE_SOCKET: return "FAILED_TO_CREATE_SOCKET";
    default: return "UNKNOWN_ERROR_CODE";
  }
}

echosrv::~echosrv()
{
  
}
