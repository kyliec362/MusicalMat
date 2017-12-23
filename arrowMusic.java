import java.awt.*;
import java.awt.event.*;
import javax.swing.*;  
import java.applet.*;

public class arrowMusic extends JApplet
{ 
  int width=500, height=500; //dimensions of window
  JLabel label;
  AudioClip A, B, C, D, E, F, G; //different music notes
  public void init()
  {
    label = new JLabel(""); //text-displaying object
    label.setFocusable(true); //key listener should focus on the label
    Container cp=getContentPane(); 
    cp.setBackground(new Color(255,0,171));
    cp.setLayout(new FlowLayout());
    cp.add(label);
    setSize(width,height);
    label.addKeyListener(new CustomKeyListener()); 
    A = getAudioClip(getCodeBase(), "A_Piano_57.wav");
    B = getAudioClip(getCodeBase(), "B_Piano_59.wav");
    C = getAudioClip(getCodeBase(), "C_Piano_60.wav");
    D = getAudioClip(getCodeBase(), "D_Piano_62.wav");
    E = getAudioClip(getCodeBase(), "E_Piano_64.wav");
    F = getAudioClip(getCodeBase(), "F_Piano_53.wav");
    G = getAudioClip(getCodeBase(), "G_Piano_55.wav");
  }
  
  public static void main(String[] args) throws Exception
  {   
  } 
  
  class CustomKeyListener implements KeyListener
  {
    public void keyTyped(KeyEvent e) { }
    public void keyReleased(KeyEvent e) //clear JLabel once arrow key released
    {
      repaint();
    } 
    public void keyPressed(KeyEvent e) 
    {
      if(e.getKeyCode() == KeyEvent.VK_A)
      {
        A.play();
        label.setText(label.getText() + "A ");
        repaint();
      }
      if(e.getKeyCode() == KeyEvent.VK_B)
      {
        B.play();
        label.setText(label.getText() + "B ");
        repaint();
      }
      if(e.getKeyCode() == KeyEvent.VK_C)
      {
        C.play();
        label.setText(label.getText() + "C ");
        repaint();
      }
      if(e.getKeyCode() == KeyEvent.VK_D)
      {
        D.play();
        label.setText(label.getText() + "D ");
        repaint();
      }
      if(e.getKeyCode() == KeyEvent.VK_E)
      {
        E.play();
        label.setText(label.getText() + "E ");
        repaint();
      }
      if(e.getKeyCode() == KeyEvent.VK_F)
      {
        F.play();
        label.setText(label.getText() + "F ");
        repaint();
      }
      if(e.getKeyCode() == KeyEvent.VK_G)
      {
        G.play();
        label.setText(label.getText() + "G ");
        repaint();
      }
    }
  } 
}