#include <SFML/Graphics.hpp> //SFML ���� - �ý���, ������, �׷���, ����� �� ��Ʈ��ũ�� 5�� ���� �����ȴ�.
using namespace sf; //SFML �Լ� ���� ����

//â ũ�� ����
int width = 1024;   //����
int height = 768;   //����
int roadW = 2000;
int segL_segment_length = 200; //segment length //�簢�� �ϳ��ϳ��� �����̴�.
float camD = 0.84; //camera depth

//�簢�� �׸��� �Լ�. (x1, y1)���� �غ��� ���̴� �¿� w1��ŭ(�� 2*w1), (x2, y2)���� ������ ���̴� �¿� w2��ŭ �簢���� �׸���.
void drawQuad(RenderWindow &w, Color c, int x1,int y1,int w1,int x2,int y2,int w2)
{
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1-w1,y1));
    shape.setPoint(1, Vector2f(x2-w2,y2));
    shape.setPoint(2, Vector2f(x2+w2,y2));
    shape.setPoint(3, Vector2f(x1+w1,y1));
    w.draw(shape);
}

//���� ����ü
struct Line
{
  //���� ��ǥ
  float x,y,z; //3d center of line
  //ȭ����� ��ǥ
  float X,Y,W; //screen coord
  float curve,spriteX,clip,scale;
  Sprite sprite;

  Line()
  {spriteX=curve=x=y=z=0;}

  //���� ��ǥ���� ������ ��ǥ�� ��ȯ
  void project(int camX,int camY,int camZ)
  {
    scale = camD/(z-camZ);
    X = (1 + scale*(x - camX)) * width/2;
    Y = (1 - scale*(y - camY)) * height/2;
    W = scale * roadW  * width/2;
  }

  //��������Ʈ�� �ѷ��ִ� �Լ��̴�.
  void drawSprite(RenderWindow &app)
  {
    Sprite s = sprite;
    //�ؽ����� w,h����
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = X + scale * spriteX * width/2;
    float destY = Y + 4;
    float destW  = w * W / 266;
    float destH  = h * W / 266;

    destX += destW * spriteX; //offsetX
    destY += destH * (-1);    //offsetY

    //Ŭ������ ��ġ�� 0���� ������ 0�� �Ҵ��ض�
    float clipH = destY+destH-clip;
    if (clipH<0) clipH=0;

    if (clipH>=destH) return;
    //��������Ʈ�� �簢 �ؽ��ķ� ��ġ�� ��ġ, ����, ��������Ʈ�� ��ǥ���� �Ҵ��ϰ� �׷���
    s.setTextureRect(IntRect(0,0,w,h-h*clipH/destH));
    s.setScale(destW/w,destH/h);
    s.setPosition(destX, destY);
    app.draw(s);
    }
};

