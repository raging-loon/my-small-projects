import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class EchoServer{
  
  private ServerSocket listener;
  private boolean doLogging = false;
  private MyLogger logger;
  private int initServer(int port){
    if(port < 0 || port > 65535) return -1;

    try{
      listener = new ServerSocket(port);

    } catch (IOException e){
      return -1;
    }
    return 0;
  }

  public EchoServer(int port) throws FailedToStartServerException{
    if(initServer(port) == -1){
      throw new FailedToStartServerException();      
    }
  }

  public EchoServer(int port, String logFileName) throws FailedToStartServerException,
                                                             IOException{
    this(port);
    doLogging = true;
    
    logger = new MyLogger(logFileName);


  }

  public void runServer(){

serverloop:
    while(true){
      try{
        Socket client = listener.accept();
        InputStream in = client.getInputStream();
        OutputStream out = client.getOutputStream();
        BufferedReader bin = new BufferedReader(new InputStreamReader(in));
        PrintWriter pout = new PrintWriter(out, true);
        String clientData = "";
        while(!clientData.equals("exit")){ 
          clientData = bin.readLine();
          
          if(clientData == null || clientData.equals("exit")) break;
          if(clientData.equals("shutdown")) break serverloop;
          System.out.println("recevied: " + clientData);
          logger.log(MyLogger.INFO,  client.getInetAddress().toString() + ":" + client.getPort() + ": " +clientData);
          pout.println(clientData);

        }

        client.close();

        
      } catch(IOException e){
        System.out.println("Failed to accept client");
      }
      
     
    }
    try{ listener.close(); }
    catch(Exception e){}
  }


}