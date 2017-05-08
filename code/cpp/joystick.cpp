//=============================================================================
// �Q�[���p�b�h���̓N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "joyStick.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CJoyStick* CJoyStick::Instance = NULL;	//�C���X�^���X

//=============================================================================
// ������
//=============================================================================
void CJoyStick::Init(void)
{
	//	��Ɨp�ϐ�
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	UseController = 0;
	for (DWORD count = 0; count < MAX_CONTROLLERS; count++)
	{
		dwResult = XInputGetState(count, &state);

		//	�f���@�C�X�����邩�ǂ���
		if (dwResult == ERROR_SUCCESS)
		{
			UseController = count;
			break;
		}
	}

	for (DWORD count = 0; count < MAX_CONTROLLERS; count++)
	{
		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(count, &state);

		//	�f���@�C�X�����邩�ǂ���
		if (dwResult == ERROR_SUCCESS)
		{// Controller is connected

			//	Press���̏�����
			m_Press[count].Gamepad.bLeftTrigger = NULL;
			m_Press[count].Gamepad.bRightTrigger = NULL;
			m_Press[count].Gamepad.sThumbLX = NULL;
			m_Press[count].Gamepad.sThumbLY = NULL;
			m_Press[count].Gamepad.sThumbRX = NULL;
			m_Press[count].Gamepad.sThumbRY = NULL;
			m_Press[count].Gamepad.wButtons = NULL;

			// Trigger���̏�����
			m_Trigger[count].Gamepad.bLeftTrigger = NULL;
			m_Trigger[count].Gamepad.bRightTrigger = NULL;
			m_Trigger[count].Gamepad.sThumbLX = NULL;
			m_Trigger[count].Gamepad.sThumbLY = NULL;
			m_Trigger[count].Gamepad.sThumbRX = NULL;
			m_Trigger[count].Gamepad.sThumbRY = NULL;
			m_Trigger[count].Gamepad.wButtons = NULL;

			//	Release���̏�����
			m_Release[count].Gamepad.bLeftTrigger = NULL;
			m_Release[count].Gamepad.bRightTrigger = NULL;
			m_Release[count].Gamepad.sThumbLX = NULL;
			m_Release[count].Gamepad.sThumbLY = NULL;
			m_Release[count].Gamepad.sThumbRX = NULL;
			m_Release[count].Gamepad.sThumbRY = NULL;
			m_Release[count].Gamepad.wButtons = NULL;
		}
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CJoyStick::Uninit(void)
{
	
}

//=============================================================================
// �`��
//=============================================================================
void CJoyStick::Update(void)
{
	//	��Ɨp�ϐ�
	DWORD dwResult;
	XINPUT_STATE state;

	for (DWORD count = 0; count < MAX_CONTROLLERS; count++)
	{
		//0�ŏ�����
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		//�f���@�C�X���擾
		dwResult = XInputGetState(count, &state);

		//�f���@�C�X����������
		if (dwResult == ERROR_SUCCESS)
		{
			//Trigger
			m_Trigger[count].Gamepad.wButtons = (m_Press[count].Gamepad.wButtons | state.Gamepad.wButtons) ^ m_Press[count].Gamepad.wButtons;

			//Release
			m_Release[count].Gamepad.wButtons = (m_Press[count].Gamepad.wButtons | state.Gamepad.wButtons) ^ state.Gamepad.wButtons;

			//Pless����
			if (state.Gamepad.sThumbLY <= 0)
			{
				m_Press[count] = state;
			}
			m_Press[count] = state;
		}
	}
}

//=============================================================================
// �v���X�L�[�̎擾
//=============================================================================
bool CJoyStick::Press(WORD nKey)
{
	return (m_Press[UseController].Gamepad.wButtons & nKey) ? true : false;
}


//=============================================================================
// �g���K�[�̎擾
//=============================================================================
bool CJoyStick::Trigger(WORD nKey)
{
	return (m_Trigger[UseController].Gamepad.wButtons & nKey) ? true : false;
}


//=============================================================================
// �����[�X�̎擾
//=============================================================================
bool CJoyStick::Release(WORD nKey)
{
	return (m_Release[UseController].Gamepad.wButtons & nKey) ? true : false;
}

//=============================================================================
// 
//=============================================================================
void CJoyStick::Vibration( int LeftMotorSpeed , int RightMotorSpeed )
{
	XINPUT_VIBRATION pVibration;
	pVibration.wLeftMotorSpeed = LeftMotorSpeed;
	pVibration.wRightMotorSpeed = RightMotorSpeed;
	XInputSetState( 0 , &pVibration );
}