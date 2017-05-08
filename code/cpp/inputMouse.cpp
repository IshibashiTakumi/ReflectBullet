//=============================================================================
// マウスの入力
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "inputMouse.h"
#include "renderer.h"
#include "camera.h"
#include "cameraManager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DIDEVICE_BUFFERSIZE	100						// デバイスに設定するバッファ・サイズ

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// クラスの生成
//=============================================================================
CInputMouse::CInputMouse()
{
	m_DevMouse = NULL;		//入力デバイス(マウス)へのポインタの初期化

	//マウスの入力情報の初期化
	for (int count = 0; count < MAUSE_BUTTON_MAX; count++)
	{
		m_State[count] = 0;
		m_Trigger[count] = 0;
		m_Release[count] = 0;
	}
}

//=============================================================================
// クラスの破棄
//=============================================================================
CInputMouse::~CInputMouse()
{

}

//=============================================================================
// マウスの初期化
//=============================================================================
HRESULT CInputMouse::Init(LPDIRECTINPUT8* Input, HWND hWnd )
{
	if (FAILED((*Input)->CreateDevice(GUID_SysMouse, &m_DevMouse, NULL))) //マウスのデバイスオブジェクトのを作成
	{
		return E_FAIL;
	}
	if (FAILED(m_DevMouse->SetDataFormat(&c_dfDIMouse2))) //データ形式を設定
	{
		return E_FAIL;
	}
	if (FAILED(FAILED(m_DevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))	//モードを設定（フォアグラウンド＆非排他モード）
	{
		return E_FAIL;
	}

	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//	diprop.dwData		= DIPROPAXISMODE_ABS;	// 絶対値モードの場合
	if (FAILED(m_DevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// バッファリング・データを取得するため、バッファ・サイズを設定
	diprop.dwData = DIDEVICE_BUFFERSIZE;
	if (FAILED(m_DevMouse->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph)))
	{
		return E_FAIL;
	}

	m_DevMouse->Acquire(); //アクセス権を取得

	return S_OK;
}

//=============================================================================
// マウスの解放
//=============================================================================
void CInputMouse::Uninit( void )
{
	ResourceRelease(m_DevMouse);
}

//=============================================================================
// マウスの更新
//=============================================================================
void CInputMouse::Update( void )
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得

	// デバイスの直接データを取得する
	DIMOUSESTATE2 dims;
	if (SUCCEEDED(m_DevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &dims)))
	{
		m_PosR = D3DXVECTOR3(dims.lX, dims.lY, dims.lZ);	//相対座標の取得
		m_PosA = D3DXVECTOR2(GetMousePos().x, GetMousePos().y);	//絶対座標の取得

		CCamera *Camera = CCameraManager::GetInstance()->GetCamera();
		m_PosW = Camera->GetPosWorld();

		for (int count = 0; count < MAUSE_BUTTON_MAX; count++)
		{
			//トリガーキーの処理
			m_Trigger[count] = (m_State[count] | dims.rgbButtons[count]) ^ m_State[count];

			//リリースキーの処理
			m_Release[count] = (m_State[count] | dims.rgbButtons[count]) ^ dims.rgbButtons[count];

			//プレスキーの処理
			m_State[count] = dims.rgbButtons[count];
		}
	}
	else
	{
		m_DevMouse->Acquire();
	}
}

//=============================================================================
// 相対座標の取得
//=============================================================================
D3DXVECTOR3 CInputMouse::GetPosR( void )
{
	return m_PosR;
}

//=============================================================================
// 絶対座標の取得
//=============================================================================
D3DXVECTOR2 CInputMouse::GetPosA(void)
{
	return m_PosA;
}

//=============================================================================
// ワールド座標の取得
//=============================================================================
D3DXVECTOR3 CInputMouse::GetPosW(void)
{
	return m_PosW;
}

//=============================================================================
// プレスの取得
//=============================================================================
bool CInputMouse::GetPress( int nBottun )
{
	return ( m_State[ nBottun ] & 0x80 )? true : false;
}

//=============================================================================
// トリガーの取得
//=============================================================================
bool CInputMouse::GetTrigger( int nBottun )
{
	return ( m_Trigger[ nBottun ] & 0x80 )? true : false;
}

//=============================================================================
// リリースキーの取得
//=============================================================================
bool CInputMouse::GetRelease( int nBottun )
{
	return ( m_Release[ nBottun ] & 0x80 )? true : false;
}