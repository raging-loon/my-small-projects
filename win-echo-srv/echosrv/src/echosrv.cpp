#include "echosrv.h"
#include <iostream>
// this cannot be used any where else
// more readable way of setting error codes
#define SET_ERROR_CODES(errcode, server_error_code) error_code = errcode; last_server_error = server_error_code;

echosrv::echosrv(unsigned int lport = 48876) : port(lport), 
                                               threadTable(MAX_CONNECTIONS){}

ServerError echosrv::init()
{ 
  int ires;
  char portstr[16]; 
  
  std::sprintf(portstr, "%d", port);
  

  if((ires = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
  {
    SET_ERROR_CODES(ires, ServerError::WSASTARTUP_ERROR)
    return ServerError::WSASTARTUP_ERROR;
  }

  // createSocket sets the error codes for us
  if(createSocket(portstr) != ServerError::OK){
    return last_server_error;
  }


  if(bindSocket() != ServerError::OK){
    return last_server_error;
  } 
  if(listenSocket() != ServerError::OK){
    return last_server_error;
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
    case ServerError::FAILED_GETADDRINFO: return "FAILED_GETADDRINFO";
    default: return "UNKNOWN_ERROR_CODE";
  }
}



ServerError echosrv::createSocket(char * portstr)
{
  int res;
  

  ZeroMemory(&hints, sizeof(hints));

  hints.ai_family = AF_INET; 
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;


  if((res = getaddrinfo(NULL, portstr, &hints, &result)) != 0)
  {
    SET_ERROR_CODES(res, ServerError::FAILED_GETADDRINFO)
    WSACleanup();
    freeaddrinfo(result);
    return ServerError::FAILED_GETADDRINFO;
  }



  serverSocket = socket(
                    result->ai_family, 
                    result->ai_socktype, 
                    result->ai_protocol);

  if(serverSocket == INVALID_SOCKET)
  {
    SET_ERROR_CODES(WSAGetLastError(), ServerError::FAILED_TO_CREATE_SOCKET)
    WSACleanup();
    freeaddrinfo(result);

    return ServerError::FAILED_TO_CREATE_SOCKET;
  }




  if(result) freeaddrinfo(result);

  return ServerError::OK;
}

ServerError echosrv::bindSocket()
{
  int res;
  if(serverSocket == INVALID_SOCKET)
  {
    freeaddrinfo(result);
    WSACleanup();
    SET_ERROR_CODES(0, ServerError::FAILED_TO_BIND)
    return ServerError::FAILED_TO_BIND;
  }

  if((res = bind(serverSocket, result->ai_addr, (int)result->ai_addrlen)) == SOCKET_ERROR)
  {
    SET_ERROR_CODES(WSAGetLastError(), ServerError::FAILED_TO_BIND)
    closesocket(serverSocket);
    WSACleanup();
    freeaddrinfo(result);
    return ServerError::FAILED_TO_BIND;
  }
  if(result) freeaddrinfo(result);  


  return ServerError::OK;
}

ServerError echosrv::listenSocket()
{
  
  if(listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
  {
    SET_ERROR_CODES(WSAGetLastError(), ServerError::FAILED_TO_LISTEN)

    closesocket(serverSocket);
    WSACleanup();
    return ServerError::FAILED_TO_LISTEN;
  }


  return ServerError::OK;
}


ServerError echosrv::run()
{

  while(true)
  {
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if(clientSocket == INVALID_SOCKET) continue;

    connectionData tempConData = { this, clientSocket};
    
    mthread newThread = threadTable.mCreateThread(&handleConnection, &tempConData, NULL);    
    
    connectionList[clientSocket] = newThread;
    
  }
}

// THREADED FUNCTION
mthreadFunction echosrv::handleConnection(void * clientdata)
{
  connectionData * dat = (connectionData *)clientdata;
  SOCKET clientSocket = dat->client;
  echosrv * srv = dat->srv;

  char recvbuf[512];
  int ires, isres, recvbuflen = sizeof(recvbuf);

  do{
    memset(recvbuf, 0, recvbuflen);
    ires = recv(clientSocket, recvbuf, recvbuflen, 0);


    if(ires > 0)
    {
      printf("recv: %s\n",recvbuf);
    
      send(clientSocket, recvbuf, ires-2, 0);
    
    }
    else if(ires == 0) {
      // connection closed
    }
    else {
      printf("Recv failed\n");
      srv->closeConnection(clientSocket);
      return 1;
    }


  } while(ires > 0);
  srv->closeConnection(clientSocket);

  return 0;
}



void echosrv::closeConnection(SOCKET client)
{
  threadTable.mDestroySingleThread(connectionList[client]);
  closesocket(client);

  WSACleanup();
}


echosrv::~echosrv()
{

  if(result) freeaddrinfo(result);  
  closesocket(serverSocket);
  WSACleanup();  
}
