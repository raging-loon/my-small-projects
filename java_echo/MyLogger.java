import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Calendar;

public class MyLogger {
  private String logLocation;
  private File logFile;
  private PrintWriter outputWriter;

  public static final int INFO = 1;
  public static final int SEVERE = 2;

  public MyLogger(String location) throws IOException{
    
    logLocation = location;

    logFile = new File(logLocation);
        
    // try to create a new file
    logFile.createNewFile();

    outputWriter = new PrintWriter(logFile);
    
  }


  public void log(int level, String msg){
    String toWrite = Calendar.getInstance().getTime().toString() + "\n" + 
                      logLevelToString(level) + ": " + msg;

    outputWriter.println(toWrite);    
    outputWriter.flush();
  }

  private String logLevelToString(int level){
    
    switch(level){
      case INFO: return "INFO";
      case SEVERE: return "SEVERE";
      default: return "UNKNOWN LOG LEVEL";

    }
  }


  
}
