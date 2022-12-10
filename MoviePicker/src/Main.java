import javax.swing.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;

public class Main {
  private static ArrayList<String> movieNames;

  private static String getRandomMovie(){
    Random r = new Random();
    return movieNames.get(r.nextInt(movieNames.size()));
  }

  private static void getMovieNames(){
    try(BufferedReader br = new BufferedReader(new FileReader("src/movie-list.txt"))){

      String line;

      while((line = br.readLine()) != null)
        movieNames.add(line);


    } catch(Exception e){
      System.out.println("Failed to open file");
      e.printStackTrace();
      System.exit(1);
    }
  }

  private static void rewriteFile(String toExclude){
    movieNames.remove(toExclude);
    try {
      FileWriter fw = new FileWriter("src/movie-list.txt");
      for(String i : movieNames){
        System.out.println("Adding: " + i);
        fw.write(i + System.lineSeparator());
      }
      fw.close();
    } catch(IOException e){
      e.printStackTrace();
      JOptionPane.showMessageDialog(null, e.getMessage(), "Error!", JOptionPane.ERROR_MESSAGE);
      System.exit(1);
    }

  }
  public static void main(String[] args) {
    movieNames = new ArrayList<>();
    getMovieNames();

    int result = -1;

    while(true){
      String movieName = getRandomMovie();
      result = JOptionPane.showConfirmDialog(null, movieName);
      if(result == 0) {
        rewriteFile(movieName);
        break;
      }
      else if(result == 2) break;
    }




  }
}