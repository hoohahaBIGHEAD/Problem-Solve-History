import java.net.*;
import java.io.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class test3Client extends JFrame{

    Socket sk;
    BufferedReader br;
    BufferedWriter bw;

    public test3Client() {
        Container c = getContentPane();
        c.setLayout(new FlowLayout());
        JTextField tf[] = new JTextField[4];
        JButton bt = new JButton("계산");

        for(int i=0;i<tf.length;i++) {
            tf[i] = new JTextField(4);
            if(i==3)
                break;
            c.add(tf[i]);
        }
        c.add(new JLabel("="));
        c.add(tf[3]);
        c.add(bt);

        setTitle("클라이언트");
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(350,120);

        try {
            sk = new Socket("localhost",9999);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        bt.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {

                try {
                    bw = new BufferedWriter(new OutputStreamWriter(sk.getOutputStream()));
                    br = new BufferedReader(new InputStreamReader(sk.getInputStream()));

                    String line = tf[0].getText() + tf[1].getText() + tf[2].getText();
                    bw.write(line+"\n");
                    bw.flush();

                    String result = br.readLine();
                    tf[3].setText(result);

                }
                catch(Exception e2) {
                    System.out.println(e2.getMessage());
                }
            }
        });
    }

    public static void main(String[] args) {
        new test3Client();
    }

}