import java.net.*;
import java.util.StringTokenizer;
import java.io.*;
import javax.swing.*;
import java.awt.*;

public class homework13server extends JFrame{

    Container c = getContentPane();
    JTextArea jta = new JTextArea();

    public homework13server() {

        jta.setEnabled(false);
        jta.setDisabledTextColor(Color.black);
        c.add(jta);

        setTitle("계산");
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(350,350);

        try {
            ServerSocket jdy = new ServerSocket(9999);
            int i=1;
            while(true) {

                Socket socket = jdy.accept();
                ClientThread ct = new ClientThread(socket);
                ct.start();
                jta.append("클라이언트"+i+"번 연결됨."+"\n");
                i++;
            }
        }catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }

    class ClientThread extends Thread{
        Socket sock;
        public ClientThread(Socket sockk) {
            this.sock = sockk;
        }

        @Override
        public void run() {
            try {
                BufferedReader br = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
                while(true) {
                    String line = br.readLine();
                    if(line == null)
                        break;
                    jta.append(line+"=");
                    int result = calculate(line);
                   if(result==-1){
                    jta.append(-1+"\n");
                    bw.write(-1+"\n");
                   }
                    else{    
                    jta.append(result+"\n");
                    bw.write(result+"\n");
                  }
                    bw.flush();
                }
            }
            catch(Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public int calculate(String line) {
        StringTokenizer alpha;
        char operator;
       
        
        

        if(line.indexOf("+") > 0) {
            alpha = new StringTokenizer(line,"+");
            operator = '+';
        }
        else if(line.indexOf("-") > 0) {
            alpha = new StringTokenizer(line,"-");
            operator = '-';
        }
        else if(line.indexOf("*") > 0) {
            alpha = new StringTokenizer(line,"*");
            operator = '*';
        }
        else if(line.indexOf("/") > 0){
            alpha = new StringTokenizer(line,"/");
            operator = '/';
        }
        else {
           return -200000;
           
        }

        int count1 = Integer.parseInt(alpha.nextToken());
        int count2 = Integer.parseInt(alpha.nextToken());

        if(operator == '+') return count1 + count2;
        else if(operator == '-') return count1 - count2;
        else if(operator == '*') return count1 * count2;
        else if(operator == '/') return count1 / count2;
        else return -200000;

    }


    public static void main(String[] args) {
        new homework13server();
    }
}