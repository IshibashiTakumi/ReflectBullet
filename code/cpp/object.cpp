//=============================================================================
// Object基底クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"
#include "objectManager.h"
#include "scene.h"
#include "sceneManager.h"
#include "behavior.h"
#include "behaviorManager.h"
#include "physics.h"
#include "physicsManager.h"
#include "pointLight.h"
#include "pointLightManager.h"
#include "collision.h"
#include "collisionManager.h"
#include "templateList.h"

//=============================================================================
// クラスの生成
//=============================================================================
CObject::CObject(const string& name, const string& tag, CTransform* Transform)
{
	m_Transform = Transform;
	m_Name = name;
	m_Tag = tag;
	CObjectManager::GetInstance()->SetObject(this);
}

//=============================================================================
// クラスの破棄
//=============================================================================
CObject::~CObject()
{
	delete m_Transform;

	//リストの解放
	//=============================================================================
	m_SceneList.clear();		//シーン
	m_CollisionList.clear();	//コリジョン
	m_BehaviorList.clear();		//行動
	m_PhysicsList.clear();		//物理演算
	m_PointLight.clear();		//点光源
}

//=============================================================================
// オブジェクトの解放
//=============================================================================
void CObject::Uninit(void)
{
	m_SceneList.clear();			
	m_CollisionList.clear();
	m_BehaviorList.clear();
	m_PhysicsList.clear();
	m_PointLight.clear();
	m_Name.clear();
	m_Tag.clear();
}

//=============================================================================
// オブジェクト単体を破棄する
//=============================================================================
void CObject::Release(void)
{
	CObjectManager::GetInstance()->Release(this);
}

//=============================================================================
// オブジェクト内全体を破棄する
//=============================================================================
void CObject::Destroy(void)
{
	CTemplateList::Uninit<CBehaviorManager>(m_BehaviorList);
	CTemplateList::Uninit<CCollisionManager>(m_CollisionList);
	CTemplateList::Uninit<CSceneManager>(m_SceneList);
	CTemplateList::Uninit<CPhysicsManager>(m_PhysicsList);
	CTemplateList::Uninit<CPointLightManager>(m_PointLight);
	CObjectManager::GetInstance()->Release(this);
}

//=============================================================================
// 衝突時オブジェクト内にあるリストに衝突時を知らせる
//=============================================================================
void CObject::CollisionTrigger(CObject * Object)
{
	for each (auto list in m_PhysicsList) list->CollisionTrigger(Object);
	for each (auto list in m_BehaviorList) list->CollisionTrigger(Object);
}

//=============================================================================
// 衝突継続時オブジェクト内にあるリストに衝突継続時を知らせる
//=============================================================================
void CObject::CollisionEnter(CObject * Object)
{
	for each (auto list in m_PhysicsList) list->CollisionEnter(Object);
	for each (auto list in m_BehaviorList) list->CollisionEnter(Object);
}

//=============================================================================
// 衝突終了時オブジェクト内にあるリストに衝突終了時を知らせる
//=============================================================================
void CObject::CollisionRelease(CObject * Object)
{
	for each (auto list in m_PhysicsList) list->CollisionRelease(Object);
	for each (auto list in m_BehaviorList) list->CollisionRelease(Object);
}

//=============================================================================
// オブジェクトのリストに登録
//=============================================================================
void CObject::Attach(CScene* Scene)
{
	m_SceneList.push_back(Scene);
	SetObject(Scene, this);
}

void CObject::Attach(CCollision* Collision)
{
	m_CollisionList.push_back(Collision);
	SetObject(Collision, this);
}

void CObject::Attach(CBehavior* Behavior)
{
	m_BehaviorList.push_back(Behavior);
	SetObject(Behavior, this);
}

void CObject::Attach(CPhysics* Physics)
{
	m_PhysicsList.push_back(Physics);
	SetObject(Physics, this);
}

void CObject::Attach(CPointLight* PointLight)
{
	m_PointLight.push_back(PointLight);
	SetObject(PointLight, this);
}

//=============================================================================
// オブジェクトのリストから削除
//=============================================================================
void CObject::Detach(CScene* Scene)
{
	DetachList<CSceneManager>(Scene, m_SceneList);
}

void CObject::Detach(CCollision* Collision)
{
	DetachList<CCollisionManager>(Collision, m_CollisionList);
}

void CObject::Detach(CBehavior* Behavior)
{
	DetachList<CBehaviorManager>(Behavior, m_BehaviorList);
}

void CObject::Detach(CPhysics* Physics)
{
	DetachList<CPhysicsManager>(Physics, m_PhysicsList);
}

void CObject::Detach(CPointLight* PointLight)
{
	DetachList<CPointLightManager>(PointLight, m_PointLight);
}

//=============================================================================
// 指定されたリストマネージャーから削除
//=============================================================================
template<class Class, class List>
void CObject::DetachList(List * Object, list<List*> List)
{
	for (auto itr = List.begin(); itr != List.end(); itr++)
	{
		if (Object == (*itr))
		{
			itr = List.erase(itr);
			Class::GetInstance()->Release(Object);
			break;
		}
	}
}