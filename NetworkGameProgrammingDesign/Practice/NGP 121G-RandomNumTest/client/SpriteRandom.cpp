#include <WinSock2.h>


#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>

#include "ddutil.h"

#include <dsound.h>
#include "dsutil.h"


#define _GetKeyState( vkey ) HIBYTE(GetAsyncKeyState( vkey ))
#define _GetKeyPush( vkey )  LOBYTE(GetAsyncKeyState( vkey ))


////////////////////////////////////////////////////////////
//�������
#include <ws2tcpip.h>
#include <stdio.h>
#include "wtpipv6.h"
#include "Packet.h"
#include "wspiapi.h"

#include <iostream>
#include <sstream>

void usage(char* progname)
{
    fprintf(stderr, "usage: %s [-n name] [-p port] \n", progname);
    fprintf(stderr, "   -n name    Host name to resolve, [127.0.0.1] \n");
    fprintf(stderr, "   -p port    Port number to resolve, [8600] \n");

    ExitProcess(-1);
}


int resolveAddr(int argc, char** argv, char* serverName, char* serverPort)
{
    int count, rc, i;

    serverName[0] = 0;
    serverPort[0] = 0;

    for (i = 1; i < argc; i++)
    {
        if ((argv[i][0] != '-') && (argv[i][0] != '/') && (strlen(argv[i]) < 2))
            usage(argv[0]);

        switch (tolower(argv[i][1]))
        {

        case 'n':       // name to resolve
            if (i + 1 >= argc)
                usage(argv[0]);
            strcpy(serverName, argv[++i]);
            break;

        case 'p':       // port/service to resolve
            if (i + 1 >= argc)
                usage(argv[0]);
            strcpy(serverPort, argv[++i]);
            break;


        default:
            usage(argv[0]);
            break;
        }
    }
    if (serverName[0] == 0)
        strcpy(serverName, "127.0.0.1");
    if (serverPort[0] == 0)
        strcpy(serverPort, "8600");

    printf("** Resolve Address %s:%s \n", serverName, serverPort);


    //******************* remoteHost = gethostbyname(host_name);

    struct hostent* remoteHost;

    remoteHost = gethostbyname(serverName);	// ns.cau.ac.kr
    printf(">> gethostbyname Official name: %s", remoteHost->h_name);

    struct in_addr addr;

    addr.s_addr = *(u_long*)remoteHost->h_addr_list[0];
    printf("-(%s) \n", inet_ntoa(addr));


    if (!isalpha(serverName[0]))
    {
        struct in_addr addr = { 0 };
        addr.s_addr = inet_addr(serverName); 	// 127.0.0.1
        remoteHost = gethostbyaddr((char*)&addr, 4, AF_INET);
        printf(">> gethostbyaddr Official name: %s\n", remoteHost->h_name);
    }

    //*****************************************************************************

    // Resolve the name/address - first assume that the name might be a string
    // literal address
    struct addrinfo  hints, * res = NULL, * ptr;


    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_NUMERICHOST;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    rc = getaddrinfo(serverName, serverPort, &hints, &res);
    if (rc != 0)
    {
        if (rc == WSAHOST_NOT_FOUND)
        {
            hints.ai_flags = AI_CANONNAME;
            printf("** AI_CANONNAME\n");
            rc = getaddrinfo(serverName, serverPort, &hints, &res);
            if (rc != 0)
            {
                fprintf(stderr, "getaddrinfo failed: %d\n", rc);
                return -1;
            }
        }
        else
        {
            fprintf(stderr, "getaddrinfo failed: %d\n", rc);
            return -1;
        }
    }

    // Count how many addresses were returned
    count = 0;
    ptr = res;
    while (ptr)
    {
        count++;
        ptr = ptr->ai_next;
    }
    printf("** Hostname '%s' resolved to %d addresses\n", serverName, count);


    //Do a reverse lookup on each of the resolved address
    char numerichost[NI_MAXHOST];

    rc = getnameinfo(res->ai_addr, res->ai_addrlen, numerichost, NI_MAXHOST, NULL, 0, NI_NUMERICHOST); // NI_NAMEREQD, NI_NUMERICHOST
    if (rc != 0)
    {
        fprintf(stderr, "getnameinfo failed: %d\n", rc);
        return -1;
    }
    strcpy(serverName, numerichost);

    printf(">> Numeric address resolved: %s:%s\n", serverName, serverPort);

    // Free up the results from getaddrinfo
    freeaddrinfo(res);

    return 1;
}
//************************************************************************



