/*
�簢�� 1���� ����� �� �����̵��� ���� ����
���� �������� �߰� �ø����� ���ϴϱ� �������� ����� ���δ�.
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
HWND                    hWndMain;   //ó�� ����� ���� �������̴�. �۷ι��� ����� ������ ���δ�.

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

//WindowProcedure�̴�.
//hWnd - � �����쿡�� message - � �޽����� �Դµ� wParam, lParam - parameter�� � ���� ������ �Դٶ�� �޽����� ���.
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
 * �����츦 ����� ��Ÿ���� ��� ���� �¾��ϴ� ���̴�. �����ϸ� true�� ��ȯ
 * ���� �۾����� �ִ�.
    * create a window
    * �����츦 �����.
    * ���⼭�� �Ʒ� �Լ��� ���� �ڿ� WindowProc�� ���� ó���϶�� ���̴�.
    
    //������ hwnd �����츦 ������� �������� ���� hWndMain - ���� �����쿡 �Ҵ�
    hWndMain = hwnd;

    // DirectDraw�� Create�ض�.

    // SetCooperativeLevel�� DDSCL_FULLSCREEN - Ǯ��ũ������ ���� ������

    // SetDisplayMode - ���÷��� ��带 ������. ���⼭ ������ ���Ѵ�.

    // SetDisplayMode - ���÷��� ��带 ������. ���⼭ ������ ���Ѵ�.

    //CreateSurface - �ʱ� primal surface�� ����� ������.

    // �������� �ð��� �����ϱ� ���� ������ �־���.

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
    //���⸦ �� ���� �Ѵ�. �����쿡�� ���콺�� Ű���� Ŭ���� �߻��ϸ� ��� ó�������� �����ϴ� �Լ��̴�.
    //�����츦 ���� �� �̸��� �������� �ְ� ���߿� ��� ���� ���̳ĸ� ���ϴ� ���̴�.
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
     * �����츦 �����.
     * ���⼭�� �Ʒ� �Լ��� ���� �ڿ� WindowProc�� ���� ó���϶�� ���̴�.
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

    //������ hwnd �����츦 ������� �������� ���� hWndMain - ���� �����쿡 �Ҵ�
    hWndMain = hwnd;

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    // Create the DirectDraw object.
    // DirectDraw�� Create�ض�.
    // DirectDrawCreate - https://docs.microsoft.com/en-us/windows/win32/api/ddraw/nf-ddraw-directdrawcreate
    if ( FAILED( DirectDrawCreate( NULL, &lpDD, NULL ) ) )
	{
        return Fail( hwnd, "Couldn't create DirectDraw object." );
    }

    // Get exclusive mode.
    // SetCooperativeLevel�� DDSCL_FULLSCREEN - Ǯ��ũ������ ���� ������
    if ( FAILED( lpDD->SetCooperativeLevel( hwnd,
                      DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN ) ) )
	{
        return Fail( hwnd, "Couldn't set cooperative level." );
    }

    // Set the display mode to 640 by 480 palettized.
    // SetDisplayMode - ���÷��� ��带 ������. ���⼭ ������ ���Ѵ�.
    if ( FAILED( lpDD->SetDisplayMode( 640, 480, 16 ) ) )
	{
        return Fail( hwnd, "Couldn't set display mode." );
    }

    // Create the primary surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
  
    //CreateSurface - �ʱ� primal surface�� ����� ������.
    if ( FAILED( lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL ) ) )
	{
        return Fail( hwnd, "Couldn't create primary surface." );
    }
    
    // Start the frame timer.
    // �������� �ð��� �����ϱ� ���� ������ �־���.
    // timeGetTime :: �Ķ���� ���� �ý����� ���۵� �ð��� �и�������� ����. Winmm.lib�� ����.
    // https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timegettime

    dwFrameTime = timeGetTime();

    return TRUE;
} /* doInit */

// �����츦 ������ �޾Ƽ� �ð� ����� �Ѵ�.
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

    //���α׷��� ����� ���������� �ð��� ����Ѵ�.
    dwTime = timeGetTime() - dwFrameTime;
    if ( dwTime > 1000 )
    {
        //�����ϴ� �ð� ���̿��� �������� �������� ����ϱ� ���� ����
        dwFrames = ( dwFrameCount*1000 )/dwTime;
        dwFrameTime = timeGetTime();
        dwFrameCount = 0;
    }

    // Clear the primary surface to black using the blitter.
    ddbltfx.dwSize = sizeof( ddbltfx );
    // dwFillColor�� 0���� �ش�. ��İ� ĥ�Ѵٴ� ���̴�.
    ddbltfx.dwFillColor = 0;

    // Blt �Լ��� ���Դ�. lpDDSPrimary - �����̸Ӹ� ���ǽ��� blit�Ѵٴ� ���̴�.
    /*
Blt : ��Ʈ��� ������ memcpy()�� �Ȱ��� �۾��� �����Ѵٰ� ���ø� �˴ϴ�.
Ư�� ���ǽ��� �׷��� ������ �ٸ� ���ǽ��� �����ϴ� �۾��� �����ϴ� �Լ��Դϴ�.
DirectX ���α׷����� �Ҷ� ���÷��̸�尡 Ǯ��ũ���� �ƴѰ�� ���α׷���
ȭ����ü�� ������ �� ���� ������ �̷� ��� DirectX�� ������۸��� ����������
�ʽ��ϴ�. �̷� ��� ���α׷��Ӱ� ���Ƿ� BackBuffer�� ����ؼ� OffScreen��
����� ������� OffScreen�� ��µ� ������ �� �׸��ϴ�. �׸��Ⱑ �Ϸ�Ǹ�
Flip()�Լ� ��� Blt�Լ��� �Ἥ OffScreen�� �׷��� ������ �״�� Primary���ǽ���
�����մϴ�. (���� �̰�� �ܿ��� ���� �뵵�� ���˴ϴ�.)
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
    // �������� 1���� �Űܰ��鼭 
    // ddbltfx.dwFillColor = 255; - ������� ĥ�Ѵ�.
    // dest - ������ �簢���� ����� �����Ѵ�.

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
        // �� �������� �������� ���ش�.
        TextOut( hdc, 320, 0, str, lstrlen( str ) );

        // Don't ever forget this.
        lpDDSPrimary->ReleaseDC( hdc );
    }

    return TRUE;
}

/*
 * WinMain - initialization, message loop
 * WinMain�� mainó�� ���� ó�� ���۵Ǵ� ���̴�.
 * argv, argc ��� ������ command line���� ������ string�� �޴� �͵鿡 ���� ������ �ִ�.
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    MSG         msg;

    //�ʱ�ȭ �۾��� doInit�� �ض�. �ȵǸ� false ����
    if ( !doInit( hInstance, nCmdShow ) )
    {
        return FALSE;
    }

    while ( 1 )
    {
        //PeekMessage, DispatchMessage - �����쿡 ���� ���� �����
        //WindowProc - ������ procedure���� ó���� ���̴�.
        if ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if ( !GetMessage( &msg, NULL, 0, 0 ) )
            {
                return msg.wParam;
            }
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        // �� �۾��� ������ UpdateFrame�� �ض�.
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
