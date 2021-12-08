import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
import java.util.*;
class MyPanel extends JPanel {
    JLabel l1,l2,l3,l4,l5;
    JTextField f1,f2,f3,f4,f5;
    JButton button;
    MyPanel(){
        l1=new JLabel("a=");
        add(l1);
        f1=new JTextField();
        f1.setColumns(6);
        add(f1);
        l2=new JLabel("b=");
        add(l2);
        f2=new JTextField();
        f2.setColumns(6);
        add(f2);
        l3=new JLabel("c=");
        add(l3);
        f3=new JTextField();
        f3.setColumns(6);
        add(f3);
        l4=new JLabel("x1=");
        add(l4);
        f4=new JTextField();
        f4.setColumns(15);
        add(f4);
        l5=new JLabel("x2=");
        add(l5);
        f5=new JTextField();
        f5.setColumns(15);
        add(f5);

        button=new JButton("вычислить");
        MyListener m=new MyListener();
        button.addActionListener(m);
        add(button);

    }
    class MyListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            int s1=Integer.parseInt(f1.getText());
            int s2=Integer.parseInt(f2.getText());
            int s3=Integer.parseInt(f3.getText());
            if (s2*s2-4*s1*s3>=0) {
                double d = Math.sqrt(s2 * s2 - 4 * s1 * s3);
                double x1 = (-s2 + d) / (2 * s1);
                double x2 = (-s2 - d) / (2 * s1);
                f4.setText(String.valueOf(x1));
                f5.setText(String.valueOf(x2));
            }
            else{
                f4.setText("нет корня");
                f5.setText("нет корня");
            }
        }


    }
}
