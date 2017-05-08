//=============================================================================
// メイン
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "fpsManager.h"

//=============================================================================
// 関数のプロトタイプ宣言
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

//=============================================================================
// グローバル変数
//=============================================================================
POINT g_MousePos;

//=============================================================================
// メイン処理
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	WNDCLASSEX wcex =
	{
		sizeof( WNDCLASSEX ), //メモリサイズを指定
		CS_CLASSDC, //ウインドウのスタイルを設定
		WndProc, //ウインドウプロシージャのアドレスを指定
		0,
		0,
		hInstance, //WinMainのインスタンハンドルを指定
		NULL, //使用するアイコンを指定
		LoadCursor( NULL, IDC_ARROW ), //マウスカーソルを指定
		( HBRUSH )( COLOR_WINDOW + 1 ), //クライアント領域の背景色を設定
		NULL, //メニューの設定
		CLASS_NAME.c_str(), //ウインドウクラスの名前
		NULL, //小さいアイコンが設定された場合の情報
	};
	HWND hWnd; //ウインドウハンドル
	MSG msg; //メッセージ

	RegisterClassEx( &wcex ); //ウインドウクラスの登録

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false  );

	hWnd = CreateWindowEx( 0,
						   CLASS_NAME.c_str(), //ウインドウクラスの名前
						   "ReflectBullet", //ウインドウの名前
						   WS_OVERLAPPEDWINDOW, //ウインドウのスタイル
						   CW_USEDEFAULT, //ウインドウの左上X座標
						   CW_USEDEFAULT, //ウインドウの左上Y座標
						   rect.right - rect.left, //幅
						   rect.bottom - rect.top, //高さ
						   NULL, //親ウインドウのハンドル
						   NULL, //メニューハンドルまたは子ウインドウID
						   hInstance, //WinMainのインスタンハンドルを指定
						   NULL ); //ウインドウ作成データ

	//ウインドウの表示
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	if( FAILED( CManager::GetInstance()->Init( hInstance, hWnd, TRUE ) ) )
	{
		return -1;
	}

	timeBeginPeriod( 1 );

	while( 1 )
	{
		//Windowsの処理
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )
		{
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		//DirectXの処理
		else
		{
			GetCursorPos(&g_MousePos); //マウスの座標の取得
			ScreenToClient(hWnd, &g_MousePos); //マウスの座標をクライアント領域に変換
			
			//FPSの計測
			CFpsManager::GetInstance()->FpsCounter();
		}
	}

	UnregisterClass( CLASS_NAME.c_str(), wcex.hInstance );
	timeEndPeriod( 1 );

	CManager::GetInstance()->Uninit( );

	return( int )msg.wParam;
}
//=============================================================================
// Windowsの処理
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	int nID;
	static HWND hWndButton000;
	static HWND hWndEdit000;
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	HDC hDC; //デバイスコンテキストのハンドル
	PAINTSTRUCT ps; //クライアント領域を描画する際に必要

	switch( uMsg )
	{
		case WM_DESTROY: //ウインドウが破棄された
			PostQuitMessage( 0 );
		break;

		case WM_KEYDOWN: //キーが押された
			switch( wParam )
			{
				case VK_ESCAPE:
					nID = MessageBox( hWnd, "終了します", "終了してもよろしいですか？", MB_YESNO + MB_ICONQUESTION );
					if( nID == IDYES )
					{
						DestroyWindow( hWnd ); //ウインドウを破棄する
					}
				break;
			}
		break;

		case WM_PAINT: //描画する
			hDC = BeginPaint( hWnd, &ps ); //描画開始

			EndPaint( hWnd, &ps ); //描画終了
		break;

		case WM_CREATE:

		break;

		case WM_LBUTTONDOWN:
			SetFocus( hWnd ); //フォーカスを合わせる
		break;

		case WM_COMMAND:
		{
			int meunID = LOWORD(wParam);

			/*switch (meunID)
			{
				default:

					break;
			}
			break;*/
		}
		case WM_TIMER: //タイマーの発生

		break;

		default :

		break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//=============================================================================
// マウス座標の取得
//=============================================================================
POINT GetMousePos(void)
{
	return g_MousePos;
}