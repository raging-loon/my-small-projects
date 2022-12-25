import java.io.File;
import java.util.ArrayList;

public class compressor {

  public int compressFiles(ArrayList<String> inFiles, String outFile){ return ZipStatus.STATUS_GENERAL_FAILURE; }

  public boolean allFilesExist(ArrayList<String> fileList){
    for(String i : fileList){
      File f = new File(i);
      if(!f.exists() | f.isDirectory()) return false;
    }
    return true;
  }

}


