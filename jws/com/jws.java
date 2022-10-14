package com;

import com.jwsConfig.*;
import com.httpRequest;
import java.io.*;
import java.net.*;

public class jws{

  private static jwsConfig mainConfiguration;  
  private static ServerSocket server;


  public static void main(String[] args) {
    
    mainConfiguration = new jwsConfig();
    mainConfiguration.parseConfigurationFile("jws.conf");

    
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
    }
    
  }



  

}