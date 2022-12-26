import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class Zip extends compressor{
  private ZipOutputStream zipout;
  private final int sChunk = 1024;
  private int writeEntry(String filename){
    // this file has already been checked to
    // make sure it exists and is not a dir
    File inFile = new File(filename);
    try{
      FileInputStream in = new FileInputStream(inFile);
      byte[] buffer = new byte[sChunk];
      int length;
      while((length = in.read(buffer)) != -1)
          zipout.write(buffer, 0, length);
      in.close();

    } catch(IOException e){
      return ZipStatus.STATUS_FAILED_TO_COMPRESS;
    }


    return ZipStatus.STATUS_OK;
  }
  private int initCompressor(String outFile){
    try{
      FileOutputStream out = new FileOutputStream(outFile);
      zipout = new ZipOutputStream(out);
    } catch(IOException e){
      return ZipStatus.STATUS_FAILED_TO_CREATE_ARCHIVE;
    }
    return ZipStatus.STATUS_OK;
  }
  @Override
  public int compressFiles(ArrayList<String> inFiles, String outFile){
    if(inFiles == null | inFiles.size() == 0 | !allFilesExist(inFiles)) return ZipStatus.STATUS_NON_EXISTENT_FILES;
    int status;

    if((status = initCompressor(outFile)) != ZipStatus.STATUS_OK)
      return status;


    try{
      for(String i : inFiles){
        ZipEntry entry = new ZipEntry(i);
        zipout.putNextEntry(entry);
        writeEntry(i);

      }
    } catch(IOException e){
      return ZipStatus.STATUS_FAILED_TO_COMPRESS;
    }

    try { zipout.close(); }
    catch(IOException e) { return ZipStatus.STATUS_FAILED_TO_CLOSE_FILES; }

    return ZipStatus.STATUS_OK;

  }

}
