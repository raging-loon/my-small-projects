package com;

import com.jwsConfig.*;
import com.httpRequest;
import java.io.*;
import java.net.*;
import java.util.Date;

/* TODOS
 *  - Add SSL/TLS support
 *  - Add security, request, and error logging
 */


public class jws{

  private static jwsConfig mainConfiguration;  
  private static ServerSocket server;
  private static String configFilePath = "jws.conf";
  
  private static void printHelp(){
    System.err.println("Usage: java com.jws [optional]");
    System.err.println("\t-c <config>\tspecify config path to use");
    System.err.println("\t-v, --version\tprint version");
    System.err.println("\t-h, --help\tprint this message");

    System.exit(0);

  }

  private static void printVersion(){
    System.err.println("JWS - Java Web Server v1.0.0");
    System.exit(0);
  }

  private static void parseCMDArgs(String[] args){
    
    for(int i = 0; i < args.length; i++){
      if(args[i].equals("-c")){
        if(i + 1 > args.length){
          System.err.println("-c requires and argument");
          System.exit(1);
        } else {
          configFilePath = args[++i];
        }
      }

      else if(args[i].matches("-v|--version"))
        printVersion();
      else if(args[i].matches("-h|--help"))
        printHelp();
    }

  }

  public static void main(String[] args) {
    parseCMDArgs(args);

    mainConfiguration = new jwsConfig();
    mainConfiguration.parseConfigurationFile(configFilePath);
    Date date = new Date();
    System.out.println("Server starting at: " + date.toString());
    
    try{
      server = new ServerSocket(mainConfiguration.getListenPort());
      while(true){
        Socket clientSock = server.accept();
        String ipAddr = clientSock.getInetAddress().toString();
        ipAddr = ipAddr.substring(ipAddr.indexOf("/") + 1);
        System.out.println("New connection " + ipAddr + ":" + clientSock.getPort());
        if(mainConfiguration.isBlockedIPAddr(ipAddr)){
          System.out.println("Blocking " + ipAddr + " based on configuration. TODO Implement logging");
          clientSock.close();
          continue;
        }

        InputStream input = clientSock.getInputStream();

        BufferedReader reader = new BufferedReader(new InputStreamReader((input)));
        
        
        String recv;

        StringBuilder clientInput = new StringBuilder();

        do{
          recv = reader.readLine();
          
          clientInput.append(recv + "\n");
        
        } while(!recv.equals(""));      

        handleRequest(clientSock, clientInput.toString());        
        
        clientSock.close();        
      }
      
    } catch (IOException e){
      System.out.println("Failed to start server");
      e.printStackTrace();
      System.exit(1);
    }
    
  }
  private static void handleRequest(Socket client, String input){
    httpRequest request = new httpRequest(input);
    try{
      request.parseHttp();
    } catch (InvalidHttpRequest e){
      System.out.println("Invalid HTTP request received. TODO Log");
      return;
    }
    

    requestHandler req = null;

    switch(request.getHTTPVerb())
    {
      case HTTPGet:
        req = new getRequestHandler(request.getFilePath());
        break;

      default:
        System.out.println("Unknown HTTP Verb: " + request.getHTTPVerb());
        return;
    }
    req.parseRequest(request);

    req.runHandler(client, input);



  }



  

}