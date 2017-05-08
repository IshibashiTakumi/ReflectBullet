//=============================================================================
// FPSの管理
//=============================================================================
#pragma once

//=============================================================================
// クラスの定義
//=============================================================================
class CFpsManager
{
public:

	//インスタンスを返す
	//=============================================================================
	static CFpsManager* GetInstance() { return Instance == NULL ? Instance = new CFpsManager() : Instance; };

	//関数宣言
	//=============================================================================
	void FpsCounter(void);
	void FrameTime(void);

	//Set・Get関数
	float GetFrameTime(void) { return m_FrameTime; }
	int GetFps(void) { return m_Fps; }

private:
	// インスタンス
	//=============================================================================
	static  CFpsManager* Instance;

	//コンストラクタ・デストラクタ
	//=============================================================================
	CFpsManager();
	~CFpsManager();

	//変数
	//=============================================================================
	unsigned int m_Fps;			
	DWORD m_FrameCount;
	DWORD m_CurrentTime;
	DWORD m_ExecLastTime;
	DWORD m_FPSLastTime;

	float m_FrameTime;	//前フレーム間の時間
	std::chrono::system_clock::time_point m_StartTime;	//計測開始時間
	std::chrono::system_clock::time_point m_EndTime;	//計測終了時間
};