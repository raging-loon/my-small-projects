package com;

import java.util.Date;
import java.lang.StringBuilder;
public class httpResponse {
  private int statusCode;
  private String codeReason;
  private Date date;
  private String serverID;

  private int ContentLength;
  private int ContentType;

  private StringBuilder contents;

  public httpResponse(){
    contents = new StringBuilder();
    date = new Date();

  }

  private void appendContent(String content){
    contents.append(content);
  }  

  public String getFullyFormatedRequest(){
    StringBuilder responceBuilder = new StringBuilder();
    responceBuilder.append("HTTP/1.1 " + statusCode + " " + codeReason + "\n");

    return responceBuilder.toString();
  }


}
