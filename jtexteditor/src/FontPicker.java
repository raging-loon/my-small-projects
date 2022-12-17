import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FontPicker extends JDialog implements ActionListener {
  private Font selectedFont;
  private JButton okButton;
  private boolean buttonClicked = false;
  public Font getSelectedFont() { return selectedFont; }


  public FontPicker(){
    // set to null in case the user closes the dialog without
    // selecting a font
    selectedFont = null;

    JList<String> fontList = getAllFonts();
    okButton = new JButton("Select");

    fontList.setBounds(100,100,75,75);

    setLayout(new BorderLayout());
    setTitle("Font Picker");
    setSize(400,600);

    add(new JScrollPane(fontList));
    add(okButton, BorderLayout.SOUTH);


    if(fontList.getSelectedIndex() != -1){
      JOptionPane.showMessageDialog(null, fontList.getSelectedValue());
    }

  }

  private JList getAllFonts(){
    JList flist;
    GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
    Font[] fonts = ge.getAllFonts();

    DefaultListModel<String> preList = new DefaultListModel<>();
    for(Font f : fonts){
      String name = f.getFontName();
      if(name.contains("Dialog")) continue;
      preList.addElement(name);
    }

    flist = new JList(preList);

    return flist;

  }


  public void actionPerformed(ActionEvent e){
    if(e.getSource() == okButton){
      buttonClicked = true;
    }
  }

  public Font getFontByName(String name){
    GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
    Font[] fonts = ge.getAllFonts();
    for(Font f : fonts){
      if(f.getFontName().equals(name)) return f;
    }
    return null;
  }




}
