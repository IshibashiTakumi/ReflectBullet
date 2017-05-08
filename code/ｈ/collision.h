//=============================================================================
// �����蔻����N���X
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "transform.h"

//=============================================================================
// �\����
//=============================================================================
//typedef struct
//{
//	D3DXVECTOR2 Pos;				//�ߎ��_
//	float Length;					//�r�˒���
//	float Angle;					//�r�ˊp�x
//	class CCollision* Collision;	//�Ώ�
//}REJECTION_2D;

typedef struct
{
	D3DXVECTOR2 Pos;				//�ߎ��_
	float Length;					//�r�˒���
	float Angle;					//�r�ˊp�x
	class CCollision* Collision;	//�Ώ�
}REJECTION_2D;

//=============================================================================
// �O���錾
//=============================================================================
class CCollision2DMap;
class CCollisionCircle;
class CCollisionSquare;
class CObject;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CCollision
{
public:

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CCollision(CTransform* Transform, bool Detection);
	~CCollision();

	//��{�֐�
	//=============================================================================
	virtual void Init(void) { };		//������
	virtual void Uninit(void) = 0;		//���
	virtual void Update(void);			//�X�V
	virtual void Draw(void) = 0;		//�`��
	virtual void Transformation(void);	//�ʒu�C��
	
	//�_�u���f�B�X�p�b�`�ɕK�v�Ȑ錾
	//=============================================================================
	virtual void CollisionDetection(CCollision* other) = 0;
	virtual void DetectionAction(CCollision2DMap* other) = 0;
	virtual void DetectionAction(CCollisionCircle* other) = 0;
	virtual void DetectionAction(CCollisionSquare* other) = 0;

	//�ݒ�E�擾�֐�
	//=============================================================================
	CObject* GetObj(void) { return m_Object; }											//�I�u�W�F�N�g
	bool GetDetection(void) { return m_Detection; }										//���o
	void SetList(CCollision* Collision) { return m_List.push_back(Collision); }			//�Փ˔���p���X�g
	void SetOldList(CCollision* Collision) { return m_OldList.push_back(Collision); }	//�Փ˔���p���X�g
	static list<CCollision*> GetList(CCollision* Collision) { return Collision->m_List; }			//�Փ˔���p���X�g
	static list<CCollision*> GetOldList(CCollision* Collision) { return Collision->m_OldList; }		//�Փ˔���p���X�g

	//�ϐ�
	//=============================================================================
	CTransform* m_Transform;
	CTransform* m_LocalTransform;
	list<REJECTION_2D> m_Rejection2D;	//�r�ˏ������2D

	//�����֐�
	//=============================================================================
	template<class Class, class ...Argument>
	static CCollision* Create(CTransform* transform, bool Detection, Argument ...argument)
	{
		Class* Collision = new Class(transform, Detection);
		Collision->Init(argument...);
		return Collision;
	}

	template<class Class, class ...Argument>
	static CCollision* _Create(CTransform* transform, bool Detection, Argument*... argument)
	{
		Class* Collision = new Class(transform, Detection);
		Collision->Init(argument...);
		return Collision;
	}

protected:
	//�ϐ�
	//=============================================================================
	CObject* m_Object;					//�I�u�W�F�N�g���
	bool m_Detection;					//���o���s����

	void CollisionSwap(std::list<CCollision*>* list, std::list<CCollision*>* _list);

	//���X�g�|�C���^
	//=============================================================================
	list<CCollision*> m_List;		//�Փ˔���p���X�g���
	list<CCollision*> m_OldList;	//�Փ˔���p���X�g���
	unordered_map<CCollision*, CCollision*> m_Search;			//�����p

private:
	//CObject�ŌĂяo�����߂̏���(friend)
	//=============================================================================
	friend static void SetObject(CCollision* Collision, CObject* Object) { Collision->m_Object = Object; }
};