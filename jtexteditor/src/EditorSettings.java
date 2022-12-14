import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EditorSettings implements ActionListener{
  private final JMenu settingsMenu;
  private final JMenuItem fontPickerMenu;
  private final JMenuItem uiPickerMenu;
  private final JMenuItem wordWrapEnabledMenu;
  public EditorSettings(JTextEditor j){
    settingsMenu = new JMenu("Settings");

    fontPickerMenu = new JMenuItem("Choose Font");
    uiPickerMenu = new JMenuItem("Change UI Theme");
    wordWrapEnabledMenu = new JMenuItem("Word Wrap");

    fontPickerMenu.addActionListener(j);
    uiPickerMenu.addActionListener(j);
    wordWrapEnabledMenu.addActionListener(j);

    settingsMenu.add(fontPickerMenu);
    settingsMenu.add(uiPickerMenu);
    settingsMenu.add(wordWrapEnabledMenu);
  }

  public JMenu getSettingsMenu() { return this.settingsMenu; }
  public JMenuItem getFontPickerMenu() { return this.fontPickerMenu; }
  public JMenuItem getUIPickerMenu() { return this.uiPickerMenu; }
  public JMenuItem getWordWrapEnabledMenuPickerMenu() { return this.wordWrapEnabledMenu; }

  public void actionPerformed(ActionEvent e) {
    if (e.getSource() == fontPickerMenu) {
      FontPicker fp = new FontPicker();
    }
  }
}