//�Լ��� ���� �κ�
int main()
{
    //sf::RenderWindow Class
    //�׷��� ����� �⺻ Ŭ�����̴�.
    //������� �� â�� �̸��� �������ش�.
/*
sf::RenderWindow::RenderWindow	(	VideoMode 	mode,
                                    const String & 	title,
                                    Uint32 	style = Style::Default,
                                    const ContextSettings & 	settings = ContextSettings() 
)		
[�� â�� ����ϴ�.]
Construct a new window.

[�� �����ڴ� ��忡�� ���ǵ� ũ��� �ȼ� ���̷� â�� ����ϴ�.]
This constructor creates the window with the size and pixel depth defined in mode.
[â�� ���� ������ ����� �����ϱ� ���� ������ ��Ÿ���� ������ �� �ֽ��ϴ� (�׵θ�, ���� ǥ�� ��, ũ�� ���� ����, �ݱ� ���� ��).]
An optional style can be passed to customize the look and behavior of the window (borders, title bar, resizable, closable, ...).

[�� ��° �Ű� ������ ��Ƽ �ٸ����, ���� ���� ��Ʈ ��� ���� ��� OpenGL ���ؽ�Ʈ ������ �����ϴ� ������ �����Դϴ�.]
The fourth parameter is an optional structure specifying advanced OpenGL context settings such as antialiasing, depth-buffer bits, etc.
[�Ϲ������� �׷��� ����� ����� ������ �̷��� �Ű� ������ �Ű� ���� ���ʽÿ�.]
You shouldn't care about these parameters for a regular usage of the graphics module.

Parameters
mode	Video mode to use (defines the width, height and depth of the rendering area of the window)
title	Title of the window
style	Window style, a bitwise OR combination of sf::Style enumerators
settings	Additional settings for the underlying OpenGL context
*/

/*
sf::VideoMode::VideoMode	(	unsigned int 	modeWidth,  //����
                                unsigned int 	modeHeight, //����
                                unsigned int 	modeBitsPerPixel = 32   //��Ʈ�� �ȼ�
                            )
[�־��� �Ӽ����� ���� ��带 �����մϴ�.]
Construct the video mode with its attributes.

    Parameters
    modeWidth	Width in pixels
    modeHeight	Height in pixels
    modeBitsPerPixel	Pixel depths in bits per pixel
*/
    RenderWindow app(VideoMode(width, height), "Outrun Racing!");
    //������ ������ 60���� �ɾ��ش�.
    app.setFramerateLimit(60);

    //���ӿ� �ʿ��� ��������Ʈ�� �����Ѵ�.
/*
    Texture
[�׸��⿡ ����� ���ִ� �׷��� ī�忡�ִ� �̹����Դϴ�.]
Image living on the graphics card that can be used for drawing.
[Sf :: Texture�� ���� ��� ��������Ʈ�� ����Ͽ� �׸� �� �ִ� �ȼ��� �����մϴ�.]
sf::Texture stores pixels that can be drawn, with a sprite for example.
*/
// Load a texture from a file
// �ؽ��ĸ� ���Ͽ��� �ҷ��ɴϴ�.
    Texture t[50];
// Assign it to a sprite
// ��������Ʈ�� �Ҵ��մϴ�.
    Sprite object[50];

    for(int i=1;i<=7;i++)
     {
        //��Ʈ ���͸����� �̹����� 7�� �ε��մϴ�.
       t[i].loadFromFile("images/"+std::to_string(i)+".png");
       // smooth filter�� enable�մϴ�.
       t[i].setSmooth(true);
       // �ҷ��� �ؽ��ĸ� �Ҵ��մϴ�.
       object[i].setTexture(t[i]);
     }

    // ��׶��� �ؽ��ĸ� �ҷ��ɴϴ�.
    // ���� ���� ����
    Texture bg;
    bg.loadFromFile("images/bg.png");
    bg.setRepeated(true);
    Sprite sBackground(bg);

    /*
void sf::Sprite::setTextureRect	(	const IntRect & 	rectangle	)
[��������Ʈ�� ǥ�� �� �ؽ�ó�� ���� ���簢���� �����մϴ�.]
Set the sub-rectangle of the texture that the sprite will display.
[�ؽ�ó rect�� ��ü �ؽ�ó�� �ƴ� �Ϻθ� ǥ���ϰ� ���� �� �����մϴ�.]
The texture rect is useful when you don't want to display the whole texture, but rather a part of it.
[�⺻������ �ؽ�ó ���簢���� ��ü �ؽ�ó�� �����ϴ�.]
By default, the texture rect covers the entire texture.

Parameters
rectangle
Rectangle defining the region of the texture to display
    */

    /*
template<typename T>
sf::Rect< T >::Rect	(	T 	rectLeft,
                        T 	rectTop,
                        T 	rectWidth,
                        T 	rectHeight 
                    )		
[��ǥ���� ���簢���� �����մϴ�.]
Construct the rectangle from its coordinates.
[������ �� �Ű� ������ ������ �� �Ʒ��� ��ǥ�� �ƴ϶� �ʺ�� �����Դϴ�.]
Be careful, the last two parameters are the width and height, not the right and bottom coordinates!

Parameters
rectLeft	Left coordinate of the rectangle
rectTop	Top coordinate of the rectangle
rectWidth	Width of the rectangle
rectHeight	Height of the rectangle
    */
    //411�� bg.png�� ���� �����Դϴ�.
    sBackground.setTextureRect(IntRect(0,0,2500,411));
    /*
    void sf::Transformable::setPosition	( float x, float y )		
[��ü�� ��ġ ����]
set the position of the object

[�� ����� ���� ��ġ�� ������ ���� ���ϴ�.]
This function completely overwrites the previous position.
[��� ���� ��ġ�� �������� �������� �����Ϸ��� �̵� ����� �����Ͻʽÿ�.]
See the move function to apply an offset based on the previous position instead.
[���� ������ ��ü�� �⺻ ��ġ�� (0, 0)�Դϴ�.]
The default position of a transformable object is (0, 0).

Parameters
x	X coordinate of the new position
y	Y coordinate of the new position
    */
    sBackground.setPosition(-2000,0);

    //���� ����
    /*
    ����(std::vector)�� ���� �迭 ������ C++�� ������ ���̴�. 
    �̰��� C�� �迭(���� ���� ������ ������)ó�� �ൿ������ �ڵ����� �迭�� ũ�� ������ ��ü�� �߰��� ������ �����ϴ�. 
    ���ʹ� C++ ǥ�� ���ø� ���̺귯�� ���� �ϳ��� ���ø� Ŭ�����̴�. 
    � Ÿ���̶� ������ �� ������, �� ���� �� Ÿ�Ը� ������ �����ϴ�. 
    ��ҿ� �����ϰų�, �� �Ǵ� �ڿ� ��Ҹ� �߰��ϰų� ������ �� �ְ� ũ�⸦ �� �� �ִ� ��� �Լ��� �����ϰ� �ִ�.
    */
    std::vector<Line> lines;

    for(int i=0;i<1600;i++)
     {
       Line line;
       line.z = i*segL_segment_length;

       // 300���� 700���� Ŀ�긦 0.5(������) �ش�.
       if (i>300 && i<700) line.curve=0.5;
       //1100 �Ѿ�鼭 Ŀ�긦 -0.7(����) �ش�.
       if (i>1100) line.curve=-0.7;

       // 300 ������ ���� ���ʿ� 20 ������ 5�� �ؽ��ĸ� ��ġ�Ѵ�
       if (i<300 && i%20==0) {line.spriteX=-2.5; line.sprite=object[5];}
       // ��ü ���� �����ʿ� 17 ������ 6�� �ؽ��ĸ� ��ġ�Ѵ�
       if (i%17==0)          {line.spriteX=2.0; line.sprite=object[6];}
       // 300 ���ķ� ���� ���ʿ� 20 ������ 4�� �ؽ��ĸ� ��ġ�Ѵ�
       if (i>300 && i%20==0) {line.spriteX=-0.7; line.sprite=object[4];}
       // 800 ���ķ� ���� ���ʿ� 20 ������ 1�� �ؽ��ĸ� ��ġ�Ѵ�
       if (i>800 && i%20==0) {line.spriteX=-1.2; line.sprite=object[1];}
       //�� �̹���
       if (i==400)           {line.spriteX=-1.2; line.sprite=object[7];}

       //750 ���ķ� y�࿡ ������ �ش�.
       if (i>750) line.y = sin(i/30.0)*1500;

       //push_back�� vector�� ���� ��Ҹ� �߰��Ҷ� ����ϴ� �Լ���. ���� ���Ϳ� ���� ��������Ʈ�� �߰��ض�.
       lines.push_back(line);
     }

    //���� ������ ����� �����Ѵ�.
   int N_lines_size = lines.size();
   //�÷��̾��� ó�� ��ġ�� �����Ѵ�.
   float playerX = 0;   //�¿� �����̴�.
   int pos = 0;
   int H = 1500;    //���� �����̴�.

   //�����찡 ���� �ִ� ���� �Ʒ��� �̺�Ʈ�� �����ϰ� �ض�
    while (app.isOpen())
    {
        //����� ȯ�濡�� �Ͼ�� �̺�Ʈ�� �Է����� �޴´�. Ű���� �Է�, ���콺 �̵� ��
        Event e;
        // �̺�Ʈ�� ����� �߻��ϸ� true�� ��ȯ�Ѵ�.
        while (app.pollEvent(e))
        {
            //������ �̺�Ʈ�� ����� ����� �޾Ҵٸ�
            //The window requested to be closed (no data)
            if (e.type == Event::Closed)
                app.close();    //���� ����
        }

  //���ǵ� ���� ����
  int speed=0;

  //Ű���� �Է��� ȭ��ǥ �������̶�� �÷��̾��� x�� ��ġ�� 0.1 ���ض�
  if (Keyboard::isKeyPressed(Keyboard::Right)) playerX+=0.1;
  //Ű���� �Է��� ȭ��ǥ �����̶�� �÷��̾��� x�� ��ġ�� 0.1 ����
  if (Keyboard::isKeyPressed(Keyboard::Left)) playerX-=0.1;
  //Ű���� �Է��� ȭ��ǥ �����̶�� �÷��̾��� ���ǵ带 200���� �����ض�.
  if (Keyboard::isKeyPressed(Keyboard::Up)) speed=200;
  //Ű���� �Է��� ȭ��ǥ �����̶�� �÷��̾��� ���ǵ带 -200���� �����ض�.
  if (Keyboard::isKeyPressed(Keyboard::Down)) speed=-200;
  //Ű���� �Է��� Tab �̶�� �÷��̾��� ���ǵ带 3�� �������Ѷ�
  if (Keyboard::isKeyPressed(Keyboard::Tab)) speed*=3;
  if (Keyboard::isKeyPressed(Keyboard::Up)) speed = 200;
  //Ű���� �Է��� W ��� �÷��̾��� ���̸� 100 �������Ѷ�
  if (Keyboard::isKeyPressed(Keyboard::W)) H+=100;
  //Ű���� �Է��� S ��� �÷��̾��� ���̸� 100 ���ҽ��Ѷ�
  if (Keyboard::isKeyPressed(Keyboard::S)) H-=100;

  //�� ���ǵ常ŭ �����ǿ� ���ض�
  pos+=speed;
  //�������� ���׸�Ʈ ���� * ������ �������� ũ�ٸ�
  //�������� ���׸�Ʈ ���� * ������ ������ŭ �����
  //�ڷΰ��� �����̴�.
  while (pos >= N_lines_size*segL_segment_length) pos-=N_lines_size*segL_segment_length;
  while (pos < 0) pos += N_lines_size*segL_segment_length;

  //���� ������ �ʷϻ����� ���������
  app.clear(Color(105,205,4));
  //���� ��׶��带 �׷���
  app.draw(sBackground);
  // ���� �������� �������� ���׸�Ʈ ������ ��������. �̰ɷ� �Ʒ��� for���� ���δ�.
  int startPos = pos/segL_segment_length;
  // ī�޶��� ��ġ(ȭ��)���� ���� ��ġ ���� ��ü�� y�� ��ġ + H ��ŭ �Ҵ��ض�
  int camH = lines[startPos].y + H;
  //���� ������ ���ٸ� ���ȭ���� ��ǥ�� Ŀ�� * 2��ŭ �������� �̵����Ѷ�
  if (speed>0) sBackground.move(-lines[startPos].curve*2,0);
  //���� �ڷ� ���ٸ� ���ȭ���� ��ǥ�� Ŀ�� * 2��ŭ ���������� �̵����Ѷ�
  if (speed<0) sBackground.move( lines[startPos].curve*2,0);

  int maxy = height;
  float x=0,dx=0;

  ///////draw road////////
  for(int n = startPos; n<startPos+300; n++)  
   {
      //��ⷯ ������ ���ϴ� ������ ������ ����� ���ؼ��̴�.
      Line &l = lines[n%N_lines_size];
    //�÷��̾��� ��ġ�� �������� �ٴ��� �׷���
    //�¿�, ���Ʒ�, �յ� ��ǥ�� ��Ÿ����.
    l.project(playerX*roadW-x, camH, startPos*segL_segment_length - (n>=N_lines_size?N_lines_size*segL_segment_length:0));
    //x�� ���� dx��ŭ ���ؼ� Ŀ�긦 ������� ���̴�.
    x+=dx;
    //���� ��ǥ�� Ŀ�길ŭ dx�� ���ض�
    dx+=l.curve;

    //������ y���� ���̸� �������ֱ� ���ؼ��̴�. max�� �����÷ο� ����
    l.clip=maxy;
    if (l.Y>=maxy) continue;
    maxy = l.Y;

    // �ٴ� ������ ���� �ʷ�, ���� �ʷ����� �Ѵ�.
    Color grass  = (n/3)%2?Color(16,200,16):Color(0,154,0);
    // ���� ���̵带 ��� ������ ���ư��� �ش�
    Color rumble = (n/3)%2?Color(255,255,255):Color(0,0,0);
    // ������ ȸ���� ĥ���ش�.
    Color road   = (n/3)%2?Color(107,107,107):Color(105,105,105);

    Line p = lines[(n-1)%N_lines_size]; //previous line

    //���� ��ü�� �ʷϻ��� ĥ�Ѵ�.
    drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
    // ���� ���̵带 ĥ�Ѵ�.
    drawQuad(app, rumble,p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2);
    //���θ� ĥ�Ѵ�.
    drawQuad(app, road,  p.X, p.Y, p.W, l.X, l.Y, l.W);
   }

  //������ ���� ������Ʈ��(����)�� 300����ŭ �տ� �׷���
    ////////draw objects////////
    for(int n=startPos+300; n>startPos; n--)
      lines[n%N_lines_size].drawSprite(app);

    //ȭ���� ����ض�
    app.display();
    }

    return 0;
}
