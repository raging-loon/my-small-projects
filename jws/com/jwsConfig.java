package com;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import javax.sound.midi.Soundbank;
public class jwsConfig {
  private String listenIpAddr;
  private Integer listenPort;
  private String rootDirectory;
  private ArrayList<String> blockedIpList;
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
        String curLine = fileReader.nextLine();

        if(curLine.length() < 2 || curLine.contains("#")) 
          continue;
        
        

      }

      fileReader.close();

    } catch (FileNotFoundException e){
      System.out.println("Config File " + configFile + " not found. Exiting");
      System.exit(1);
    }
  }


  
}
