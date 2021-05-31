#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>

#include "ddutil.h"

#include <dsound.h>
#include "dsutil.h"


#define _GetKeyState( vkey ) HIBYTE(GetAsyncKeyState( vkey ))
#define _GetKeyPush( vkey )  LOBYTE(GetAsyncKeyState( vkey ))

HWND MainHwnd;

LPDIRECTDRAW         DirectOBJ;
LPDIRECTDRAWSURFACE  RealScreen;
LPDIRECTDRAWSURFACE  BackScreen;
LPDIRECTDRAWSURFACE  SpriteImage;
LPDIRECTDRAWSURFACE  BackGround;
LPDIRECTDRAWSURFACE  Gunship;

LPDIRECTDRAWCLIPPER	ClipScreen;

int gFullScreen=0, Click=0;
//창의 사이즈를 결정한다.
int gWidth=640*2, gHeight=480;
int MouseX=100, MouseY=gHeight/2;

//캐릭터의 기본 시작 위치를 정한다
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
    MessageBox( hwnd, "DIRECT X 초기화에 실패했습니다.", "게임 디자인", MB_OK );
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

//키보드나 마우스가 입력되었을 때 발생한다. _GameProc 는 setTimer 에 의해 30ms마다 1번씩 발생한다.
//주인공의 모션을 여기서 설정
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
                    PosY = PosY - 5; //윈도우에서 Y 좌표 보정
					return 0;

                case VK_DOWN: 
                    PosY = PosY + 5; //윈도우에서 Y 좌표 보정
                    return 0;

				case VK_SPACE:
                    //공격해라
                    Click = 1;
                    //사운드 출력
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
*윈도우를 하나 만들고
* 윈도우에 대한 프로퍼티를 쭉 준다.
* 돌멩이의 움직임을 여기서 만든다.
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

    //풀스크린일 때 셋팅
	if(gFullScreen){
		if((MainHwnd=CreateWindowEx (0, "TEST", NULL, WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), 
				GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL ))==NULL)
			ExitProcess(1);
	}
    //창모드일 때 셋팅
    else{
		if((MainHwnd=CreateWindow("TEST", "이승후", WS_OVERLAPPEDWINDOW, 0, 0, x, 
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


	// 윈도우 핸들의 협력 단계를 설정한다.
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

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////  modify here

void CALLBACK _GameProc(HWND hWnd, UINT message, UINT wParam, DWORD lParam)
{
    RECT BackRect = { 0, 0, 640, 480 };
	RECT DispRect = { 0, 0, gWidth, gHeight };
	RECT SpriteRect, dstRect, WinRect;
    
    //랜덤오브젝트 생성
    static RECT dstRectNew[20];

    BackScreen -> BltFast(0, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY); 
    BackScreen -> BltFast(640, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY); 

    //전역으로 선언했다. 다시 실행되더라도 기존의 값을 가져온다.
    static int Frame = 0;

    RECT SpriteRectBefore, SpriteRectAfter;

    SpriteRect.left     =   Frame * 100;
    SpriteRect.top      =   0;
    SpriteRect.right    =   SpriteRect.left + 100;
    SpriteRect.bottom   =   70;

	if(Click){
        //프레임을 1 더해라. 그게 4보다 크면 다시 0으로 바꿔라
		if ( ++Frame >= 4 ){
			Frame = 0;
			Click = 0;
		}
	}

	if(MouseX<=50) MouseX=50;
	if(MouseX>gWidth-50) MouseX=gWidth-50;
	if(MouseY<=35) MouseY=35;
	if(MouseY>gHeight-35) MouseY=gHeight-35;

    //마우스 좌표를 기준으로 캐릭터 위치 이동
    //BackScreen -> BltFast( MouseX - 50, MouseY - 35, SpriteImage, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY );
    //100과 70짜리니까 50, 35이다.
    //키보드로 캐릭터 위치 이동
    BackScreen->BltFast(PosX, PosY, SpriteImage, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);




	//////////////////////////////
	// Enter splite animation here
	// use srand(int seed); rand();
	// stone            (380, 375)            (405, 395)
	// flare            (360, 425)            (390, 455)


    //돌의 이미지 참조
    SpriteRectBefore.left = 380;
    SpriteRectBefore.top = 375;
    SpriteRectBefore.right = 405;
    SpriteRectBefore.bottom = 395;
    //화염의 이미지 참조
    SpriteRectAfter.left = 360;
    SpriteRectAfter.top = 425;
    SpriteRectAfter.right = 390;
    SpriteRectAfter.bottom = 455;


    //화염의 이미지 참조
	SpriteRect.left = 360; 
	SpriteRect.top = 425; 
	SpriteRect.right = 390; 
	SpriteRect.bottom = 455; 
    
    //------------여기부터
    //창의 좌표 참조 및 크기 설정. 위의 스프라이트를 해당 크기로 바꿔서 출력해준다.
	dstRect.left = 400; 
    dstRect.top = 300;
	dstRect.right = dstRect.left+30; 
    dstRect.bottom = dstRect.top+30;

    //해당 창의 좌표에 스프라이트 이미지를 올려라
	//BackScreen->Blt(&dstRect, Gunship, &SpriteRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
    //------------여기까지 for문을 돌려 돌을 20개 만들어라
    //만약 돌의 위치가 캐릭터 위치와 비슷하다면 폭발시켜라

    //돌의 이미지 참조
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
        //오브젝트 위치 초기화
        if (!isMade[i])
        {
            dstRectNew[i].left = rand() % (gWidth);
            dstRectNew[i].top = rand() % gHeight;
            dstRectNew[i].right = dstRectNew[i].left + 30;
            dstRectNew[i].bottom = dstRectNew[i].top + 30;
            isMade[i] = true;
        }
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

        if ((dstRectNew[i].left + 5 - 50< PosX && PosX < dstRectNew[i].right + 5 - 50) &&
            (dstRectNew[i].top - 5 - 70< PosY && PosY < dstRectNew[i].bottom + 5 - 35))
        {
            isCollapsed[i] = true;
        }

        //충돌하지 않았을 때 보여주기
        if (!isCollapsed[i])
            BackScreen->Blt(&dstRectNew[i], Gunship, &SpriteRectBefore, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
        else {
            if (isCollapsedInt[i]++ == 0)
                _Play(4);
            if (isCollapsedInt[i] < 30)
                BackScreen->Blt(&dstRectNew[i], Gunship, &SpriteRectAfter, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
        }

    }

    //돌의 좌표 참조
	dstRect.left = 500; 
    dstRect.top = 300;
	dstRect.right = dstRect.left+30; 
    dstRect.bottom = dstRect.top+30;

	//BackScreen->Blt(&dstRect, Gunship, &SpriteRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);


	if(gFullScreen)
		RealScreen->Flip(NULL, DDFLIP_WAIT);
	else{
		GetWindowRect(MainHwnd, &WinRect);
		RealScreen->Blt(&WinRect, BackScreen, &DispRect, DDBLT_WAIT, NULL ); 
	}
}

///////////////////////////////////////////////////////////////////////////////////////////


int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    MSG msg;

    if ( !_GameMode(hInstance, nCmdShow, gWidth, gHeight, 32) ) return FALSE;

    SpriteImage = DDLoadBitmap( DirectOBJ, "EXAM3_1.BMP", 0, 0 );
    BackGround  = DDLoadBitmap( DirectOBJ, "EXAM3_2.BMP", 0, 0 );
    Gunship  = DDLoadBitmap( DirectOBJ, "EXAM3_3.BMP", 0, 0 );

    DDSetColorKey( SpriteImage, RGB(0,0,0) );
    DDSetColorKey( Gunship, RGB(0,0,0) );

    //윈도우 프로시져에서 셋타이머가 시작되게 해라.
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
    }
    DestroyWindow( MainHwnd );

    return TRUE;
}
