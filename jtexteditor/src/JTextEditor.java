import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

public class JTextEditor implements ActionListener {
  private JFrame mainWindow;

  // menus
  private JMenuBar mainMenuBar;

  // file menu
  private JMenu fileMenu;
  private JMenuItem openFileMenu;
  private JMenuItem saveFileMenu;


  private JTextArea editorArea;

  public JTextEditor(){
    mainWindow = new JFrame("JTextEditor - No File Opened");

    //  set up our menues
    mainMenuBar = new JMenuBar();
    mainWindow.setJMenuBar(mainMenuBar);

    fileMenu = new JMenu("File");
    openFileMenu = new JMenuItem("Open...");
    saveFileMenu = new JMenuItem("Save");

    openFileMenu.addActionListener(this);
    saveFileMenu.addActionListener(this);

    fileMenu.add(openFileMenu);
    fileMenu.add(saveFileMenu);

    mainMenuBar.add(fileMenu);

    // set up the editor

    editorArea = new JTextArea();

    editorArea.setFont(new Font("SansSerif.plain",Font.PLAIN, 12));
    mainWindow.add(editorArea);


  }

  public void run(){
    mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    mainWindow.setSize(400,400);
    mainWindow.setVisible(true);
  }

  public void actionPerformed(ActionEvent e){
    if(e.getSource() == openFileMenu){
      openNewFile();

    }
    else if(e.getSource() == saveFileMenu){
      System.out.println("User clicked on save menu");
    }
  }

  private void openNewFile(){
    String fileName;
    String fileContents;
    JFileChooser jfc = new JFileChooser();
    int status = jfc.showOpenDialog(null);

    if(status != JFileChooser.APPROVE_OPTION) return;
    fileName = jfc.getSelectedFile().getAbsolutePath();

    fileContents = getFileContents(fileName);

    if(fileContents != null){
      editorArea.setText(fileContents);
      mainWindow.setTitle("JTextEditor - " + fileName);
    }
  }


  private String getFileContents(String filename){
    String contents = null;
    try{
      contents = Files.readString(Path.of(filename));
    } catch(Exception e){
      JOptionPane.showMessageDialog(null,"Failed to read" + filename, "Error",JOptionPane.ERROR_MESSAGE);

    }
    return contents;
  }
}
