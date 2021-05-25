#include <SFML/Graphics.hpp> //SFML 포함 - 시스템, 윈도우, 그래픽, 오디오 및 네트워크의 5개 모듈로 구성된다.
using namespace sf; //SFML 함수 쓰기 위함

//창 크기 설정
int width = 1024;   //가로
int height = 768;   //세로
int roadW = 2000;
int segL_segment_length = 200; //segment length //사각형 하나하나의 단위이다.
float camD = 0.84; //camera depth

//사각형 그리는 함수. (x1, y1)에서 밑변의 길이는 좌우 w1만큼(총 2*w1), (x2, y2)에서 윗변의 길이는 좌우 w2만큼 사각형을 그린다.
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

//라인 구조체
struct Line
{
  //내부 좌표
  float x,y,z; //3d center of line
  //화면상의 좌표
  float X,Y,W; //screen coord
  float curve,spriteX,clip,scale;
  Sprite sprite;

  Line()
  {spriteX=curve=x=y=z=0;}

  //내부 좌표에서 윈도우 좌표로 변환
  void project(int camX,int camY,int camZ)
  {
    scale = camD/(z-camZ);
    X = (1 + scale*(x - camX)) * width/2;
    Y = (1 - scale*(y - camY)) * height/2;
    W = scale * roadW  * width/2;
  }

  //스프라이트를 뿌려주는 함수이다.
  void drawSprite(RenderWindow &app)
  {
    Sprite s = sprite;
    //텍스쳐의 w,h설정
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = X + scale * spriteX * width/2;
    float destY = Y + 4;
    float destW  = w * W / 266;
    float destH  = h * W / 266;

    destX += destW * spriteX; //offsetX
    destY += destH * (-1);    //offsetY

    //클립높이 위치가 0보다 작으면 0에 할당해라
    float clipH = destY+destH-clip;
    if (clipH<0) clipH=0;

    if (clipH>=destH) return;
    //스프라이트의 사각 텍스쳐룰 배치할 위치, 비율, 스프라이트의 좌표값을 할당하고 그려라
    s.setTextureRect(IntRect(0,0,w,h-h*clipH/destH));
    s.setScale(destW/w,destH/h);
    s.setPosition(destX, destY);
    app.draw(s);
    }
};

