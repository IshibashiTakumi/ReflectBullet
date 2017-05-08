//=============================================================================
// Object���N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
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
// �N���X�̐���
//=============================================================================
CObject::CObject(const string& name, const string& tag, CTransform* Transform)
{
	m_Transform = Transform;
	m_Name = name;
	m_Tag = tag;
	CObjectManager::GetInstance()->SetObject(this);
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CObject::~CObject()
{
	delete m_Transform;

	//���X�g�̉��
	//=============================================================================
	m_SceneList.clear();		//�V�[��
	m_CollisionList.clear();	//�R���W����
	m_BehaviorList.clear();		//�s��
	m_PhysicsList.clear();		//�������Z
	m_PointLight.clear();		//�_����
}

//=============================================================================
// �I�u�W�F�N�g�̉��
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
// �I�u�W�F�N�g�P�̂�j������
//=============================================================================
void CObject::Release(void)
{
	CObjectManager::GetInstance()->Release(this);
}

//=============================================================================
// �I�u�W�F�N�g���S�̂�j������
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
// �Փˎ��I�u�W�F�N�g���ɂ��郊�X�g�ɏՓˎ���m�点��
//=============================================================================
void CObject::CollisionTrigger(CObject * Object)
{
	for each (auto list in m_PhysicsList) list->CollisionTrigger(Object);
	for each (auto list in m_BehaviorList) list->CollisionTrigger(Object);
}

//=============================================================================
// �Փˌp�����I�u�W�F�N�g���ɂ��郊�X�g�ɏՓˌp������m�点��
//=============================================================================
void CObject::CollisionEnter(CObject * Object)
{
	for each (auto list in m_PhysicsList) list->CollisionEnter(Object);
	for each (auto list in m_BehaviorList) list->CollisionEnter(Object);
}

//=============================================================================
// �ՓˏI�����I�u�W�F�N�g���ɂ��郊�X�g�ɏՓˏI������m�点��
//=============================================================================
void CObject::CollisionRelease(CObject * Object)
{
	for each (auto list in m_PhysicsList) list->CollisionRelease(Object);
	for each (auto list in m_BehaviorList) list->CollisionRelease(Object);
}

//=============================================================================
// �I�u�W�F�N�g�̃��X�g�ɓo�^
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
// �I�u�W�F�N�g�̃��X�g����폜
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
// �w�肳�ꂽ���X�g�}�l�[�W���[����폜
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