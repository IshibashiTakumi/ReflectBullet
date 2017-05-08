//=============================================================================
// Object基底クラス
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "transform.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene;
class CCollision;
class CBehavior;
class CPhysics;
class CPointLight;

//=============================================================================
// クラスの定義
//=============================================================================
class CObject
{
public:
	//コンストラクタ・デストラクタ
	//=============================================================================
	CObject(const string& name, const string& tag, CTransform* Transform);
	~CObject();

	//基本
	//=============================================================================
	void Init(void) {};		//初期化
	void Uninit(void);		//解放
	void Update(void) {};	//更新
	void Draw(void) {};	//描画

	//破棄
	//=============================================================================
	virtual void Release(void);		//単体
	virtual void Destroy(void);		//全体

	//衝突
	//=============================================================================
	void CollisionTrigger(CObject* Object);		//衝突時
	void CollisionEnter(CObject* Object);		//衝突継続時
	void CollisionRelease(CObject* Object);		//衝突終了時

	//変数
	//=============================================================================
	CTransform* m_Transform;

	//リスト取得
	//=============================================================================
	list<CScene*>		GetSceneList(void) { return m_SceneList; }				//シーン
	list<CCollision*>	GetCollisionList(void) { return m_CollisionList; }		//コリジョン
	list<CBehavior*>	GetBehaviorList(void) { return m_BehaviorList; }		//行動
	list<CPhysics*>		GetPhysicsList(void) { return m_PhysicsList; }			//物理演算
	string GetName(void) { return m_Name; }										//名前の取得								
	string GetTag(void) { return m_Tag; }										//タグの取得

	//生成関数
	//=============================================================================
	template<class Pointer>
	static void Search(CObject* Object, Pointer* pointer)
	{
		std::cout << pointer << std::endl;
		Object->Attach(pointer);
		//SetObject(pointer, Object);
		pointer->Transformation();
	}
	template<class First, class... Argument>
	static void Search(CObject* Object, First* first, Argument* ...argument)
	{
		Search(Object, first);
		Search(Object, argument...);
	}
	template<class First, class ...Argument>
	static CObject* Create(const string& name, const string& tag, CTransform* Transform, First* first, Argument* ...argument)
	{
		CObject* Object = new CObject(name, tag, Transform);
		Search(Object, first, argument...);
		return Object;
	}

	//リスト追加関数
	//=============================================================================
	void Attach(CScene* Scene);
	void Attach(CCollision* Collision);
	void Attach(CBehavior* Behavior);
	void Attach(CPhysics* Physics);
	void Attach(CPointLight* PointLight);

	void Detach(CScene* Scene);
	void Detach(CCollision* Collision);
	void Detach(CBehavior* Behavior);
	void Detach(CPhysics* Physics);
	void Detach(CPointLight* PointLight);

protected:
	//リストポインタ
	//=============================================================================
	list<CScene*> m_SceneList;			//シーン
	list<CCollision*> m_CollisionList;	//コリジョン
	list<CBehavior*> m_BehaviorList;	//行動
	list<CPhysics*> m_PhysicsList;		//物理演算
	list<CPointLight*> m_PointLight;	//点光源

private:
	//変数
	//=============================================================================
	string m_Name;	//名前
	string m_Tag;	//タグ

	//関数
	//=============================================================================
	template<class Class, class List>
	static void DetachList(List * Object, list<List*> List);
};
