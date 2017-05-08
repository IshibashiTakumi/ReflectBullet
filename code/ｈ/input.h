//=============================================================================
// 入力の基底クラス
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "inputKeyboard.h"
#include "inputMouse.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CInput
{
	public:
		//インスタンスを返す
		static CInput* GetInstance() { return Instance == NULL ? Instance = new CInput() : Instance; };

		HRESULT Init ( HINSTANCE hInstance, HWND hWnd );
		void Uninit ( void );
		void Update ( void );

		CInputKeyboard* GetKeyboard(void) { return m_Keyboard; }
		CInputMouse* GetMouse(void) { return m_Mouse; }

private:
	static  CInput* Instance;	//インスタンス

	CInput();
	~CInput();

	LPDIRECTINPUT8 m_Input; //DirectInputオブジェクトへのポインタ
	CInputKeyboard* m_Keyboard;
	CInputMouse* m_Mouse;

	template<class Class, class ...Argument>
	static Class* Create(LPDIRECTINPUT8* Input, Argument... argument)
	{
		Class* _Class = new Class();
		_Class->Init(Input, argument...);
		return _Class;
	}
};