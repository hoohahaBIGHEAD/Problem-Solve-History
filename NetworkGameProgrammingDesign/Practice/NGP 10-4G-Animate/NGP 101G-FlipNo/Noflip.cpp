/*
사각형 1개를 만들고 쭉 움직이도록 만든 파일
위에 프레임이 뜨고 플리핑을 안하니까 찢어지는 모습이 보인다.
*/

#define NAME "Noflip"
#define TITLE "Page Flipping"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <ddraw.h>
#include <mmsystem.h>

LPDIRECTDRAW            lpDD;           // DirectDraw object
LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE     lpDDSBack;      // DirectDraw back buffer surface
BOOL                    bActive;        // Is application active
HWND                    hWndMain;   //처음 선언된 메인 윈도우이다. 글로벌로 선언된 것으로 보인다.

DWORD                   dwFrameTime = 0;    // Time of the last frame.
DWORD                   dwFrames = 0;       // The frame rate (frames/second).
DWORD                   dwFrameCount = 0;   // Frames displayed.

LONG                    position = 0;   // Current position of "sprite"

static void ReleaseObjects( void )
{
    if ( lpDD != NULL )
    {
        if ( lpDDSPrimary != NULL )
        {
            lpDDSPrimary->Release();
            lpDDSPrimary = NULL;
        }
        lpDD->Release();
        lpDD = NULL;
    }
}

BOOL Fail( HWND hwnd,  char *szMsg )
{
    ReleaseObjects();
    OutputDebugString( szMsg );
    DestroyWindow( hwnd );
    return FALSE;
}

//WindowProcedure이다.
//hWnd - 어떤 윈도우에서 message - 어떤 메시지가 왔는데 wParam, lParam - parameter는 어떤 것을 가지고 왔다라는 메시지가 뜬다.
long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
                            WPARAM wParam, LPARAM lParam )
{
    switch ( message )
    {
        case WM_ACTIVATEAPP:
            bActive = wParam;
            break;

        case WM_CREATE:
            break;

        case WM_SETCURSOR:
            SetCursor( NULL );    // Turn off the mouse cursor
            return TRUE;
 
        case WM_KEYDOWN:
            switch ( wParam )
            {
                case VK_ESCAPE:
                case VK_F12:
                    PostMessage( hWnd, WM_CLOSE, 0, 0 );
                    break;
            }
            break;

        case WM_DESTROY:
            ReleaseObjects();
            PostQuitMessage( 0 );
            break;
        }

    return DefWindowProc( hWnd, message, wParam, lParam );
} /* WindowProc */

/*
 * doInit - Create the window, initialize data, etc.
 * 윈도우를 만들고 스타일을 어떻게 할지 셋업하는 것이다. 성공하면 true를 반환
 * 여러 작업들이 있다.
    * create a window
    * 윈도우를 만든다.
    * 여기서는 아래 함수를 만든 뒤에 WindowProc에 가서 처리하라는 뜻이다.
    
    //위에서 hwnd 윈도우를 만들었고 윈도우의 값을 hWndMain - 메인 윈도우에 할당
    hWndMain = hwnd;

    // DirectDraw를 Create해라.

    // SetCooperativeLevel을 DDSCL_FULLSCREEN - 풀스크린으로 만든 다음에

    // SetDisplayMode - 디스플레이 모드를 만들어라. 여기서 사이즈 정한다.

    // SetDisplayMode - 디스플레이 모드를 만들어라. 여기서 사이즈 정한다.

    //CreateSurface - 초기 primal surface를 만들고 끝난다.

    // 프레임의 시간을 측정하기 위해 변수를 주었다.

 */
static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
    HWND                hwnd;
    WNDCLASS            wc;
    DDSURFACEDESC       ddsd;       // Surface description structure
    char*               szBitmap = "SQUARE.BMP";    // Our "artwork"

    /*
     * set up and register window class
     */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    //여기를 잘 봐야 한다. 윈도우에서 마우스나 키보드 클릭이 발생하면 어디서 처리할지를 결정하는 함수이다.
    //윈도우를 만들 때 이름을 무엇으로 주고 나중에 어떻게 만들 것이냐를 말하는 것이다.
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NAME;
    wc.lpszClassName = NAME;
    RegisterClass( &wc );
    
    /*
     * create a window
     * 윈도우를 만든다.
     * 여기서는 아래 함수를 만든 뒤에 WindowProc에 가서 처리하라는 뜻이다.
     */
    hwnd = CreateWindowEx(
        WS_EX_TOPMOST,
        NAME,
        TITLE,
        WS_POPUP,
        0, 0,
        GetSystemMetrics( SM_CXSCREEN ),
        GetSystemMetrics( SM_CYSCREEN ),
        NULL,
        NULL,
        hInstance,
        NULL );

    if ( !hwnd )
    {
        return FALSE;
    }

    //위에서 hwnd 윈도우를 만들었고 윈도우의 값을 hWndMain - 메인 윈도우에 할당
    hWndMain = hwnd;

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    // Create the DirectDraw object.
    // DirectDraw를 Create해라.
    // DirectDrawCreate - https://docs.microsoft.com/en-us/windows/win32/api/ddraw/nf-ddraw-directdrawcreate
    if ( FAILED( DirectDrawCreate( NULL, &lpDD, NULL ) ) )
	{
        return Fail( hwnd, "Couldn't create DirectDraw object." );
    }

    // Get exclusive mode.
    // SetCooperativeLevel을 DDSCL_FULLSCREEN - 풀스크린으로 만든 다음에
    if ( FAILED( lpDD->SetCooperativeLevel( hwnd,
                      DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN ) ) )
	{
        return Fail( hwnd, "Couldn't set cooperative level." );
    }

    // Set the display mode to 640 by 480 palettized.
    // SetDisplayMode - 디스플레이 모드를 만들어라. 여기서 사이즈 정한다.
    if ( FAILED( lpDD->SetDisplayMode( 640, 480, 16 ) ) )
	{
        return Fail( hwnd, "Couldn't set display mode." );
    }

    // Create the primary surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
  
    //CreateSurface - 초기 primal surface를 만들고 끝난다.
    if ( FAILED( lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL ) ) )
	{
        return Fail( hwnd, "Couldn't create primary surface." );
    }
    
    // Start the frame timer.
    // 프레임의 시간을 측정하기 위해 변수를 주었다.
    // timeGetTime :: 파라메터 없고 시스템이 시작된 시간을 밀리세컨드로 리턴. Winmm.lib를 쓴다.
    // https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timegettime

    dwFrameTime = timeGetTime();

    return TRUE;
} /* doInit */

