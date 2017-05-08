//=============================================================================
// ���C��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "fpsManager.h"

//=============================================================================
// �֐��̃v���g�^�C�v�錾
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
POINT g_MousePos;

//=============================================================================
// ���C������
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	WNDCLASSEX wcex =
	{
		sizeof( WNDCLASSEX ), //�������T�C�Y���w��
		CS_CLASSDC, //�E�C���h�E�̃X�^�C����ݒ�
		WndProc, //�E�C���h�E�v���V�[�W���̃A�h���X���w��
		0,
		0,
		hInstance, //WinMain�̃C���X�^���n���h�����w��
		NULL, //�g�p����A�C�R�����w��
		LoadCursor( NULL, IDC_ARROW ), //�}�E�X�J�[�\�����w��
		( HBRUSH )( COLOR_WINDOW + 1 ), //�N���C�A���g�̈�̔w�i�F��ݒ�
		NULL, //���j���[�̐ݒ�
		CLASS_NAME.c_str(), //�E�C���h�E�N���X�̖��O
		NULL, //�������A�C�R�����ݒ肳�ꂽ�ꍇ�̏��
	};
	HWND hWnd; //�E�C���h�E�n���h��
	MSG msg; //���b�Z�[�W

	RegisterClassEx( &wcex ); //�E�C���h�E�N���X�̓o�^

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false  );

	hWnd = CreateWindowEx( 0,
						   CLASS_NAME.c_str(), //�E�C���h�E�N���X�̖��O
						   "ReflectBullet", //�E�C���h�E�̖��O
						   WS_OVERLAPPEDWINDOW, //�E�C���h�E�̃X�^�C��
						   CW_USEDEFAULT, //�E�C���h�E�̍���X���W
						   CW_USEDEFAULT, //�E�C���h�E�̍���Y���W
						   rect.right - rect.left, //��
						   rect.bottom - rect.top, //����
						   NULL, //�e�E�C���h�E�̃n���h��
						   NULL, //���j���[�n���h���܂��͎q�E�C���h�EID
						   hInstance, //WinMain�̃C���X�^���n���h�����w��
						   NULL ); //�E�C���h�E�쐬�f�[�^

	//�E�C���h�E�̕\��
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	if( FAILED( CManager::GetInstance()->Init( hInstance, hWnd, TRUE ) ) )
	{
		return -1;
	}

	timeBeginPeriod( 1 );

	while( 1 )
	{
		//Windows�̏���
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
		//DirectX�̏���
		else
		{
			GetCursorPos(&g_MousePos); //�}�E�X�̍��W�̎擾
			ScreenToClient(hWnd, &g_MousePos); //�}�E�X�̍��W���N���C�A���g�̈�ɕϊ�
			
			//FPS�̌v��
			CFpsManager::GetInstance()->FpsCounter();
		}
	}

	UnregisterClass( CLASS_NAME.c_str(), wcex.hInstance );
	timeEndPeriod( 1 );

	CManager::GetInstance()->Uninit( );

	return( int )msg.wParam;
}
//=============================================================================
// Windows�̏���
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	int nID;
	static HWND hWndButton000;
	static HWND hWndEdit000;
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	HDC hDC; //�f�o�C�X�R���e�L�X�g�̃n���h��
	PAINTSTRUCT ps; //�N���C�A���g�̈��`�悷��ۂɕK�v

	switch( uMsg )
	{
		case WM_DESTROY: //�E�C���h�E���j�����ꂽ
			PostQuitMessage( 0 );
		break;

		case WM_KEYDOWN: //�L�[�������ꂽ
			switch( wParam )
			{
				case VK_ESCAPE:
					nID = MessageBox( hWnd, "�I�����܂�", "�I�����Ă���낵���ł����H", MB_YESNO + MB_ICONQUESTION );
					if( nID == IDYES )
					{
						DestroyWindow( hWnd ); //�E�C���h�E��j������
					}
				break;
			}
		break;

		case WM_PAINT: //�`�悷��
			hDC = BeginPaint( hWnd, &ps ); //�`��J�n

			EndPaint( hWnd, &ps ); //�`��I��
		break;

		case WM_CREATE:

		break;

		case WM_LBUTTONDOWN:
			SetFocus( hWnd ); //�t�H�[�J�X�����킹��
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
		case WM_TIMER: //�^�C�}�[�̔���

		break;

		default :

		break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//=============================================================================
// �}�E�X���W�̎擾
//=============================================================================
POINT GetMousePos(void)
{
	return g_MousePos;
}