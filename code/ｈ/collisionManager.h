//=============================================================================
// 当たり判定管理クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CCollision;

//=============================================================================
// クラスの定義
//=============================================================================
class CCollisionManager
{
public:
	//インスタンスを返す
	static CCollisionManager* GetInstance() { return Instance == NULL ? Instance = new CCollisionManager() : Instance; };

	//基本関数
	//=============================================================================
	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);
	void SetCollision(CCollision* Collision) { m_List.push_back(Collision); }
	void Release(CCollision* Collision);

	//設定・取得関数
	//=============================================================================
	list<CCollision*> GetList(void) { return m_List; }	//指定したリストの取得

private:
	static  CCollisionManager* Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	//=============================================================================
	CCollisionManager();
	~CCollisionManager();

	//解放用リスト
	//=============================================================================
	void ReleaseList(void);		//collision

	//変数
	//=============================================================================
	list<CCollision*> m_List;				//リスト構造
	list<CCollision*> m_ReleaseList;		//解放用リスト
};
