package com;

import java.net.Socket;

import com.requestHandler;

public class getRequestHandler extends requestHandler{
  private String fullFilePath;

  public getRequestHandler(String baseFilePath){
    if(baseFilePath.equals("/")) baseFilePath += "index.html";
    
    fullFilePath = baseFilePath;


  }

  
  @Override
  public void runHandler(Socket clientSocket, String formatedDataToSend){

    System.out.println("Should be sending our data");
  }


  @Override
  public void parseRequest(httpRequest req){
    


  }
}
