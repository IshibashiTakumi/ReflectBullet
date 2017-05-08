//=============================================================================
// FPS�̊Ǘ�
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "fpsManager.h"
#include "manager.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CFpsManager* CFpsManager::Instance = NULL;	//�C���X�^���X������

//=============================================================================
// �N���X�̐���
//=============================================================================
CFpsManager::CFpsManager()
{
	m_Fps = 0;
	m_FrameCount = m_CurrentTime = 0;
	m_ExecLastTime = m_FPSLastTime = timeGetTime();
	m_FrameTime = 0;
	m_StartTime = std::chrono::system_clock::now(); // �v���J�n����
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CFpsManager::~CFpsManager()
{

}

//=============================================================================
// FPS�̌v��
//=============================================================================
void CFpsManager::FpsCounter(void)
{
	m_CurrentTime = timeGetTime();

	if ((m_CurrentTime - m_FPSLastTime) >= 500)
	{
		m_Fps = (m_FrameCount * 1000) / (m_CurrentTime - m_FPSLastTime);
		m_FPSLastTime = m_CurrentTime;
		m_FrameCount = 0;
	}
	if ((m_CurrentTime - m_ExecLastTime) >= (1000 / 60))
	{
		m_ExecLastTime = m_CurrentTime;

		CManager::GetInstance()->Update();
		CManager::GetInstance()->Draw();
		FrameTime();

		m_FrameCount++;
	}
}

//=============================================================================
// DeltaTime�̌v��
//=============================================================================
void CFpsManager::FrameTime(void)
{
	m_EndTime = std::chrono::system_clock::now(); // �v���J�n����

	m_FrameTime = (double)std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime - m_StartTime).count(); //�����ɗv�������Ԃ��~���b�ɕϊ�
	m_FrameTime *= 0.000001f;

	m_StartTime = std::chrono::system_clock::now(); // �v���J�n����
}