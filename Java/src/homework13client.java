package homework13;

import java.net.*;
import java.io.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class homework13client extends JFrame{

    Socket sockkk;
    BufferedReader buffeR;
    BufferedWriter buffeW;

    public homework13client() {
        Container c = getContentPane();
        c.setLayout(new FlowLayout());
        JTextField jtf[] = new JTextField[4];
        JButton button = new JButton("calc");

        for(int i=0;i<jtf.length;i++) {
            jtf[i] = new JTextField(4);
            if(i==3)
                break;
            c.add(jtf[i]);
        }
        c.add(new JLabel("="));
        c.add(jtf[3]);
        c.add(button);

        setTitle("client");
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(350,120);

        try {
            sockkk = new Socket("localhost",9999);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {

                try {
                    buffeW = new BufferedWriter(new OutputStreamWriter(sockkk.getOutputStream()));
                    buffeR = new BufferedReader(new InputStreamReader(sockkk.getInputStream()));

                    String line = jtf[0].getText() + jtf[1].getText() + jtf[2].getText();
                    buffeW.write(line+"\n");
                    buffeW.flush();

                    String result = buffeR.readLine();
                    jtf[3].setText(result);

                }
                catch(Exception e2) {
                    System.out.println(e2.getMessage());
                }
            }
        });
    }

    public static void main(String[] args) {
        new homework13client();
    }

}