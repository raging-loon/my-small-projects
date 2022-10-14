package com;
import com.InvalidHttpRequest;
public class httpRequest {
  private String[] requestBuffer;

  enum httpVerb{
    HTTPGet
  };  

  private httpVerb verb;
  private String filePath;

  public httpRequest(String fullRequest){
    requestBuffer = fullRequest.split("\n");


  }

  public void parseHttp() throws InvalidHttpRequest{
    if(requestBuffer.length == 0) 
      throw new InvalidHttpRequest();
    
    String requestLine = requestBuffer[0];
    

  }

}