//함수의 시작 부분
int main()
{
    //sf::RenderWindow Class
    //그래픽 모듈의 기본 클래스이다.
    //비디오모드 및 창의 이름을 설정해준다.
/*
sf::RenderWindow::RenderWindow	(	VideoMode 	mode,
                                    const String & 	title,
                                    Uint32 	style = Style::Default,
                                    const ContextSettings & 	settings = ContextSettings() 
)		
[새 창을 만듭니다.]
Construct a new window.

[이 생성자는 모드에서 정의된 크기와 픽셀 깊이로 창을 만듭니다.]
This constructor creates the window with the size and pixel depth defined in mode.
[창의 모양과 동작을 사용자 지정하기 위해 선택적 스타일을 전달할 수 있습니다 (테두리, 제목 표시 줄, 크기 조정 가능, 닫기 가능 등).]
An optional style can be passed to customize the look and behavior of the window (borders, title bar, resizable, closable, ...).

[네 번째 매개 변수는 안티 앨리어싱, 깊이 버퍼 비트 등과 같은 고급 OpenGL 컨텍스트 설정을 지정하는 선택적 구조입니다.]
The fourth parameter is an optional structure specifying advanced OpenGL context settings such as antialiasing, depth-buffer bits, etc.
[일반적으로 그래픽 모듈을 사용할 때에는 이러한 매개 변수를 신경 쓰지 마십시오.]
You shouldn't care about these parameters for a regular usage of the graphics module.

Parameters
mode	Video mode to use (defines the width, height and depth of the rendering area of the window)
title	Title of the window
style	Window style, a bitwise OR combination of sf::Style enumerators
settings	Additional settings for the underlying OpenGL context
*/

/*
sf::VideoMode::VideoMode	(	unsigned int 	modeWidth,  //가로
                                unsigned int 	modeHeight, //세로
                                unsigned int 	modeBitsPerPixel = 32   //비트당 픽셀
                            )
[주어진 속성으로 비디오 모드를 구성합니다.]
Construct the video mode with its attributes.

    Parameters
    modeWidth	Width in pixels
    modeHeight	Height in pixels
    modeBitsPerPixel	Pixel depths in bits per pixel
*/
    RenderWindow app(VideoMode(width, height), "Outrun Racing!");
    //프레임 제한을 60으로 걸어준다.
    app.setFramerateLimit(60);

    //게임에 필요한 스프라이트를 생성한다.
/*
    Texture
[그리기에 사용할 수있는 그래픽 카드에있는 이미지입니다.]
Image living on the graphics card that can be used for drawing.
[Sf :: Texture는 예를 들어 스프라이트를 사용하여 그릴 수 있는 픽셀을 저장합니다.]
sf::Texture stores pixels that can be drawn, with a sprite for example.
*/
// Load a texture from a file
// 텍스쳐를 파일에서 불러옵니다.
    Texture t[50];
// Assign it to a sprite
// 스프라이트에 할당합니다.
    Sprite object[50];

    for(int i=1;i<=7;i++)
     {
        //루트 디렉터리에서 이미지를 7개 로드합니다.
       t[i].loadFromFile("images/"+std::to_string(i)+".png");
       // smooth filter를 enable합니다.
       t[i].setSmooth(true);
       // 불러온 텍스쳐를 할당합니다.
       object[i].setTexture(t[i]);
     }

    // 백그라운드 텍스쳐를 불러옵니다.
    // 이하 위와 동일
    Texture bg;
    bg.loadFromFile("images/bg.png");
    bg.setRepeated(true);
    Sprite sBackground(bg);

    /*
void sf::Sprite::setTextureRect	(	const IntRect & 	rectangle	)
[스프라이트가 표시 할 텍스처의 하위 직사각형을 설정합니다.]
Set the sub-rectangle of the texture that the sprite will display.
[텍스처 rect는 전체 텍스처가 아닌 일부를 표시하고 싶을 때 유용합니다.]
The texture rect is useful when you don't want to display the whole texture, but rather a part of it.
[기본적으로 텍스처 직사각형은 전체 텍스처를 덮습니다.]
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
[좌표에서 직사각형을 생성합니다.]
Construct the rectangle from its coordinates.
[마지막 두 매개 변수는 오른쪽 및 아래쪽 좌표가 아니라 너비와 높이입니다.]
Be careful, the last two parameters are the width and height, not the right and bottom coordinates!

Parameters
rectLeft	Left coordinate of the rectangle
rectTop	Top coordinate of the rectangle
rectWidth	Width of the rectangle
rectHeight	Height of the rectangle
    */
    //411은 bg.png의 세로 길이입니다.
    sBackground.setTextureRect(IntRect(0,0,2500,411));
    /*
    void sf::Transformable::setPosition	( float x, float y )		
[물체의 위치 설정]
set the position of the object

[이 기능은 이전 위치를 완전히 덮어 씁니다.]
This function completely overwrites the previous position.
[대신 이전 위치를 기준으로 오프셋을 적용하려면 이동 기능을 참조하십시오.]
See the move function to apply an offset based on the previous position instead.
[변형 가능한 개체의 기본 위치는 (0, 0)입니다.]
The default position of a transformable object is (0, 0).

Parameters
x	X coordinate of the new position
y	Y coordinate of the new position
    */
    sBackground.setPosition(-2000,0);

    //라인 벡터
    /*
    벡터(std::vector)는 동적 배열 구조를 C++로 구현한 것이다. 
    이것은 C의 배열(빠른 랜덤 접근이 가능한)처럼 행동하지만 자동으로 배열의 크기 조절과 객체의 추가와 삭제가 가능하다. 
    벡터는 C++ 표준 템플릿 라이브러리 중의 하나인 템플릿 클래스이다. 
    어떤 타입이라도 저장할 수 있지만, 한 번에 한 타입만 저장이 가능하다. 
    요소에 접근하거나, 앞 또는 뒤에 요소를 추가하거나 삭제할 수 있고 크기를 알 수 있는 멤버 함수를 제공하고 있다.
    */
    std::vector<Line> lines;

    for(int i=0;i<1600;i++)
     {
       Line line;
       line.z = i*segL_segment_length;

       // 300에서 700까지 커브를 0.5(오른쪽) 준다.
       if (i>300 && i<700) line.curve=0.5;
       //1100 넘어가면서 커브를 -0.7(왼쪽) 준다.
       if (i>1100) line.curve=-0.7;

       // 300 전까지 도로 왼쪽에 20 단위로 5번 텍스쳐를 배치한다
       if (i<300 && i%20==0) {line.spriteX=-2.5; line.sprite=object[5];}
       // 전체 도로 오른쪽에 17 단위로 6번 텍스쳐를 배치한다
       if (i%17==0)          {line.spriteX=2.0; line.sprite=object[6];}
       // 300 이후로 도로 왼쪽에 20 단위로 4번 텍스쳐를 배치한다
       if (i>300 && i%20==0) {line.spriteX=-0.7; line.sprite=object[4];}
       // 800 이후로 도로 왼쪽에 20 단위로 1번 텍스쳐를 배치한다
       if (i>800 && i%20==0) {line.spriteX=-1.2; line.sprite=object[1];}
       //집 이미지
       if (i==400)           {line.spriteX=-1.2; line.sprite=object[7];}

       //750 이후로 y축에 굴곡을 준다.
       if (i>750) line.y = sin(i/30.0)*1500;

       //push_back은 vector의 끝에 요소를 추가할때 사용하는 함수다. 라인 벡터에 위의 스프라이트를 추가해라.
       lines.push_back(line);
     }

    //라인 벡터의 사이즈를 저장한다.
   int N_lines_size = lines.size();
   //플레이어의 처음 위치를 셋팅한다.
   float playerX = 0;   //좌우 변수이다.
   int pos = 0;
   int H = 1500;    //높이 변수이다.

   //윈도우가 켜져 있는 동안 아래의 이벤트를 동작하게 해라
    while (app.isOpen())
    {
        //사용자 환경에서 일어나는 이벤트를 입력으로 받는다. 키보드 입력, 마우스 이동 등
        Event e;
        // 이벤트가 제대로 발생하면 true를 반환한다.
        while (app.pollEvent(e))
        {
            //윈도우 이벤트가 끄라는 명령을 받았다면
            //The window requested to be closed (no data)
            if (e.type == Event::Closed)
                app.close();    //앱을 꺼라
        }

  //스피드 변수 선언
  int speed=0;

  //키보드 입력이 화살표 오른쪽이라면 플레이어의 x축 위치를 0.1 더해라
  if (Keyboard::isKeyPressed(Keyboard::Right)) playerX+=0.1;
  //키보드 입력이 화살표 왼쪽이라면 플레이어의 x축 위치를 0.1 빼라
  if (Keyboard::isKeyPressed(Keyboard::Left)) playerX-=0.1;
  //키보드 입력이 화살표 위쪽이라면 플레이어의 스피드를 200으로 고정해라.
  if (Keyboard::isKeyPressed(Keyboard::Up)) speed=200;
  //키보드 입력이 화살표 위쪽이라면 플레이어의 스피드를 -200으로 고정해라.
  if (Keyboard::isKeyPressed(Keyboard::Down)) speed=-200;
  //키보드 입력이 Tab 이라면 플레이어의 스피드를 3배 증가시켜라
  if (Keyboard::isKeyPressed(Keyboard::Tab)) speed*=3;
  if (Keyboard::isKeyPressed(Keyboard::Up)) speed = 200;
  //키보드 입력이 W 라면 플레이어의 높이를 100 증가시켜라
  if (Keyboard::isKeyPressed(Keyboard::W)) H+=100;
  //키보드 입력이 S 라면 플레이어의 높이를 100 감소시켜라
  if (Keyboard::isKeyPressed(Keyboard::S)) H-=100;

  //위 스피드만큼 포지션에 더해라
  pos+=speed;
  //포지션이 세그먼트 길이 * 벡터의 갯수보다 크다면
  //포지션을 세그먼트 길이 * 벡터의 갯수만큼 빼줘라
  //뒤로가기 구현이다.
  while (pos >= N_lines_size*segL_segment_length) pos-=N_lines_size*segL_segment_length;
  while (pos < 0) pos += N_lines_size*segL_segment_length;

  //앱의 배경색을 초록색으로 선언해줘라
  app.clear(Color(105,205,4));
  //앱의 백그라운드를 그려라
  app.draw(sBackground);
  // 시작 포지션은 포지션을 세그먼트 단위로 나눠주자. 이걸로 아래의 for문에 쓰인다.
  int startPos = pos/segL_segment_length;
  // 카메라의 위치(화면)에는 현재 위치 벡터 객체의 y축 위치 + H 만큼 할당해라
  int camH = lines[startPos].y + H;
  //만약 앞으로 간다면 배경화면의 좌표를 커브 * 2만큼 왼쪽으로 이동시켜라
  if (speed>0) sBackground.move(-lines[startPos].curve*2,0);
  //만약 뒤로 간다면 배경화면의 좌표를 커브 * 2만큼 오른쪽으로 이동시켜라
  if (speed<0) sBackground.move( lines[startPos].curve*2,0);

  int maxy = height;
  float x=0,dx=0;

  ///////draw road////////
  for(int n = startPos; n<startPos+300; n++)  
   {
      //모듈러 연산을 취하는 이유는 루프를 만들기 위해서이다.
      Line &l = lines[n%N_lines_size];
    //플레이어의 위치를 기준으로 바닥을 그려라
    //좌우, 위아래, 앞뒤 좌표를 나타낸다.
    l.project(playerX*roadW-x, camH, startPos*segL_segment_length - (n>=N_lines_size?N_lines_size*segL_segment_length:0));
    //x에 현재 dx만큼 더해서 커브를 만들어줄 것이다.
    x+=dx;
    //현재 좌표의 커브만큼 dx에 더해라
    dx+=l.curve;

    //도로의 y축의 높이를 저장해주기 위해서이다. max는 오버플로우 방지
    l.clip=maxy;
    if (l.Y>=maxy) continue;
    maxy = l.Y;

    // 바닥 패턴을 진한 초록, 연한 초록으로 한다.
    Color grass  = (n/3)%2?Color(16,200,16):Color(0,154,0);
    // 도로 사이드를 흰검 패턴을 돌아가며 준다
    Color rumble = (n/3)%2?Color(255,255,255):Color(0,0,0);
    // 도로의 회색을 칠해준다.
    Color road   = (n/3)%2?Color(107,107,107):Color(105,105,105);

    Line p = lines[(n-1)%N_lines_size]; //previous line

    //가로 전체로 초록색을 칠한다.
    drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
    // 도로 사이드를 칠한다.
    drawQuad(app, rumble,p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2);
    //도로를 칠한다.
    drawQuad(app, road,  p.X, p.Y, p.W, l.X, l.Y, l.W);
   }

  //위에서 만든 오브젝트들(도로)을 300개만큼 앞에 그려라
    ////////draw objects////////
    for(int n=startPos+300; n>startPos; n--)
      lines[n%N_lines_size].drawSprite(app);

    //화면을 출력해라
    app.display();
    }

    return 0;
}
