import javax.swing.JFrame;

class MyFrame extends JFrame {
    MyFrame(){
        setSize(800,600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MyPanel panel=new MyPanel();
        add(panel);
        setVisible(true);
    }
}