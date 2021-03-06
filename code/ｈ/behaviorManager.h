//=============================================================================
// 行動管理クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CBehavior;

//=============================================================================
// クラスの定義
//=============================================================================
class CBehaviorManager
{
public:
	//インスタンスを返す
	static CBehaviorManager* GetInstance() { return Instance == NULL ? Instance = new CBehaviorManager() : Instance; };

	//基本的な関数の宣言
	//=============================================================================
	void UninitAll(void);
	void UpdateAll(void);
	void SetBehavior(CBehavior* Behavior) { m_List.push_back(Behavior); }
	void Release(CBehavior* Behavior);

	//設定・取得関数
	//=============================================================================
	list<CBehavior*> GetList(void) { return m_List; }	//指定したリストの取得

private:
	static  CBehaviorManager* Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	//=============================================================================
	CBehaviorManager() {}
	~CBehaviorManager() {}

	//解放用リスト
	//=============================================================================
	void ReleaseList(void);		//behavior

	//変数
	//=============================================================================
	list<CBehavior*> m_List;		//リスト構造
	list<CBehavior*> m_ReleaseList;	//解放用リスト
};