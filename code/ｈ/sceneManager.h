//=============================================================================
// 描画管理クラス
//=============================================================================
#pragma once

//=============================================================================
// 構造体
//=============================================================================
typedef enum
{
	PRIORITY_3D = 0,
	PRIORITY_2D,
	PRIORITY_MAX,
}PRIORITY;

//=============================================================================
// 前方宣言
//=============================================================================
class CScene;

//=============================================================================
// クラスの定義
//=============================================================================
class CSceneManager
{
public:
	//インスタンスを返す
	static CSceneManager* GetInstance() { return Instance == NULL ? Instance = new CSceneManager() : Instance; };

	//基本的な関数の宣言
	//=============================================================================
	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);
	void PriorityDraw(PRIORITY Priority, int pass = 0);
	void SetObject(PRIORITY Priority, CScene* Scene) { m_List[Priority].push_back(Scene); }
	void Release(CScene* Scene);

	//設定・取得関数
	//=============================================================================
	list<CScene*> GetList(PRIORITY Priority) { return m_List[Priority]; }	//指定したリストの取得

private:
	static  CSceneManager* Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	//=============================================================================
	CSceneManager();
	~CSceneManager();

	//解放用リスト
	//=============================================================================
	void ReleaseList(void);		//scene
	friend static PRIORITY GetPriority(CScene* Scene);

	//変数
	//=============================================================================
	list<CScene*> m_List[PRIORITY_MAX];	//リスト構造
	list<CScene*> m_ReleaseList;	//解放用リスト
};