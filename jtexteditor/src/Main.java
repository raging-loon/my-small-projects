import javax.swing.*;

public class Main
{

  public static void main(String[] args) {
    try{
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

   } catch(Exception e){
      JOptionPane.showMessageDialog(null, "Could not load system look and feel. Using builtin");
    }


    JTextEditor jt = new JTextEditor();
    jt.run();
  }
}