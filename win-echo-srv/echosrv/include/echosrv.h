#pragma once

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_CONNECTIONS         32


enum class ServerError{
  OK,
  WSASTARTUP_ERROR,
  FAILED_TO_LISTEN,
  FAILED_TO_CREATE_SOCKET,
  FAILED_TO_BIND,
  FAILED_GETADDRINFO
};


class echosrv{  

  HANDLE connectionTable[MAX_CONNECTIONS];
  DWORD tidTable[MAX_CONNECTIONS];

  // connections count, 
  unsigned int ccount = 0, tcount = 0;

  WSAData wsaData;
  
  SOCKET serverSocket = INVALID_SOCKET;

  struct addrinfo * result = NULL,
                  *ptr = NULL,
                   hints;

  unsigned int port;
  unsigned int error_code;


  ServerError last_server_error;

  ServerError createSocket(char * portstr);
  ServerError bindSocket();
  ServerError listenSocket();
  static void closeConnection(SOCKET client);
  static void handleConnection(void * clientsocket);

  void startNewClientThread(SOCKET client);

public:
  echosrv(unsigned int lport);
  ~echosrv();
  ServerError init();  
  unsigned int get_error_code() { return error_code; }
  ServerError get_server_error_code() 
                                { return last_server_error; }

  
  ServerError run();


  char * get_err_msg();

};