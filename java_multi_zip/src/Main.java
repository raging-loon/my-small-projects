import java.util.ArrayList;

public class Main {
  public static void main(String[] args) {
    ArrayList<String> fileList = new ArrayList<>();
    fileList.add("testfiles/java_multi_zip.iml");
    fileList.add("testfiles/tux.png");
    fileList.add("testfiles/pink_floyd_animals.png");


    Zip z = new Zip();
    if(z.compressFiles(fileList, "test.zip") != ZipStatus.STATUS_OK){
      System.out.println("Failed to create archive");
    }
  }
}