DWORD WINAPI NetReceive(LPVOID socketConnect)
{
    char recvBuffer[127];
    int  RecvBytes;

    Packet	recvPacket;
    char	receiveBuffer[PACKETBUFFERSIZE];
    int		receivedPacketSize = 0;


    while (1) {

        ///////////////////////////////////////////////////////
        int bufSize = PACKETBUFFERSIZE - receivedPacketSize;

        if ((RecvBytes = recv((SOCKET)socketConnect, &(receiveBuffer[receivedPacketSize]), bufSize, 0)) < 1) {
            ::shutdown((SOCKET)socketConnect, SD_BOTH);
            ::closesocket((SOCKET)socketConnect);
            socketConnect = (LPVOID)INVALID_SOCKET;
            break;
        }
        receivedPacketSize += RecvBytes;

        //���⼭ ��Ŷ�� �޵��� ��������.
        //while( receivedPacketSize > 0 )	// parsing Packet Length
        while (1)	// parsing Packet Length	//1�� �ٲٴ� �ٷ� �޾�����.
        {
            ///////////////////////////////////////////////////////////////////////////////////////
            int recvBytes;

            int bufSize;

            bufSize = PACKETBUFFERSIZE - receivedPacketSize;

            if ((recvBytes = recv((SOCKET)socketConnect, &(receiveBuffer[receivedPacketSize]), bufSize, 0)) < 1) {
                //  ����� ���� �Ŀ��� Ŭ���̾�Ʈ�� ������ �����Ѵ�.
                printf("*** Closed the client : this\n");

                //::shutdown(socketClient[k], SD_BOTH);
                //::closesocket(socketClient[k]);
                //socketClient[k] = INVALID_SOCKET;
                break;
            }

            //���Ⱑ �޴� �κ��̴�. �̰��� �Űܶ�.
            //printf("<<< Receive bytes %d from server\n", recvBytes);	�޾Ҵٴ� ǥ�� ����
            receivedPacketSize += recvBytes;

            while (receivedPacketSize > 0)	// parsing Packet Length
            {
                recvPacket.copyToBuffer(receiveBuffer, receivedPacketSize);
                int packetlength = (int)recvPacket.getPacketSize();

                if (receivedPacketSize >= packetlength)
                {
                    //  Parsing, main routine 
                    recvPacket.readData(recvBuffer, recvPacket.getDataFieldSize());
                    printf("(%d Bytes, ID=%d) %s\n", recvPacket.getDataFieldSize(), recvPacket.id(), recvBuffer);


                    //sentBytes = ::send(socketConnect[k], sendPacket.getPacketBuffer(), sendPacket.getPacketSize(), 0);

                    //::send( socketClient[k], recvBuffer, strlen(recvBuffer)+1, 0 );
                    //::send(socketClient, recvPacket[k].getPacketBuffer(), recvPacket[k].getPacketSize(), 0);

                    receivedPacketSize -= packetlength;
                    if (receivedPacketSize > 0)
                    {
                        ::CopyMemory(recvBuffer, (receiveBuffer + recvPacket.getPacketSize()), receivedPacketSize);
                        ::CopyMemory(receiveBuffer, recvBuffer, receivedPacketSize);
                    }
                }
                else
                    break;
            }

            ///////////////////////////////////////////////////////////////////////////////////////


        }

        ///////////////////////////////////////////////////////

    }

    return NULL;
}




//�������
////////////////////////////////////////////////////////////


HWND MainHwnd;

LPDIRECTDRAW         DirectOBJ;
LPDIRECTDRAWSURFACE  RealScreen;
LPDIRECTDRAWSURFACE  BackScreen;
LPDIRECTDRAWSURFACE  SpriteImage;
LPDIRECTDRAWSURFACE  BackGround;
LPDIRECTDRAWSURFACE  Gunship;

LPDIRECTDRAWCLIPPER	ClipScreen;

int gFullScreen=0, Click=0;
//â�� ����� �����Ѵ�.
int gWidth=640*2, gHeight=480;
int MouseX=100, MouseY=gHeight/2;

//ĳ������ �⺻ ���� ��ġ�� ���Ѵ�
int PosX = 100, PosY = gHeight / 2;

////////////////////

LPDIRECTSOUND       SoundOBJ = NULL;
LPDIRECTSOUNDBUFFER SoundDSB = NULL;
DSBUFFERDESC        DSB_desc;

