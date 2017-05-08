//=============================================================================
// デバック表示
//=============================================================================
#pragma once

//=============================================================================
// クラスの定義
//=============================================================================
class CDebugProc
{
public:
	//インスタンスを返す
	static CDebugProc* GetInstance() { return Instance == NULL ? Instance = new CDebugProc() : Instance; };

	void Init(void);
	void Uninit(void);
	void Draw(void);
	void PrintDebugProc(string str, ...);

private:
	static  CDebugProc* Instance;	//インスタンス

	CDebugProc();
	~CDebugProc();

	LPD3DXFONT m_pFont; //フォントへのポインタ
	string  m_aStrDebug;

};