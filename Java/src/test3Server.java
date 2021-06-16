import java.io.*;
import java.net.*;
import java.util.StringTokenizer;

import javax.swing.*;
import java.awt.*;

public class test3Server extends JFrame{

    Container c = getContentPane();
    JTextArea ta = new JTextArea();

    public test3Server() {

        ta.setEnabled(false);
        ta.setDisabledTextColor(Color.black);
        c.add(ta);

        setTitle("계산 서버");
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300,300);

        try {
            ServerSocket ss = new ServerSocket(9999);
            int i=1;
            while(true) {

                Socket sk = ss.accept();
                ClientThread ct = new ClientThread(sk);
                ct.start();
                ta.append("클라이언트"+i+"번 연결됨."+"\n");
                i++;
            }
        }catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }

    class ClientThread extends Thread{
        Socket sk;
        public ClientThread(Socket sk) {
            this.sk = sk;
        }

        @Override
        public void run() {
            try {
                BufferedReader br = new BufferedReader(new InputStreamReader(sk.getInputStream()));
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(sk.getOutputStream()));
                while(true) {
                    String line = br.readLine();
                    if(line == null)
                        break;
                    ta.append(line+"=");
                    int result = calculate(line);
                    ta.append(result+"\n");
                    bw.write(result+"\n");
                    bw.flush();
                }
            }
            catch(Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public int calculate(String line) {
        StringTokenizer st;
        char oprator;

        if(line.indexOf("+") > 0) {
            st = new StringTokenizer(line,"+");
            oprator = '+';
        }
        else if(line.indexOf("-") > 0) {
            st = new StringTokenizer(line,"-");
            oprator = '-';
        }
        else if(line.indexOf("*") > 0) {
            st = new StringTokenizer(line,"*");
            oprator = '*';
        }
        else{
            st = new StringTokenizer(line,"/");
            oprator = '/';
        }

        int num1 = Integer.parseInt(st.nextToken());
        int num2 = Integer.parseInt(st.nextToken());

        if(oprator == '+') return num1 + num2;
        else if(oprator == '-') return num1 - num2;
        else if(oprator == '*') return num1 * num2;
        else return num1 / num2;

    }


    public static void main(String[] args) {
        new test3Server();
    }
}
