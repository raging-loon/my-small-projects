#include "echosrv.h"
#include <iostream>
// this cannot be used any where else
// more readable way of setting error codes
#define SET_ERROR_CODES(errcode, server_error_code) error_code = errcode; last_server_error = server_error_code;


using namespace std;
/**
 * Default constructor
 * 
 * @param lport port to listen on
 * 
*/
echosrv::echosrv(unsigned int lport = 48876) : port(lport), 
                                               threadTable(MAX_CONNECTIONS){}


/**
 * Initialize the server. This includes:
 *  1. Setting an environment if nec.
 *  2. Creating the socket
 *  3. Binding and listening
 * 
 * @returns an appropriate ServerError code
 * 
*/
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


/**
 * Get the last error message and convert it into a string
 * 
 * @returns said string
 * 
*/
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


/**
 * Internal socket creation function for easier porting
 * and abstraction
 * 
 * @param portstr A string which is the port 
 * 
 * @returns an appropriate ServerError code
*/
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


/**
 * Internal binding function for abstraction and portablility
 * 
 * @returns an appropriate ServerError code
*/
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




/**
 * Internal listening function for portability and porting
 * 
 * @returns an appropriate ServerError code
*/
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

/**
 * Actually accept connections
 * 
 * Starts up a new thread using mthreads and callign 
 * echosrv::handleConnection
 * 
 * @returns an appropriate ServerError code
*/
ServerError echosrv::run()
{

  while(true)
  {
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if(clientSocket == INVALID_SOCKET) continue;

    connectionData tempConData = { this, clientSocket};
    
    // TODO: make this more efficient
    sockaddr_in clientInfo;
    int addrinSize = sizeof(sockaddr_in); 
    // get ip info
    getpeername(clientSocket, (sockaddr*)&clientInfo, &addrinSize);
    char socketPair[64];
    snprintf(socketPair, 64, "%s:%d", inet_ntoa(clientInfo.sin_addr), clientInfo.sin_port);
    socketList[clientSocket] = string(socketPair);

    logMessage(mlog_log_level::ML_INFO, socketList[clientSocket] + " new connection");

    mthread newThread = threadTable.mCreateThread(&handleConnection, &tempConData, NULL);    

    connectionList[clientSocket] = newThread;
    
  }
}


/**
 * Actually send and receive data 
 * 
 * @param clientdata void ptr to a connectionData struct
 * 
*/
mthreadFunction echosrv::handleConnection(void * clientdata)
{
  connectionData * dat = (connectionData *)clientdata;
  SOCKET clientSocket = dat->client;
  echosrv * srv = dat->srv;




  char recvbuf[512];
  int ires = 0, recvbuflen = sizeof(recvbuf);
  
  
  // main loop
  do{
    memset(recvbuf, 0, recvbuflen);
    ires = srv->es_recv(clientSocket, recvbuf, recvbuflen, 0);  

    

    if(ires > 0)
    {
        
      srv->es_send(clientSocket, recvbuf, ires, 0);
    
    }
    else if(ires == 0) {
      // connection closed
      srv->closeConnection(clientSocket);
      return 0;
    }
    else {
      srv->closeConnection(clientSocket);
      return 1;
    }


  } while(ires > 0);
  srv->closeConnection(clientSocket);

  return 0;
}


/**
 * Close a client socket
 * 
 * @param client the client
*/
void echosrv::closeConnection(SOCKET client)
{
  logMessage(mlog_log_level::ML_INFO, socketList[client] + " disconnected");

  threadTable.mDestroySingleThread(connectionList[client]);
  connectionList.erase(client);
  socketList.erase(client);
  closesocket(client);

  // WSACleanup(); // breaks the code
}

/**
 * Set up logging, this ideally would be called after
 * initialization.
 * 
 * @param filename name of the log file
 * @param flags mlog constructor flags
 * 
 * @return 0 if success or logger already init.
 * @return -1 if fail
 * 
*/
int echosrv::setLogging(std::string filename, unsigned int flags)
{
  if(logger) return 0;

  logger = new mlog(filename, flags);
  
  int status = logger->init();
  
  if(status == -1) delete logger;
  logMessage(mlog_log_level::ML_STATUS, "Server logging starting");

  return status;
}


/**
 * Write a message if the logger exists
 * 
 * @param l log level
 * @param message
*/
void echosrv::logMessage(mlog_log_level l, std::string message)
{
  if(logger) logger->write(l, message);
}


int echosrv::es_recv(SOCKET sock, char * buf, int buflen, int flags)
{
  int ret = recv(sock, buf, buflen, flags);

  logMessage(mlog_log_level::ML_INFO, socketList[sock] + " sent: " + buf);

  return ret;

}


int echosrv::es_send(SOCKET sock, const char * buf, int buflen, int flags)
{
  int ret = send(sock, buf, buflen, flags);

  return ret;
}





echosrv::~echosrv()
{
  if(result) freeaddrinfo(result);  
  if(logger) delete logger;
  closesocket(serverSocket);

  

  WSACleanup();  
}
