//=============================================================================
// オブジェクト管理クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CObject;

//=============================================================================
// クラスの定義
//=============================================================================
class CObjectManager
{
public:
	//インスタンスを返す
	static CObjectManager* GetInstance() { return Instance == NULL ? Instance = new CObjectManager() : Instance; };

	//基本的な関数の宣言
	//=============================================================================
	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);
	void SetObject(CObject* Object) { m_List.push_back(Object); }
	void Release(CObject* Object);
	CObject* FindName(const string& Name);
	list<CObject*> FindTag(const string& Tag);

	//設定・取得関数
	//=============================================================================
	list<CObject*> GetList(void) { return m_List; }	//指定したリストの取得

private:
	static  CObjectManager* Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	//=============================================================================
	CObjectManager() {}
	~CObjectManager() {}

	//解放用リスト
	//=============================================================================
	void ReleaseList(void);		//object

	//変数
	//=============================================================================
	list<CObject*> m_List;			//リスト構造
	list<CObject*> m_ReleaseList;	//解放用リスト
};