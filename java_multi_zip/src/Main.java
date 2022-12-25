import java.util.ArrayList;

public class Main {
  public static void main(String[] args) {
//    ArrayList<String> fileList = new ArrayList<>();
//    String filename = "testfiles/pooh_batemen.png";
//
//    fileList.add(filename);
//    String zipname = filename + ".gz";
//
//    gzip zip = new gzip();
//
//    if(zip.compressFiles(fileList, zipname) != ZipStatus.STATUS_OK){
//      System.out.println("Failed to create archive");
//    }
    gunzip gz = new gunzip();

    if(gz.decompressFile("testfiles/pooh_batemen.png.gz", false) != ZipStatus.STATUS_OK){
      System.out.println("Failed to open archive");
    }

  }
}