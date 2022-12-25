import java.io.*;
import java.util.zip.GZIPInputStream;

public class gunzip extends decompressor {
  private static final int sChunk = 8192;
  private GZIPInputStream zipin;


  private int initUnzipStream(String archiveName){
    try{
      FileInputStream in = new FileInputStream(archiveName);
      zipin = new GZIPInputStream(in);
    } catch (FileNotFoundException e){
      return ZipStatus.STATUS_NON_EXISTENT_ARCHIVE;
    } catch(IOException e){
      return ZipStatus.STATUS_FAILED_TO_OPEN_FILES;
    }

    return ZipStatus.STATUS_OK;
  }
  @Override
  public int decompressFile(String archiveName, boolean printStatus){
    if(archiveName == null | archiveName.equals("") | !fileExists(archiveName))
      return ZipStatus.STATUS_NON_EXISTENT_ARCHIVE;
    if(zipin == null) initUnzipStream(archiveName);


    String source = getSourceFilename(archiveName, ".gz");

    byte[] buffer = new byte[sChunk];

    try{
      FileOutputStream out = new FileOutputStream(source);
      int length;
      while((length = zipin.read(buffer, 0, sChunk)) != -1)
        out.write(buffer, 0, length);
      out.close();
    } catch(IOException e){
      return ZipStatus.STATUS_FAILED_TO_DECOMPRESS;
    }

    try{ zipin.close(); }
    catch(IOException e) { return ZipStatus.STATUS_FAILED_TO_CLOSE_FILES; }
    return ZipStatus.STATUS_OK;
  }
}
