#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>

#include "ddutil.h"

#define _GetKeyState( vkey ) HIBYTE(GetAsyncKeyState( vkey ))
#define _GetKeyPush( vkey )  LOBYTE(GetAsyncKeyState( vkey ))

HWND MainHwnd;

LPDIRECTDRAW         DirectOBJ;
LPDIRECTDRAWSURFACE  RealScreen;
LPDIRECTDRAWSURFACE  BackScreen;
LPDIRECTDRAWSURFACE  SpriteImage;
LPDIRECTDRAWSURFACE  BackGround;

LPDIRECTDRAWCLIPPER	ClipScreen;

int gFullScreen=0;
int gWidth, gHeight;
int MouseX, MouseY;


BOOL Fail( HWND hwnd )
{
    ShowWindow( hwnd, SW_HIDE );
    MessageBox( hwnd, "DIRECT X 초기화에 실패했습니다.", "프로그래밍", MB_OK );
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

// 메시지로 피드백이 날라가면
long FAR PASCAL WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch ( message )
    {
        //마우스가 움직이면 해당 마우스 위치를 넘겨주고 블리팅해주라.
        case    WM_MOUSEMOVE    :   MouseX = LOWORD(lParam);
                                    MouseY = HIWORD(lParam);
                                    break;
        case    WM_DESTROY      :  _ReleaseAll();
                                    PostQuitMessage( 0 );
                                    break;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}

//게임시작할 때
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
    wc.lpszClassName = "EXAM3";
    RegisterClass( &wc );

    // 윈도우를 만들어라
    MainHwnd = CreateWindowEx (
            0, "EXAM3", NULL, WS_POPUP, 0, 0,
            GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
            NULL, NULL, hInstance, NULL );


    if ( !MainHwnd ) return FALSE;

    //커서를 만들고
    SetFocus( MainHwnd );
    ShowWindow( MainHwnd, nCmdShow );
    UpdateWindow( MainHwnd );
    //커서를 보이지 않게 해라
    ShowCursor( FALSE );

    result = DirectDrawCreate( NULL, &pdd, NULL );
    if ( result != DD_OK ) return Fail( MainHwnd );

    result = pdd->QueryInterface(IID_IDirectDraw, (LPVOID *) &DirectOBJ);
    if ( result != DD_OK ) return Fail( MainHwnd );

	gWidth=x;
	gHeight=y;

	// 윈도우 핸들의 협력 단계를 설정한다.
	if(gFullScreen){
        //서피스를 만들고
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

       //서피스에 캐릭터를 집어넣는다.
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


//타이머에 의해 불러지는 _GameProc
void CALLBACK _GameProc(HWND hWnd, UINT message, UINT wParam, DWORD lParam)
{
    static int Frame = 0, Count = 0;
    RECT BackRect = { 0, 0, 640, 480 }, SpriteRect;

    //사각형에 표현해줘라. 표현해주고 
    BackScreen -> BltFast( 0, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY );

    //사각형의 위치를 잘라라
    //프레임 값을 바꿔주면 그 다음 칸에서는 다음 모양을 보여준다.
    SpriteRect.left     =   Frame * 100;
    SpriteRect.top      =   0;
    SpriteRect.right    =   SpriteRect.left + 100;
    SpriteRect.bottom   =   70;

    //자른 사각형에서 마우스 위치에 가져다 두라
    BackScreen -> BltFast( MouseX - 50, MouseY - 35, SpriteImage, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY );

// enter animation code here!





	if(gFullScreen)
		RealScreen->Flip(NULL, DDFLIP_WAIT);
	else{
		RECT WinRect, SrcRect={0, 0, gWidth, gHeight};

		GetWindowRect(MainHwnd, &WinRect);
		RealScreen->Blt(&WinRect, BackScreen, &SrcRect, DDBLT_WAIT, NULL );
	}

}

int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    MSG msg;

    //게임 모드를 만든다.
    if ( !_GameMode(hInstance, nCmdShow, 640, 480, 32) ) return FALSE;

    //디스크에서 파일을 불러온다.
    SpriteImage = DDLoadBitmap( DirectOBJ, "sprite_char.BMP", 0, 0 );
    BackGround  = DDLoadBitmap( DirectOBJ, "sprite_back.BMP", 0, 0 );

    //주인공 캐릭터는 컬러키가 필요하기 때문에 RGB(0,0,0)해주었다.
    DDSetColorKey( SpriteImage, RGB(0,0,0) );

    //5ms마다 1번씩 _GameProc 를 불러라.
	SetTimer(MainHwnd, 1, 5, _GameProc);

    //마우스나 키보드 인풋을 처리하기 위한 부분
    while ( !_GetKeyState(VK_ESCAPE) )
    {
        if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) )
        {
            if ( !GetMessage(&msg, NULL, 0, 0) ) return msg.wParam;

            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }
    DestroyWindow( MainHwnd );

    return TRUE;
}
