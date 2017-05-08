//=============================================================================
// FPS�̊Ǘ�
//=============================================================================
#pragma once

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CFpsManager
{
public:

	//�C���X�^���X��Ԃ�
	//=============================================================================
	static CFpsManager* GetInstance() { return Instance == NULL ? Instance = new CFpsManager() : Instance; };

	//�֐��錾
	//=============================================================================
	void FpsCounter(void);
	void FrameTime(void);

	//Set�EGet�֐�
	float GetFrameTime(void) { return m_FrameTime; }
	int GetFps(void) { return m_Fps; }

private:
	// �C���X�^���X
	//=============================================================================
	static  CFpsManager* Instance;

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CFpsManager();
	~CFpsManager();

	//�ϐ�
	//=============================================================================
	unsigned int m_Fps;			
	DWORD m_FrameCount;
	DWORD m_CurrentTime;
	DWORD m_ExecLastTime;
	DWORD m_FPSLastTime;

	float m_FrameTime;	//�O�t���[���Ԃ̎���
	std::chrono::system_clock::time_point m_StartTime;	//�v���J�n����
	std::chrono::system_clock::time_point m_EndTime;	//�v���I������
};