//=============================================================================
// ���͂̊��N���X
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "inputKeyboard.h"
#include "inputMouse.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CInput
{
	public:
		//�C���X�^���X��Ԃ�
		static CInput* GetInstance() { return Instance == NULL ? Instance = new CInput() : Instance; };

		HRESULT Init ( HINSTANCE hInstance, HWND hWnd );
		void Uninit ( void );
		void Update ( void );

		CInputKeyboard* GetKeyboard(void) { return m_Keyboard; }
		CInputMouse* GetMouse(void) { return m_Mouse; }

private:
	static  CInput* Instance;	//�C���X�^���X

	CInput();
	~CInput();

	LPDIRECTINPUT8 m_Input; //DirectInput�I�u�W�F�N�g�ւ̃|�C���^
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