#pragma once

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

enum class ServerError{
  OK,
  WSASTARTUP_ERROR,
  FAILED_TO_LISTEN,
  FAILED_TO_CREATE_SOCKET,
  FAILED_TO_BIND,
};



class echosrv{  
  WSAData wsaData;
  unsigned int port;
  unsigned int error_code;
  ServerError last_server_error;
public:
  echosrv(unsigned int lport);
  ~echosrv();
  ServerError init();  
  unsigned int get_error_code() { return error_code; }
  ServerError get_server_error_code() 
                                { return last_server_error; }

  char * get_err_msg();

};