HSNDOBJ Sound[10];


BOOL _InitDirectSound( void )
{
    if ( DirectSoundCreate(NULL,&SoundOBJ,NULL) == DS_OK )
    {
        if (SoundOBJ->SetCooperativeLevel(MainHwnd,DSSCL_PRIORITY)!=DS_OK) return FALSE;

        memset(&DSB_desc,0,sizeof(DSBUFFERDESC));
        DSB_desc.dwSize = sizeof(DSBUFFERDESC);
        DSB_desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;

        if (SoundOBJ->CreateSoundBuffer(&DSB_desc,&SoundDSB,NULL)!=DS_OK) return FALSE;
        SoundDSB -> SetVolume(DSBVOLUME_MAX); // DSBVOLUME_MIN
        SoundDSB -> SetPan(DSBPAN_RIGHT);
        return TRUE;
    }
    return FALSE;
}

void _Play( int num )
{
    SndObjPlay( Sound[num], NULL );
}

////////////////////////


BOOL Fail( HWND hwnd )
{
    ShowWindow( hwnd, SW_HIDE );
    MessageBox( hwnd, "DIRECT X �ʱ�ȭ�� �����߽��ϴ�.", "���� ������", MB_OK );
    DestroyWindow( hwnd );
    return FALSE;
}

void _ReleaseAll( void )
{
    if ( DirectOBJ != NULL )
    {
        if ( RealScreen != NULL )
        {
            RealScreen->Release();
            RealScreen = NULL;
        }
        if ( SpriteImage != NULL )
        {
            SpriteImage->Release();
            SpriteImage = NULL;
        }
        if ( BackGround != NULL )
        {
            BackGround->Release();
            BackGround = NULL;
        }
        DirectOBJ->Release();
        DirectOBJ = NULL;
    }
}

//Ű���峪 ���콺�� �ԷµǾ��� �� �߻��Ѵ�. _GameProc �� setTimer �� ���� 30ms���� 1���� �߻��Ѵ�.
//���ΰ��� ����� ���⼭ ����
long FAR PASCAL WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	int Step=5;


    switch ( message )
    {

        case    WM_MOUSEMOVE    :   MouseX = LOWORD(lParam);
                                    MouseY = HIWORD(lParam);
                                    break;

		case	WM_LBUTTONDOWN	: 	Click=1;
									_Play( 3 );
									break;
        case	WM_KEYDOWN:            
            switch (wParam)
            {
                case VK_ESCAPE:
                case VK_F12: 
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    return 0;            

				case VK_LEFT:
                    PosX = PosX - 5;
					return 0;

                case VK_RIGHT: 
                    PosX = PosX + 5;
					return 0;

                case VK_UP:
                    PosY = PosY - 5; //�����쿡�� Y ��ǥ ����
					return 0;

                case VK_DOWN: 
                    PosY = PosY + 5; //�����쿡�� Y ��ǥ ����
                    return 0;

				case VK_SPACE:
                    //�����ض�
                    Click = 1;
                    //���� ���
                    _Play(3);
					break;
			}
            break;

        case    WM_DESTROY      :  _ReleaseAll();
                                    PostQuitMessage( 0 );
                                    break;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}

