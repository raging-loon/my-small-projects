
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Path;

public class JTextEditor implements ActionListener {
  private final JFrame mainWindow;
  private final JScrollPane editorScroller;
  private final JMenuItem openFileMenu;
  private final JMenuItem saveFileMenu;


  private final JTextArea editorArea;

  // save status
  private boolean currentFileSaved = false;

  private final EditorSettings settings;
  private String currentlyOpenedFile = "";
  public JTextEditor(){
    mainWindow = new JFrame("JTextEditor - No File Opened");
    settings = new EditorSettings(this);
    //  set up our menus

    // menus
    JMenuBar mainMenuBar = new JMenuBar();
    mainWindow.setJMenuBar(mainMenuBar);

    // file menu
    JMenu fileMenu = new JMenu("File");
    openFileMenu = new JMenuItem("Open...");
    saveFileMenu = new JMenuItem("Save");

    openFileMenu.addActionListener(this);
    saveFileMenu.addActionListener(this);

    fileMenu.add(openFileMenu);
    fileMenu.add(saveFileMenu);

    mainMenuBar.add(fileMenu);
    mainMenuBar.add(settings.getSettingsMenu());
    // set up the editor

    editorArea = new JTextArea();

    editorArea.setFont(new Font("SansSerif.plain",Font.PLAIN, 12));
    editorScroller = new JScrollPane(editorArea);
    mainWindow.add(editorScroller);


  }

  public void run(){
    mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    mainWindow.setSize(400,400);
    mainWindow.setVisible(true);
  }

  public void actionPerformed(ActionEvent e){
    Object source = e.getSource();

    if(source instanceof JMenuItem){
      if(e.getSource() == openFileMenu){
        openNewFile();

      }
      else if(e.getSource() == saveFileMenu){
        saveFile();
      } else {
        settings.actionPerformed(e);
      }

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
      currentlyOpenedFile = fileName;
      
    }
  }


  private String getFileContents(String filename){
    String contents = null;
    try{
      contents = Files.readString(Path.of(filename));
    } catch(Exception e){
      JOptionPane.showMessageDialog(null,"Failed to read " + filename, "Error",JOptionPane.ERROR_MESSAGE);

    }
    return contents;
  }

  private void createFile(){
    String folderName;


    JFileChooser jfc = new JFileChooser();
    jfc.setDialogTitle("Choose a folder");
    jfc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

    int retval = jfc.showSaveDialog(null);
    if(retval == JFileChooser.APPROVE_OPTION){
      folderName = jfc.getSelectedFile().getAbsolutePath();

      String filename = JOptionPane.showInputDialog("Enter a filename: ");

      JOptionPane.showMessageDialog(null, folderName + filename);
      if(!folderName.endsWith("/")) folderName += "/";
      currentlyOpenedFile = folderName + filename;
    }

  }

  private void dumpFileContents(){
    try{
      FileWriter fw = new FileWriter(currentlyOpenedFile);
      fw.append(editorArea.getText());
      fw.close();
    } catch(Exception e){
      JOptionPane.showMessageDialog(mainWindow, e.getStackTrace(), "Error opening" + currentlyOpenedFile, JOptionPane.ERROR_MESSAGE);
    }
    mainWindow.setTitle("JTextEditor - " + currentlyOpenedFile);

  }

  private void saveFile(){
    if(currentlyOpenedFile.equals("")){
      createFile();
    }

    dumpFileContents();

  }
}
