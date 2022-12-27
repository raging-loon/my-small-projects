import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class EchoClient {
  private Socket serverSocket;
  private InputStream in;
  private OutputStream out;
  private PrintWriter pout;

  public int connectToEchoServer(String ipAddress, int port){
    try{
      serverSocket = new Socket(ipAddress, port);
      in = serverSocket.getInputStream();
      out = serverSocket.getOutputStream();
      pout = new PrintWriter(out, true);
    } catch (Exception e){
      return -1;
    }
    return 0;
  }

  public String sendAndRecv(String toSend){
    String recvData = null;

    BufferedReader bin = new BufferedReader(new InputStreamReader(in));

    pout.println(toSend);

    try { recvData = bin.readLine(); }
    catch (IOException e){}

    

    return recvData;
  }

  public void disconnect(){
    try{ serverSocket.close(); }
    catch(Exception e){}
  }

  public static void main(String[] args){
    int serverPort;
    if(args.length == 0) serverPort = 123;
    else serverPort = Integer.parseInt(args[0]);

    EchoClient ec = new EchoClient();
    ec.connectToEchoServer("127.0.0.1", serverPort);
    
    String dataToSend = "";

    Scanner input = new Scanner(System.in);

    while(true){
      System.out.print("> ");
      dataToSend = input.nextLine();
      if(dataToSend.equals("stop")) break;

      String dataRecv = ec.sendAndRecv(dataToSend);

      System.out.println("Received back: " + dataRecv);

    }
    input.close();
    ec.disconnect();
    

    
  }


}
