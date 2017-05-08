//=============================================================================
// モード管理クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CMode;

//=============================================================================
// クラスの定義
//=============================================================================
class CModeManager
{
public:
	//インスタンスを返す
	static CModeManager* GetInstance() { return Instance == NULL ? Instance = new CModeManager() : Instance; };

	//基本的な関数の宣言
	//=============================================================================
	void Uninit(void);
	void Update(void);
	void Draw(void);


	void SetMode(CMode* Mode);
	CMode* GetMode() { return m_Mode; }

private:
	static  CModeManager* Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	//=============================================================================
	CModeManager() { m_Mode = NULL; }
	~CModeManager() {}

	//変数
	//=============================================================================
	CMode* m_Mode;			//リスト構造
};