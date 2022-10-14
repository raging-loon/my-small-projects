package com;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class jwsConfig {
  private String listenIpAddr;
  private Integer listenPort;
  private String rootDirectory;
  private ArrayList<String> blockedIpList;
  private int parsedLines = 0;

  // private bool isEncrypted
  
  
  /**
   * Init the class
   */
  public jwsConfig(){
    blockedIpList = new ArrayList<>();
  }

  /**
   * Parse the config
   * @param configFile location of configuration file
   */
  public void parseConfigurationFile(String configFile){
    try{
      File configFileObj = new File(configFile);

      Scanner fileReader = new Scanner(configFileObj);

      while(fileReader.hasNextLine()){
        parsedLines++;
        String curLine = fileReader.nextLine();

        if(curLine.length() < 2 || curLine.contains("#")) 
          continue;
        
        confAssignment(curLine);
        
      }

      fileReader.close();

    } catch (FileNotFoundException e){
      System.out.println("Config File " + configFile + " not found. Exiting");
      System.exit(1);
    }
  }

  private void confAssignment(String buff){
    String[] assignBuffer = buff.split("=");

    if(assignBuffer.length < 2){
      System.out.println("Invalid config: " + parsedLines + " " + buff);
    }

    if(assignBuffer[0].equals("listen_port"))
      setListenPort(assignBuffer[1]);

  }

  private void setListenIpAddr(String ipAddr){
    this.listenIpAddr = ipAddr;
  }

  private void setListenPort(String listenPort){
    try{
      this.listenPort = Integer.parseInt(listenPort);
      System.out.println(listenPort);
    } catch(NumberFormatException e){
      System.out.println("Invalid port found at line " + parsedLines);
      System.exit(1);
    }
  }


}
