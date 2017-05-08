//=============================================================================
// �}�E�X�̓���
//=============================================================================
#pragma once

//=============================================================================
// �}�N����`
//=============================================================================
#define MAUSE_BUTTON_MAX ( 8 ) //�}�E�X�{�^���̍ő吔

//=============================================================================
// �\����
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
// �O���錾
//=============================================================================

//=============================================================================
// �N���X�̒�`
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
	LPDIRECTINPUTDEVICE8 m_DevMouse; //���̓f�o�C�X(�}�E�X)�ւ̃|�C���^

	D3DXVECTOR2 m_PosA;						//�}�E�X�̐�΍��W
	D3DXVECTOR3 m_PosR;						//�}�E�X�̑��΍��W
	D3DXVECTOR3 m_PosW;						//�}�E�X�̃��[���h���W
	BYTE m_State[MAUSE_BUTTON_MAX];			//�}�E�X�̓��͏�񃏁[�N
	BYTE m_Trigger[MAUSE_BUTTON_MAX];		//�g���K�[���
	BYTE m_Release[MAUSE_BUTTON_MAX];		//�����[�X���
};