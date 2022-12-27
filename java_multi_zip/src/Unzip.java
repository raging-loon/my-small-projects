import java.io.FileInputStream;
import java.io.IOException;
import java.util.zip.ZipInputStream;

public class Unzip extends decompressor{

  private ZipInputStream zipIn;
  private int initDecompressor(String archiveName){
    try{
      FileInputStream in = new FileInputStream(archiveName);
      zipIn = new ZipInputStream(in);
    } catch (IOException e){
      return ZipStatus.STATUS_FAILED_TO_OPEN_FILES;
    }

    return ZipStatus.STATUS_OK;
  }

  @Override
  public int decompressFile(String archiveName, boolean printStatus) {
    if(archiveName == null | archiveName.equals("") | !fileExists(archiveName))
      return ZipStatus.STATUS_NON_EXISTENT_ARCHIVE;
    int status;
    if((status = initDecompressor(archiveName)) != ZipStatus.STATUS_OK)
      return status;


    return ZipStatus.STATUS_OK;
  }
}
