import java.io.File;

public class decompressor {

  public boolean fileExists(String archiveName){
    File f = new File(archiveName);
    if(!f.exists() | f.isDirectory()) return false;

    return true;
  }
  public int decompressFile(String archiveName, boolean printStatus){ return ZipStatus.STATUS_GENERAL_FAILURE; }


  public String getSourceFilename(String archiveName, String extension){
    return archiveName.substring(0, archiveName.length() - extension.length());
  }
}
