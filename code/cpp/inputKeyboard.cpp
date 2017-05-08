//=============================================================================
// �L�[�{�[�h�̓���
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "inputKeyboard.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	m_DevKeyboard = NULL;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^�̏�����

	//�L�[�{�[�h�̓��͏��̏�����
	for (int count = 0; count < 256; count++)
	{
		m_State[count] = 0;
		m_Trigger[count] = 0;
		m_Release[count] = 0;
		m_Repeat[count] = 0;
	}
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputKeyboard::Init(LPDIRECTINPUT8* Input, HWND hWnd)
{
	if (FAILED((*Input)->CreateDevice(GUID_SysKeyboard, &m_DevKeyboard, NULL))) return E_FAIL;
	if (FAILED(m_DevKeyboard->SetDataFormat(&c_dfDIKeyboard))) return E_FAIL;									//�f�[�^�t�H�[�}�b�g�̐ݒ� 
	if (FAILED(m_DevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) return E_FAIL;	//�������[�h�̐ݒ� 
	m_DevKeyboard->Acquire(); //�A�N�Z�X�����擾
	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̉��
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	ResourceRelease(m_DevKeyboard);
}
//=============================================================================
// ���͂̍X�V
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[256];

	if (SUCCEEDED(m_DevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int count = 0; count < 256; count++)
		{
			//�g���K�[�L�[�̏���
			m_Trigger[count] = (m_State[count] | aKeyState[count]) ^ m_State[count];

			//�����[�X�L�[�̏���
			m_Release[count] = (m_State[count] | aKeyState[count]) ^ aKeyState[count];

			//���s�[�g�L�[�̏���
			if (m_RepeatCount[count] <= REPEAT_INTERVAL)
			{
				m_Repeat[count] = (m_State[count] | aKeyState[count]) ^ m_State[count];
				m_RepeatCount[count]++;
			}
			else m_Repeat[count] = m_State[count];
			if (m_Release[count] == m_State[count]) m_RepeatCount[count] = 0;

			//�v���X�L�[�̏���
			m_State[count] = aKeyState[count];
		}
	}
	else m_DevKeyboard->Acquire();
}

//=============================================================================
// �v���X�L�[�̎擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_State[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �g���K�[�L�[�̎擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_Trigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �����[�X�L�[�̎擾
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_Release[nKey] & 0x80) ? true : false;
}

//=============================================================================
// ���s�[�g�L�[�̎擾
//=============================================================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_Repeat[nKey] & 0x80) ? true : false;
}