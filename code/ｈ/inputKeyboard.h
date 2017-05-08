//=============================================================================
// キーボードの入力
//=============================================================================
#pragma once

//=============================================================================
// マクロ定義
//=============================================================================
#define REPEAT_INTERVAL ( 40 ) //リピートキーの間隔

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
class CInputKeyboard
{
public:

	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(LPDIRECTINPUT8* Input, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:

	LPDIRECTINPUTDEVICE8 m_DevKeyboard; //入力デバイス(キーボード)へのポインタ
	BYTE m_State[256]; //キーボードの入力情報ワーク
	BYTE m_Trigger[256]; //トリガー情報
	BYTE m_Release[256]; //リリース情報
	BYTE m_Repeat[256]; //キーリピート情報
	unsigned int m_RepeatCount[256]; //キーリピートカウント
};