//=============================================================================
// �Q�[���p�b�h���̓N���X
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "XInput.h"
#pragma comment(lib,"XInput.lib")

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CONTROLLERS ( 4 )			//	�R���g���[���[�̍ő吔

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CJoyStick
{
public:
	//�C���X�^���X��Ԃ�
	static CJoyStick* GetInstance() { return Instance == NULL ? Instance = new CJoyStick() : Instance; };

	void Init(void);
	void Uninit(void);
	void Update(void);

	//	JoyStick�̓��͂��󂯎��֐�
	bool Press(WORD nKey);
	bool Trigger(WORD nKey);
	bool Release(WORD nKey);
	void Vibration(int LeftMotorSpeed, int RightMotorSpeed);
	WORD GetUse(void) { return UseController; }

private:
	static CJoyStick* Instance;	//�C���X�^���X

	CJoyStick() {};
	~CJoyStick() {};

	XINPUT_STATE m_Press[MAX_CONTROLLERS];		//�v���X���
	XINPUT_STATE m_Trigger[MAX_CONTROLLERS];	//�g���K�[���
	XINPUT_STATE m_Release[MAX_CONTROLLERS];	//�����[�X���
	WORD UseController;							//�g�p���Ă���R���g���[���[
};