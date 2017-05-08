//=============================================================================
// キーボードの入力
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "inputKeyboard.h"

//=============================================================================
// クラスの生成
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	m_DevKeyboard = NULL;	//入力デバイス(キーボード)へのポインタの初期化

	//キーボードの入力情報の初期化
	for (int count = 0; count < 256; count++)
	{
		m_State[count] = 0;
		m_Trigger[count] = 0;
		m_Release[count] = 0;
		m_Repeat[count] = 0;
	}
}

//=============================================================================
// クラスの破棄
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT CInputKeyboard::Init(LPDIRECTINPUT8* Input, HWND hWnd)
{
	if (FAILED((*Input)->CreateDevice(GUID_SysKeyboard, &m_DevKeyboard, NULL))) return E_FAIL;
	if (FAILED(m_DevKeyboard->SetDataFormat(&c_dfDIKeyboard))) return E_FAIL;									//データフォーマットの設定 
	if (FAILED(m_DevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) return E_FAIL;	//協調モードの設定 
	m_DevKeyboard->Acquire(); //アクセス権を取得
	return S_OK;
}

//=============================================================================
// キーボードの解放
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	ResourceRelease(m_DevKeyboard);
}
//=============================================================================
// 入力の更新
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[256];

	if (SUCCEEDED(m_DevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int count = 0; count < 256; count++)
		{
			//トリガーキーの処理
			m_Trigger[count] = (m_State[count] | aKeyState[count]) ^ m_State[count];

			//リリースキーの処理
			m_Release[count] = (m_State[count] | aKeyState[count]) ^ aKeyState[count];

			//リピートキーの処理
			if (m_RepeatCount[count] <= REPEAT_INTERVAL)
			{
				m_Repeat[count] = (m_State[count] | aKeyState[count]) ^ m_State[count];
				m_RepeatCount[count]++;
			}
			else m_Repeat[count] = m_State[count];
			if (m_Release[count] == m_State[count]) m_RepeatCount[count] = 0;

			//プレスキーの処理
			m_State[count] = aKeyState[count];
		}
	}
	else m_DevKeyboard->Acquire();
}

//=============================================================================
// プレスキーの取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_State[nKey] & 0x80) ? true : false;
}

//=============================================================================
// トリガーキーの取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_Trigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// リリースキーの取得
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_Release[nKey] & 0x80) ? true : false;
}

//=============================================================================
// リピートキーの取得
//=============================================================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_Repeat[nKey] & 0x80) ? true : false;
}