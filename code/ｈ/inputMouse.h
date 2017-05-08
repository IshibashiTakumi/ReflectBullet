//=============================================================================
// マウスの入力
//=============================================================================
#pragma once

//=============================================================================
// マクロ定義
//=============================================================================
#define MAUSE_BUTTON_MAX ( 8 ) //マウスボタンの最大数

//=============================================================================
// 構造体
//=============================================================================
typedef enum
{
	MOUSE_BUTTON0 = 0,
	MOUSE_BUTTON1,
	MOUSE_BUTTON2,
	MOUSE_BUTTON3,
	MOUSE_BUTTON4,
	MOUSE_BUTTON5,
	MOUSE_BUTTON6,
	MOUSE_BUTTON7,
}MOUSE_BUTTON;

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
class CInputMouse
{
	public:

		CInputMouse();
		~CInputMouse();

		HRESULT Init (LPDIRECTINPUT8* Input, HWND hWnd );
		void Uninit ( void );
		void Update ( void );

		D3DXVECTOR3 GetPosR( void );
		D3DXVECTOR2 GetPosA( void );
		D3DXVECTOR3 GetPosW(void);
		bool GetPress( int nMouseBottun );
		bool GetTrigger( int nMouseBottun );
		bool GetRelease( int nMouseBottun );

private:
	LPDIRECTINPUTDEVICE8 m_DevMouse; //入力デバイス(マウス)へのポインタ

	D3DXVECTOR2 m_PosA;						//マウスの絶対座標
	D3DXVECTOR3 m_PosR;						//マウスの相対座標
	D3DXVECTOR3 m_PosW;						//マウスのワールド座標
	BYTE m_State[MAUSE_BUTTON_MAX];			//マウスの入力情報ワーク
	BYTE m_Trigger[MAUSE_BUTTON_MAX];		//トリガー情報
	BYTE m_Release[MAUSE_BUTTON_MAX];		//リリース情報
};