import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class GT extends Thread {
    boolean gambling = false; //스레드의 작동 여부 설정. 초깃값 = false
    JLabel la[];
    JLabel result;

    public GT(JLabel la[], JLabel result) {
        this.la = la;
        this.result = result;
    }

    synchronized public void wFG() { //스레드의 run()에서 호출
        if (!gambling) //마우스 클릭에 의해 gambling이 true가 될 때까지 기다림
            try {
                this.wait();
            }
            //true 아니면 기다리라는 말
            catch (InterruptedException e) {
                return;
            }
    }

    synchronized public void sG() { //마우스 클릭 핸들러에서 호출
        gambling = true; //마우스 클릭으로 스레드가 게임을 진행하도록 지시
        this.notify(); //기다리는 스레드를 깨움
    }
    public void run() {
        while (true) {
            wFG(); //마우스 클릭이 일어나기를 기다린다.
            for (int i = 0; i < 3; i++) {
                int x = (int) (Math.random() * 5);
                la[i].setText(Integer.toString(x));
                try {
                    sleep(200);
                }
                catch (InterruptedException e) {
                    return;
                }
            }
            gambling = false; //이제 다음 게임이 가능하도록 설정한다.
            int x = Integer.parseInt(la[0].getText());
            int y = Integer.parseInt(la[1].getText());
            int z = Integer.parseInt(la[2].getText());
            if (x == y && y == z) result.setText("           축하합니다!!");
            else result.setText("             아쉽군요");
            //대충 가운데 정렬 맞추기 위해 ..
        }
    }
}

class GP extends JPanel {
    JLabel la[];
    JLabel result;
    GT g;
    public GP(GT g, JLabel la[], JLabel result) {
        this.g = g;
        this.la = la;
        this.result = result;
        setLayout(null); //null로 하고 3개 레이블 위치 지정해줌
        for (int i = 0; i < 3; i++) {
            la[i].setFont(new Font("Arial", Font.ITALIC, 40));
            la[i].setForeground(Color.YELLOW);
            JPanel pa = new JPanel();
            pa.add(la[i]);
            pa.setBackground(Color.MAGENTA);
            pa.setSize(100, 50);
            pa.setLocation(110 * (i + 1), 80);
            add(pa);
            addMouseListener(new MouseAdapter() {
                public void mouseClicked(MouseEvent e) {
                    g.sG();
                    //겜블링 시작할거라고 메소드 보내서 메소드 안에서 true로 바꿔주기까지 진행
                }
            });
            pa.requestFocus();
        }
        result.setFont(new Font("", Font.BOLD, 25));
        //여기에 영어폰트 설정하면 한글이 안나온다
        add(result);
        result.setSize(500, 25);
        result.setLocation(50, 200);
    }
}

public class Main extends JFrame {
    JLabel la[] = new JLabel[3];
    JLabel result = new JLabel("마우스를 클릭할 때 마다 게임합니다.");

    public Main() {
        setTitle("스레드를 가진 겜블링");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        la[0] = new JLabel(Integer.toString(0));
        la[1] = new JLabel(Integer.toString(0));
        la[2] = new JLabel(Integer.toString(0));
        //이거를 panel에 넣으면 thread랑 panel 생성자에서 서로 엇갈려서?
        //둘다 만들때 서로가 있어야했는데 서로 엇갈리니까 여기에 label은 미리 만들어줬다.
        GT g = new GT(la, result);
        g.start();
        setContentPane(new GP(g, la, result));
        setSize(550, 350);
        setVisible(true);
        getContentPane().setFocusable(true);
        getContentPane().requestFocus();

    }

    public static void main(String[] args) {
        new Main();
    }
}