//=============================================================================
// Object���N���X
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "transform.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene;
class CCollision;
class CBehavior;
class CPhysics;
class CPointLight;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CObject(const string& name, const string& tag, CTransform* Transform);
	~CObject();

	//��{
	//=============================================================================
	void Init(void) {};		//������
	void Uninit(void);		//���
	void Update(void) {};	//�X�V
	void Draw(void) {};	//�`��

	//�j��
	//=============================================================================
	virtual void Release(void);		//�P��
	virtual void Destroy(void);		//�S��

	//�Փ�
	//=============================================================================
	void CollisionTrigger(CObject* Object);		//�Փˎ�
	void CollisionEnter(CObject* Object);		//�Փˌp����
	void CollisionRelease(CObject* Object);		//�ՓˏI����

	//�ϐ�
	//=============================================================================
	CTransform* m_Transform;

	//���X�g�擾
	//=============================================================================
	list<CScene*>		GetSceneList(void) { return m_SceneList; }				//�V�[��
	list<CCollision*>	GetCollisionList(void) { return m_CollisionList; }		//�R���W����
	list<CBehavior*>	GetBehaviorList(void) { return m_BehaviorList; }		//�s��
	list<CPhysics*>		GetPhysicsList(void) { return m_PhysicsList; }			//�������Z
	string GetName(void) { return m_Name; }										//���O�̎擾								
	string GetTag(void) { return m_Tag; }										//�^�O�̎擾

	//�����֐�
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

	//���X�g�ǉ��֐�
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
	//���X�g�|�C���^
	//=============================================================================
	list<CScene*> m_SceneList;			//�V�[��
	list<CCollision*> m_CollisionList;	//�R���W����
	list<CBehavior*> m_BehaviorList;	//�s��
	list<CPhysics*> m_PhysicsList;		//�������Z
	list<CPointLight*> m_PointLight;	//�_����

private:
	//�ϐ�
	//=============================================================================
	string m_Name;	//���O
	string m_Tag;	//�^�O

	//�֐�
	//=============================================================================
	template<class Class, class List>
	static void DetachList(List * Object, list<List*> List);
};
