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
    
    // e.g. GET /api/config HTTP/1.1 
    String requestLine = requestBuffer[0];
    parseRequestLine(requestLine);
    
  }

  private void parseRequestLine(String line) throws InvalidHttpRequest{
    String[] requestLineBuf = line.split(" ");
    if(requestLineBuf.length < 3){
      throw new InvalidHttpRequest();
    }

    verb = parseVerb(requestLineBuf[0]);
    

  }

  private httpVerb parseVerb(String verb) throws InvalidHttpRequest{
    switch(verb.toUpperCase()){
      case "GET":
        return httpVerb.HTTPGet;
      default:
       throw new InvalidHttpRequest();
    }
  }

}