// 윈도우를 변수로 받아서 시간 계산을 한다.
BOOL UpdateFrame( HWND hwnd )
{
    HDC                 hdc;
    char                str[255];
    DDBLTFX             ddbltfx;
    RECT                dest;
    DWORD               dwTime;

    // When a second or more has elapsed (dwTime > 1000) since
    // the last update, update the frame rate estimate.
    dwFrameCount++;

    //프로그램이 진행된 다음부터의 시간을 계산한다.
    dwTime = timeGetTime() - dwFrameTime;
    if ( dwTime > 1000 )
    {
        //저장하는 시간 사이에서 프레임이 얼마인지를 계산하기 위한 수식
        dwFrames = ( dwFrameCount*1000 )/dwTime;
        dwFrameTime = timeGetTime();
        dwFrameCount = 0;
    }

    // Clear the primary surface to black using the blitter.
    ddbltfx.dwSize = sizeof( ddbltfx );
    // dwFillColor를 0으로 준다. 까맣게 칠한다는 뜻이다.
    ddbltfx.dwFillColor = 0;

    // Blt 함수가 나왔다. lpDDSPrimary - 프라이머리 서피스에 blit한다는 뜻이다.
    /*
Blt : 블리트라고 읽으며 memcpy()와 똑같은 작업을 수행한다고 보시면 됩니다.
특정 서피스에 그려진 내용을 다른 서피스로 복사하는 작업을 수행하는 함수입니다.
DirectX 프로그래밍을 할때 디스플레이모드가 풀스크린이 아닌경우 프로그램이
화면전체를 독점할 수 없기 때문에 이런 경우 DirectX는 더블버퍼링을 지원해주지
않습니다. 이런 경우 프로그래머가 임의로 BackBuffer를 대신해서 OffScreen을
만들고 만들어진 OffScreen에 출력된 내용을 다 그립니다. 그리기가 완료되면
Flip()함수 대신 Blt함수를 써서 OffScreen에 그려진 내용을 그대로 Primary서피스에
복사합니다. (물론 이경우 외에도 여러 용도로 사용됩니다.)
    */
    if ( FAILED( lpDDSPrimary->Blt( NULL, NULL, NULL,
                    DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx ) ) )
	{
        return Fail( hwnd, "Couldn't clear buffer." );
    }

    // Use the blitter to draw a white square on the surface, moving it
    // slowly from left to right.
    // This operation is performed multiple times in a loop to simulate the
    // drawing of multiple sprites.
    // 포지션을 1개씩 옮겨가면서 
    // ddbltfx.dwFillColor = 255; - 흰색으로 칠한다.
    // dest - 목적지 사각형의 사이즈를 정의한다.

    position += 1;
    if ( position > 540 ) position = 0;

    ddbltfx.dwFillColor = 255;
    dest.left = position;
    dest.top = 190;
    dest.right = dest.left + 100;
    dest.bottom = 290;

    if ( FAILED( lpDDSPrimary->Blt( &dest, NULL, NULL,
                    DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx ) ) )
	{
        return Fail( hwnd, "Couldn't Blt." );
    }

    // Use GDI to write the current frame rate.

    if ( FAILED( lpDDSPrimary->GetDC( &hdc ) ) )
	{
        return Fail( hwnd, "Couldn't get DC." );
    }
    else
    {
        sprintf( str, "%d", dwFrames );
        SetBkColor( hdc, RGB( 0, 0, 0 ) );
        SetTextColor( hdc, RGB( 255, 255, 255 ) );
        SetTextAlign( hdc, TA_CENTER );
        // 몇 프레임이 찍히는지 써준다.
        TextOut( hdc, 320, 0, str, lstrlen( str ) );

        // Don't ever forget this.
        lpDDSPrimary->ReleaseDC( hdc );
    }

    return TRUE;
}

/*
 * WinMain - initialization, message loop
 * WinMain은 main처럼 제일 처음 시작되는 곳이다.
 * argv, argc 대신 들어오는 command line에서 들어오는 string을 받는 것들에 대한 설명이 있다.
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    MSG         msg;

    //초기화 작업인 doInit을 해라. 안되면 false 리턴
    if ( !doInit( hInstance, nCmdShow ) )
    {
        return FALSE;
    }

    while ( 1 )
    {
        //PeekMessage, DispatchMessage - 윈도우에 무슨 일이 생기면
        //WindowProc - 윈도우 procedure에서 처리할 것이다.
        if ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if ( !GetMessage( &msg, NULL, 0, 0 ) )
            {
                return msg.wParam;
            }
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        // 위 작업이 없으면 UpdateFrame을 해라.
        else if ( bActive )
        {   
            UpdateFrame( hWndMain );
        }
        else
        {
            WaitMessage();
        }
    }
} /* WinMain */
