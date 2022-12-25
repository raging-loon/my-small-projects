import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.zip.GZIPOutputStream;

public class gzip extends compressor{
  private static int sChunk = 8192;
  private GZIPOutputStream gzipOut;
  private String outFile;

  private int createZipStream(String outFile){
    this.outFile = outFile;

    try{
      FileOutputStream out = new FileOutputStream(this.outFile);
      gzipOut = new GZIPOutputStream(out);
    } catch (IOException e){
      return  ZipStatus.STATUS_FAILED_TO_CREATE_ARCHIVE;
    }
    return ZipStatus.STATUS_OK;
  }

  @Override
  public int compressFiles(ArrayList<String> inFiles, String outFile){
    if(inFiles == null | inFiles.size() != 1) return ZipStatus.STATUS_FAILED_TO_CREATE_ARCHIVE;
    if(!allFilesExist(inFiles)) return ZipStatus.STATUS_NON_EXISTENT_FILES;

    if(gzipOut == null) {
      int status;
      if((status = createZipStream(outFile)) != ZipStatus.STATUS_OK) return status;
    }


    byte[] buffer = new byte[sChunk];

    try{
      FileInputStream in = new FileInputStream(inFiles.get(0));
      int length;

      while((length = in.read(buffer, 0, sChunk)) != -1)
        gzipOut.write(buffer,0,length);

      in.close();
    } catch (FileNotFoundException e){
      return ZipStatus.STATUS_NON_EXISTENT_FILES;
    }
    catch(IOException e) {
      return ZipStatus.STATUS_FAILED_TO_COMPRESS;
    }

    try{ gzipOut.close(); }
    catch (IOException e){ return ZipStatus.STATUS_FAILED_TO_CLOSE_FILES; }



    return ZipStatus.STATUS_OK;
  }
}
