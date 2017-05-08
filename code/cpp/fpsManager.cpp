//=============================================================================
// FPSの管理
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "fpsManager.h"
#include "manager.h"

//=============================================================================
// グローバル変数
//=============================================================================
CFpsManager* CFpsManager::Instance = NULL;	//インスタンス初期化

//=============================================================================
// クラスの生成
//=============================================================================
CFpsManager::CFpsManager()
{
	m_Fps = 0;
	m_FrameCount = m_CurrentTime = 0;
	m_ExecLastTime = m_FPSLastTime = timeGetTime();
	m_FrameTime = 0;
	m_StartTime = std::chrono::system_clock::now(); // 計測開始時間
}

//=============================================================================
// クラスの破棄
//=============================================================================
CFpsManager::~CFpsManager()
{

}

//=============================================================================
// FPSの計測
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
// DeltaTimeの計測
//=============================================================================
void CFpsManager::FrameTime(void)
{
	m_EndTime = std::chrono::system_clock::now(); // 計測開始時間

	m_FrameTime = (double)std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime - m_StartTime).count(); //処理に要した時間をミリ秒に変換
	m_FrameTime *= 0.000001f;

	m_StartTime = std::chrono::system_clock::now(); // 計測開始時間
}