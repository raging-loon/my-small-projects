#pragma once

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>

#include "mthreads.h"
#include "mlog.h"

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

  mthreads threadTable;

  std::map<SOCKET, mthread> connectionList;
  std::map<SOCKET, std::string> socketList;

  WSAData wsaData;
  
  SOCKET serverSocket = INVALID_SOCKET;

  struct addrinfo * result = NULL,
                  *ptr = NULL,
                   hints;

  unsigned int port;
  unsigned int error_code;

  mlog * logger = nullptr;
  

  ServerError last_server_error;

  // these function just call the OS
  ServerError createSocket(char * portstr);
  ServerError bindSocket();
  ServerError listenSocket();


  static mthreadFunction handleConnection(void * clientsocket);

  void startNewClientThread(SOCKET client);

  void logMessage(mlog_log_level l, std::string message);

public:
  echosrv(unsigned int lport);
  ~echosrv();
  ServerError init();  
  unsigned int get_error_code() { return error_code; }
  ServerError get_server_error_code() 
                                { return last_server_error; }

  
  int setLogging(std::string filename, unsigned int flags);

  ServerError run();
  void closeConnection(SOCKET client);

  // why implement these? Logging
  int es_recv(SOCKET sock, char * buf, int buflen, int flags);
  int es_send(SOCKET sock, const char * buf, int buflen, int flags);

  char * get_err_msg();

};

struct connectionData{
  echosrv * srv;
  SOCKET client;  
};
