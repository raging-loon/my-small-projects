package com;
import com.jwsConfig.*;

public class jws{

  private static jwsConfig mainConfiguration;  

  public static void main(String[] args) {
    mainConfiguration = new jwsConfig();
    mainConfiguration.parseConfigurationFile("jws.conf");
    
  }
}