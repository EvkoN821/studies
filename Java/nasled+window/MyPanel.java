import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

class MyPanel extends JPanel {
    JLabel l1,l2,l3,l4,l5,l6;
    JTextField f1,f2,f3,f4,f5,f6;
    JButton button;
    MyPanel(){
        l1=new JLabel("input name: ");
        add(l1);
        f1=new JTextField();
        f1.setColumns(6);
        add(f1);
        l2=new JLabel("input density: ");
        add(l2);
        f2=new JTextField();
        f2.setColumns(6);
        add(f2);
        l3=new JLabel("input concentration");
        add(l3);
        f3=new JTextField();
        f3.setColumns(6);
        add(f3);
        l4=new JLabel("input new density");
        add(l4);
        f4=new JTextField();
        f4.setColumns(6);
        add(f4);
        l5=new JLabel("данные1: =");
        add(l5);
        f5=new JTextField();
        f5.setColumns(30);
        add(f5);
        l6=new JLabel("данные2: =");
        add(l6);
        f6=new JTextField();
        f6.setColumns(30);
        add(f6);

        button=new JButton("вывести данные");
        MyListener m=new MyListener();
        button.addActionListener(m);
        add(button);

    }
    class MyListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            String s1= new String(f1.getText());
            double s2=Double.parseDouble(f2.getText());
            double s3=Double.parseDouble(f3.getText());
            double s4=Double.parseDouble(f4.getText());
            Acid a=new Acid(s1,s2,s3);
            f5.setText(String.valueOf(a.print()));
            a.setDensity(s4);
            f6.setText(String.valueOf(a.print()));
            }
        }


    }