/*
*�����츦 �ϳ� �����
* �����쿡 ���� ������Ƽ�� �� �ش�.
* �������� �������� ���⼭ �����.
*/
BOOL _GameMode( HINSTANCE hInstance, int nCmdShow, int x, int y, int bpp )
{
    HRESULT result;
    WNDCLASS wc;
    DDSURFACEDESC ddsd;
    DDSCAPS ddscaps;
    LPDIRECTDRAW pdd;

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "TEST";
    RegisterClass( &wc );

    //Ǯ��ũ���� �� ����
	if(gFullScreen){
		if((MainHwnd=CreateWindowEx (0, "TEST", NULL, WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), 
				GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL ))==NULL)
			ExitProcess(1);
	}
    //â����� �� ����
    else{
		if((MainHwnd=CreateWindow("TEST", "�̽���", WS_OVERLAPPEDWINDOW, 0, 0, x, 
									y, NULL, NULL, hInstance, NULL))==NULL)
			ExitProcess(1);
		SetWindowPos(MainHwnd, NULL, 100, 100, x, y, SWP_NOZORDER);
	}

    SetFocus( MainHwnd );
    ShowWindow( MainHwnd, nCmdShow );
    UpdateWindow( MainHwnd );
    ShowCursor( FALSE );

    result = DirectDrawCreate( NULL, &pdd, NULL );
    if ( result != DD_OK ) return Fail( MainHwnd );

    result = pdd->QueryInterface(IID_IDirectDraw, (LPVOID *) &DirectOBJ);
    if ( result != DD_OK ) return Fail( MainHwnd );


	// ������ �ڵ��� ���� �ܰ踦 �����Ѵ�.
	if(gFullScreen){
	    result = DirectOBJ->SetCooperativeLevel( MainHwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
		if ( result != DD_OK ) return Fail( MainHwnd );

		result = DirectOBJ->SetDisplayMode( x, y, bpp);
		if ( result != DD_OK ) return Fail( MainHwnd );

		memset( &ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;

	    result = DirectOBJ -> CreateSurface( &ddsd, &RealScreen, NULL );
	   if ( result != DD_OK ) return Fail( MainHwnd );

		memset( &ddscaps, 0, sizeof(ddscaps) );
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		result = RealScreen -> GetAttachedSurface( &ddscaps, &BackScreen );
		if ( result != DD_OK ) return Fail( MainHwnd );
	}
	else{
	    result = DirectOBJ->SetCooperativeLevel( MainHwnd, DDSCL_NORMAL );
		if ( result != DD_OK ) return Fail( MainHwnd );

		memset( &ddsd, 0, sizeof(ddsd) );
	    ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS;
	    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		ddsd.dwBackBufferCount = 0;

		result = DirectOBJ -> CreateSurface( &ddsd, &RealScreen, NULL );
	    if(result != DD_OK) return Fail(MainHwnd);

		memset( &ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof(ddsd);
	    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwWidth = x; 
		ddsd.dwHeight = y;
		result = DirectOBJ->CreateSurface( &ddsd, &BackScreen, NULL );
		if ( result != DD_OK ) return Fail( MainHwnd );

		result = DirectOBJ->CreateClipper( 0, &ClipScreen, NULL);
		if ( result != DD_OK ) return Fail( MainHwnd );

		result = ClipScreen->SetHWnd( 0, MainHwnd );
		if ( result != DD_OK ) return Fail( MainHwnd );

		result = RealScreen->SetClipper( ClipScreen );
		if ( result != DD_OK ) return Fail( MainHwnd );

		SetWindowPos(MainHwnd, NULL, 100, 100, x, y, SWP_NOZORDER | SWP_NOACTIVATE); 
	}


    return TRUE;
}

void CALLBACK _GameProc(HWND hWnd, UINT message, UINT wParam, DWORD lParam);




WSADATA wsaData;
SOCKET socketConnect = INVALID_SOCKET;
struct sockaddr_in serverAddr;
int  k;

HANDLE handleThread;
char serverName[120], serverPort[120];

Packet sendPacket;
char sendBuffer[127];
int sentBytes, count = 0;

std::string temp;


int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    ///////////////////////////////////
    


    ::WSAStartup(0x202, &wsaData);
    socketConnect = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketConnect == INVALID_SOCKET)
    {
        printf("Cannot create socket %d !!\n", k);
    }

    //******************************* Address and port resolve

    if (resolveAddr(__argc, __argv, serverName, serverPort) < 1) {
        printf("*** Unable to resolve server name !\n");
        ExitProcess(-1);
    }

    //  ������ ������ ������ �����Ѵ�.
    ::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ::inet_addr(serverName);
    serverAddr.sin_port = ::htons(atoi(serverPort));

    //********************************************************



    if (socketConnect != INVALID_SOCKET) {
        if (::connect(socketConnect, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            printf("Cannot connect to server %d !!\n", k);
            socketConnect = INVALID_SOCKET;
            exit(0);
        }
        else {
            // create thread for receive
            handleThread = CreateThread(NULL, 0, NetReceive, (void*)socketConnect, THREAD_PRIORITY_NORMAL, NULL);
        }
    }




    ///////////////////////////////////


    MSG msg;

    if ( !_GameMode(hInstance, nCmdShow, gWidth, gHeight, 32) ) return FALSE;

    SpriteImage = DDLoadBitmap( DirectOBJ, "EXAM3_1.BMP", 0, 0 );
    BackGround  = DDLoadBitmap( DirectOBJ, "EXAM3_2.BMP", 0, 0 );
    Gunship  = DDLoadBitmap( DirectOBJ, "EXAM3_3.BMP", 0, 0 );

    DDSetColorKey( SpriteImage, RGB(0,0,0) );
    DDSetColorKey( Gunship, RGB(0,0,0) );

    //������ ���ν������� ��Ÿ�̸Ӱ� ���۵ǰ� �ض�.
	SetTimer(MainHwnd, 1, 30, _GameProc);


///////////////////

    if ( _InitDirectSound() )
    {
        Sound[0] = SndObjCreate(SoundOBJ,"MUSIC.WAV",1);
        Sound[1] = SndObjCreate(SoundOBJ,"LAND.WAV",2);
        Sound[2] = SndObjCreate(SoundOBJ,"GUN1.WAV",2);
        Sound[3] = SndObjCreate(SoundOBJ,"KNIFE1.WAV",2);
        Sound[4] = SndObjCreate(SoundOBJ,"DAMAGE1.WAV",2);
        Sound[5] = SndObjCreate(SoundOBJ,"DAMAGE2.WAV",2);

//        SndObjPlay( Sound[0], DSBPLAY_LOOPING );
    }
//////////////////

    while ( !_GetKeyState(VK_ESCAPE) )
    {

        if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) )
        {
            if ( !GetMessage(&msg, NULL, 0, 0) ) return msg.wParam;

            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
//        else _GameProc();


        //����
        /*
        std::cin >> PosX >> PosY;
        //sendBuffer = tmp.str().c_str();
        fgets(sendBuffer, 126, stdin);

        if (socketConnect != INVALID_SOCKET) {
            sendPacket.clear();
            sendPacket.id(1000 + count);
            count++;
            sendPacket.writeData(sendBuffer, strlen(sendBuffer) + 1);

            sentBytes = ::send(socketConnect, sendPacket.getPacketBuffer(), sendPacket.getPacketSize(), 0);

            if (sentBytes < 0) {
                ::shutdown(socketConnect, SD_BOTH);
                ::closesocket(socketConnect);
                socketConnect = INVALID_SOCKET;
            }

            Sleep(100);
        }
        */
        //����

    }
    DestroyWindow( MainHwnd );

    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////  modify here

void CALLBACK _GameProc(HWND hWnd, UINT message, UINT wParam, DWORD lParam)
{
    RECT BackRect = { 0, 0, 640, 480 };
    RECT DispRect = { 0, 0, gWidth, gHeight };
    RECT SpriteRect, dstRect, WinRect;

    //����������Ʈ ����
    static RECT dstRectNew[20];

    BackScreen->BltFast(0, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
    BackScreen->BltFast(640, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

    //�������� �����ߴ�. �ٽ� ����Ǵ��� ������ ���� �����´�.
    static int Frame = 0;

    RECT SpriteRectBefore, SpriteRectAfter;

    SpriteRect.left = Frame * 100;
    SpriteRect.top = 0;
    SpriteRect.right = SpriteRect.left + 100;
    SpriteRect.bottom = 70;

    if (Click) {
        //�������� 1 ���ض�. �װ� 4���� ũ�� �ٽ� 0���� �ٲ��
        if (++Frame >= 4) {
            Frame = 0;
            Click = 0;
        }
    }

    if (MouseX <= 50) MouseX = 50;
    if (MouseX > gWidth - 50) MouseX = gWidth - 50;
    if (MouseY <= 35) MouseY = 35;
    if (MouseY > gHeight - 35) MouseY = gHeight - 35;

    //���콺 ��ǥ�� �������� ĳ���� ��ġ �̵�
    //BackScreen -> BltFast( MouseX - 50, MouseY - 35, SpriteImage, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY );
    //100�� 70¥���ϱ� 50, 35�̴�.
    //Ű����� ĳ���� ��ġ �̵�
    BackScreen->BltFast(PosX, PosY, SpriteImage, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);




    //////////////////////////////
    // Enter splite animation here
    // use srand(int seed); rand();
    // stone            (380, 375)            (405, 395)
    // flare            (360, 425)            (390, 455)


    //���� �̹��� ����
    SpriteRectBefore.left = 380;
    SpriteRectBefore.top = 375;
    SpriteRectBefore.right = 405;
    SpriteRectBefore.bottom = 395;
    //ȭ���� �̹��� ����
    SpriteRectAfter.left = 360;
    SpriteRectAfter.top = 425;
    SpriteRectAfter.right = 390;
    SpriteRectAfter.bottom = 455;


    //ȭ���� �̹��� ����
    SpriteRect.left = 360;
    SpriteRect.top = 425;
    SpriteRect.right = 390;
    SpriteRect.bottom = 455;

    //------------�������
    //â�� ��ǥ ���� �� ũ�� ����. ���� ��������Ʈ�� �ش� ũ��� �ٲ㼭 ������ش�.
    dstRect.left = 400;
    dstRect.top = 300;
    dstRect.right = dstRect.left + 30;
    dstRect.bottom = dstRect.top + 30;

    //�ش� â�� ��ǥ�� ��������Ʈ �̹����� �÷���
    //BackScreen->Blt(&dstRect, Gunship, &SpriteRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
    //------------������� for���� ���� ���� 20�� ������
    //���� ���� ��ġ�� ĳ���� ��ġ�� ����ϴٸ� ���߽��Ѷ�

    //���� �̹��� ����
    SpriteRect.left = 380;
    SpriteRect.top = 375;
    SpriteRect.right = 405;
    SpriteRect.bottom = 395;


    static BOOLEAN isMade[20] = { false };
    static BOOLEAN isCollapsed[20] = { false };
    static int isCollapsedInt[20] = { 0 };
    //gWidth*2 gHeight
    srand(0);
    for (size_t i = 0; i < 20; i++)
    {
        //������Ʈ ��ġ �ʱ�ȭ
        if (!isMade[i])
        {
            dstRectNew[i].left = rand() % (gWidth);
            dstRectNew[i].top = rand() % gHeight;
            dstRectNew[i].right = dstRectNew[i].left + 30;
            dstRectNew[i].bottom = dstRectNew[i].top + 30;
            isMade[i] = true;
        }
        //�� ������
        else
        {
            if (dstRectNew[i].left == 0)
            {
                dstRectNew[i].left += gWidth;
                dstRectNew[i].right += gWidth;
            }
            dstRectNew[i].left-- % (gWidth);
            dstRectNew[i].right-- % (gWidth);
        }

        //�ε�����
        if ((dstRectNew[i].left + 5 - 50 < PosX && PosX < dstRectNew[i].right + 5 - 50) &&
            (dstRectNew[i].top - 5 - 70 < PosY && PosY < dstRectNew[i].bottom + 5 - 35))
        {
            isCollapsed[i] = true;
        }

        //�浹���� �ʾ��� �� �����ֱ�
        if (!isCollapsed[i])
            BackScreen->Blt(&dstRectNew[i], Gunship, &SpriteRectBefore, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
        else {
            if (isCollapsedInt[i]++ == 0)
                _Play(4);
            if (isCollapsedInt[i] < 30)
                BackScreen->Blt(&dstRectNew[i], Gunship, &SpriteRectAfter, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
        }

    }

    //���� ��ǥ ����
    dstRect.left = 500;
    dstRect.top = 300;
    dstRect.right = dstRect.left + 30;
    dstRect.bottom = dstRect.top + 30;

    //BackScreen->Blt(&dstRect, Gunship, &SpriteRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);


    if (gFullScreen)
        RealScreen->Flip(NULL, DDFLIP_WAIT);
    else {
        GetWindowRect(MainHwnd, &WinRect);
        RealScreen->Blt(&WinRect, BackScreen, &DispRect, DDBLT_WAIT, NULL);
    }


    //��Ŷ ������
    temp = "X:";
    temp.append(std::to_string(PosX));
    temp.append("Y:");
    temp.append(std::to_string(PosY));
    strcpy(sendBuffer, temp.c_str());

    //fgets(sendBuffer, 126, stdin);

//    sendBuffer = num_char;
  //  sprintf(sendBuffer, "%d", PosX);
    if (socketConnect != INVALID_SOCKET) {
        sendPacket.clear();
        sendPacket.id(1000 + count);
        count++;
        sendPacket.writeData(sendBuffer, strlen(sendBuffer) + 1);

        sentBytes = ::send(socketConnect, sendPacket.getPacketBuffer(), sendPacket.getPacketSize(), 0);

        if (sentBytes < 0) {
            ::shutdown(socketConnect, SD_BOTH);
            ::closesocket(socketConnect);
            socketConnect = INVALID_SOCKET;
        }
        //Sleep(100);
    }

}

///////////////////////////////////////////////////////////////////////////////////////////