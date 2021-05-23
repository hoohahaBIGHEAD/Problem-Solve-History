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
    MessageBox( hwnd, "DIRECT X �ʱ�ȭ�� �����߽��ϴ�.", "���α׷���", MB_OK );
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

// �޽����� �ǵ���� ���󰡸�
long FAR PASCAL WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch ( message )
    {
        //���콺�� �����̸� �ش� ���콺 ��ġ�� �Ѱ��ְ� �������ֶ�.
        case    WM_MOUSEMOVE    :   MouseX = LOWORD(lParam);
                                    MouseY = HIWORD(lParam);
                                    break;
        case    WM_DESTROY      :  _ReleaseAll();
                                    PostQuitMessage( 0 );
                                    break;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}

//���ӽ����� ��
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

    // �����츦 ������
    MainHwnd = CreateWindowEx (
            0, "EXAM3", NULL, WS_POPUP, 0, 0,
            GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
            NULL, NULL, hInstance, NULL );


    if ( !MainHwnd ) return FALSE;

    //Ŀ���� �����
    SetFocus( MainHwnd );
    ShowWindow( MainHwnd, nCmdShow );
    UpdateWindow( MainHwnd );
    //Ŀ���� ������ �ʰ� �ض�
    ShowCursor( FALSE );

    result = DirectDrawCreate( NULL, &pdd, NULL );
    if ( result != DD_OK ) return Fail( MainHwnd );

    result = pdd->QueryInterface(IID_IDirectDraw, (LPVOID *) &DirectOBJ);
    if ( result != DD_OK ) return Fail( MainHwnd );

	gWidth=x;
	gHeight=y;

	// ������ �ڵ��� ���� �ܰ踦 �����Ѵ�.
	if(gFullScreen){
        //���ǽ��� �����
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

       //���ǽ��� ĳ���͸� ����ִ´�.
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


//Ÿ�̸ӿ� ���� �ҷ����� _GameProc
void CALLBACK _GameProc(HWND hWnd, UINT message, UINT wParam, DWORD lParam)
{
    static int Frame = 0, Count = 0;
    RECT BackRect = { 0, 0, 640, 480 }, SpriteRect;

    //�簢���� ǥ�������. ǥ�����ְ� 
    BackScreen -> BltFast( 0, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY );

    //�簢���� ��ġ�� �߶��
    //������ ���� �ٲ��ָ� �� ���� ĭ������ ���� ����� �����ش�.
    SpriteRect.left     =   Frame * 100;
    SpriteRect.top      =   0;
    SpriteRect.right    =   SpriteRect.left + 100;
    SpriteRect.bottom   =   70;

    //�ڸ� �簢������ ���콺 ��ġ�� ������ �ζ�
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

    //���� ��带 �����.
    if ( !_GameMode(hInstance, nCmdShow, 640, 480, 32) ) return FALSE;

    //��ũ���� ������ �ҷ��´�.
    SpriteImage = DDLoadBitmap( DirectOBJ, "sprite_char.BMP", 0, 0 );
    BackGround  = DDLoadBitmap( DirectOBJ, "sprite_back.BMP", 0, 0 );

    //���ΰ� ĳ���ʹ� �÷�Ű�� �ʿ��ϱ� ������ RGB(0,0,0)���־���.
    DDSetColorKey( SpriteImage, RGB(0,0,0) );

    //5ms���� 1���� _GameProc �� �ҷ���.
	SetTimer(MainHwnd, 1, 5, _GameProc);

    //���콺�� Ű���� ��ǲ�� ó���ϱ� ���� �κ�
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
