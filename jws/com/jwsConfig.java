package com;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
    else if(assignBuffer[0].equals("listen_addr"))
      setListenIpAddr(assignBuffer[1]);
    else if(assignBuffer[0].equals("root_dir"))
      setRootDirectory(assignBuffer[0]); 
    else if(assignBuffer[0].equals("blocked_ips"))
      setBlockedIPList(assignBuffer[1]); 
  }

  private void setListenIpAddr(String ipAddr){
    Pattern p = Pattern.compile("^(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\." +
    "(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)$");
    Matcher m = p.matcher(ipAddr);
    if(!m.matches()){
      System.out.println("Invalid IP Address: " + ipAddr);
      System.exit(1);
    }
    this.listenIpAddr = ipAddr;
  }

  private void setListenPort(String listenPort){
    try{
      this.listenPort = Integer.parseInt(listenPort);
    } catch(NumberFormatException e){
      System.out.println("Invalid port found at line " + parsedLines);
      System.exit(1);
    }
  }

  private void setRootDirectory(String path){
    this.rootDirectory = path;
  }

  private void setBlockedIPList(String ipList){
    String list = ipList.substring(ipList.indexOf("[") + 1, ipList.indexOf("]"));
    for(String addr : list.split(",")){
      if(isValidIPv4Addr(addr))
        this.blockedIpList.add(addr);
      else
        System.out.println("Invalid IPv4 addr "+ addr + ". Skipping");
    }
  }

  public static boolean isValidIPv4Addr(String possibleAddress){
    Pattern p = Pattern.compile("^(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\." +
    "(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)$");
    Matcher m = p.matcher(possibleAddress);

    return m.matches();
  }


  public boolean isBlockedIPAddr(String ipAddr){
    return blockedIpList.contains(ipAddr);
  }

  public String getListenAddr(){ return listenIpAddr; }

  public Integer getListenPort(){ return listenPort; }


  
}

