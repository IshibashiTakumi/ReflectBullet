//=============================================================================
// �����蔻����N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "collision.h"
#include "collisionManager.h"
#include "object.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CCollision::CCollision(CTransform* Transform, bool Detection)
{
	m_Transform = new CTransform;
	m_LocalTransform = Transform;
	m_Detection = Detection;
	CCollisionManager::GetInstance()->SetCollision(this);
	m_List.clear();
	m_OldList.clear();
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CCollision::~CCollision()
{
	m_List.clear();
	m_OldList.clear();
}

//=============================================================================
// �X�V
//=============================================================================
void CCollision::Update(void)
{
	CollisionSwap(&m_List, &m_OldList);
	m_List.clear();
	m_Rejection2D.clear();
}

//=============================================================================
// �ʒu�C��
//=============================================================================
void CCollision::Transformation(void)
{
	m_Transform->Pos = (m_Object->m_Transform->Pos + m_LocalTransform->Pos);
	m_Transform->Rot = (m_Object->m_Transform->Rot + m_LocalTransform->Rot);
	m_Transform->Scl = D3DXVECTOR3(m_Object->m_Transform->Scl.x * m_LocalTransform->Scl.x,
								   m_Object->m_Transform->Scl.y * m_LocalTransform->Scl.y,
								   m_Object->m_Transform->Scl.z * m_LocalTransform->Scl.z);
}

//=============================================================================
// ���X�g�̓���ւ�
//=============================================================================
void CCollision::CollisionSwap(std::list<CCollision*>* list, std::list<CCollision*>* _list)
{
	std::list<CCollision*> List, _List;

	List.clear();
	_List.clear();

	List.swap(*list);
	_List.swap(*_list);

	List.swap(_List);

	(*list).clear();
	(*_list).clear();

	for each (auto var in List)
	{
		(*list).push_back(var);
	}
	for each (auto _var in _List)
	{
		(*_list).push_back(_var);
	}
}