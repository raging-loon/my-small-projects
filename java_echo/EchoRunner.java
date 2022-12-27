import java.io.IOException;

public class EchoRunner {
  
  public static void main(String[] args){
    EchoServer server;
    try{
      server = new EchoServer(123, "echoserver.log");
      
      server.runServer();
      
    } catch(FailedToStartServerException e){
      System.out.println("Failed to start server");
      System.exit(1);
    }
    catch(IOException e2){

    }

  }
}
