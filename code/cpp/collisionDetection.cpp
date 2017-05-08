//=============================================================================
// �����蔻����s�N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "collisionDetection.h"
#include "collision.h"
#include "collisionManager.h"
#include "collision2DMap.h"
#include "collisionCircle.h"
#include "collisionSquare.h"
#include "object.h"
#include "debugProc.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CCollisionDetection* CCollisionDetection::Instance = NULL;	//�C���X�^���X

//=============================================================================
// �N���X�̐���
//=============================================================================
CCollisionDetection::CCollisionDetection()
{

}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CCollisionDetection::~CCollisionDetection()
{

}

//=============================================================================
// �����蔻��
//=============================================================================
void CCollisionDetection::CollisionDetection(void)
{
	for each (auto list in CCollisionManager::GetInstance()->GetList())
	{
		if (list->GetDetection() == false) continue;
		for each (auto _list in CCollisionManager::GetInstance()->GetList())
		{
			if (Overlap(list, _list) == false) continue;
			list->CollisionDetection(_list);
		}
	}
	for each (auto list in CCollisionManager::GetInstance()->GetList())
	{
		CollisionState(list);
		if (list->GetDetection() == false) continue;
		Rejection(list);
	}
}

//=============================================================================
// �~�Ɖ~�̂����蔻��
//=============================================================================
void CCollisionDetection::CircleToCircle(CCollisionCircle* Circle, CCollisionCircle* _Circle)
{
	float Radius = Circle->m_Radius + _Circle->m_Radius;
	D3DXVECTOR2 Sub = Vec2Sub(D3DXVECTOR2(_Circle->m_Transform->Pos.x, _Circle->m_Transform->Pos.z), D3DXVECTOR2(Circle->m_Transform->Pos.x, Circle->m_Transform->Pos.z));
	if (Vec2Length(Sub) <= Radius * Radius)
	{
		REJECTION_2D Rejection{ D3DXVECTOR2(_Circle->m_Transform->Pos.x, _Circle->m_Transform->Pos.z), Radius - Vec2LengthSq(Sub), atan2f(Sub.x, Sub.y) + D3DX_PI, _Circle };
		Circle->m_Rejection2D.push_back(Rejection);
		REJECTION_2D _Rejection{ D3DXVECTOR2(Circle->m_Transform->Pos.x, Circle->m_Transform->Pos.z), Radius - Vec2LengthSq(Sub), atan2f(Sub.x, Sub.y), Circle };
		_Circle->m_Rejection2D.push_back(_Rejection);
		HitCollision(Circle, _Circle);
	}
}


//=============================================================================
// �~�Ǝl�p�̂����蔻��
//=============================================================================
void CCollisionDetection::CircleToSquare(CCollisionCircle* Circle, CCollisionSquare* Square)
{
	if(CCollisionSquare::SquareToCircle(Square, Circle))
	{
		HitCollision(Square, Circle);
	}
}

//=============================================================================
// �l�p�Ǝl�p�̂����蔻��
//=============================================================================
void CCollisionDetection::SquareToSquare(CCollisionSquare* Square, CCollisionSquare* _Square)
{
	/*float Radius = Circle->m_Radius + _Circle->m_Radius;
	D3DXVECTOR2 Sub = Vec2Sub(D3DXVECTOR2(_Circle->m_Transform->Pos.x, _Circle->m_Transform->Pos.z), D3DXVECTOR2(Circle->m_Transform->Pos.x, Circle->m_Transform->Pos.z));

	float angle = atan2f(Sub.x, Sub.y);
	CDebugProc::GetInstance()->PrintDebugProc("�p�x : %f", angle);

	if (Vec2Length(Sub) <= Radius * Radius)
	{
		if (Circle != NULL && _Circle != NULL) Ejection(Circle, _Circle, angle, (Radius - Vec2LengthSq(Sub)));
		HitCollision(Circle, _Circle);
	}*/
}

//=============================================================================
// �����������̏���
//=============================================================================
void CCollisionDetection::HitCollision(CCollision* Collision, CCollision* _Collision)
{
	Collision->SetList(_Collision);		//���������R���W�����N���X��ǉ�
	_Collision->SetList(Collision);		//���������R���W�����N���X��ǉ�
}

//=============================================================================
// �Փˏ��
//=============================================================================
void CCollisionDetection::CollisionState(CCollision* Collision)
{
	list<CCollision*> List = CCollision::GetList(Collision);
	list<CCollision*> OldList = CCollision::GetOldList(Collision);
	bool bUse;
	
	for each (auto list in List)
	{
		bUse = CollisionOverlap(list, OldList);
		if (bUse)
		{
			Collision->GetObj()->CollisionEnter(list->GetObj());
		}
		else if (!bUse)
		{
			Collision->GetObj()->CollisionTrigger(list->GetObj());
			Collision->GetObj()->CollisionEnter(list->GetObj());
		}
	}
	for each (auto list in OldList)
	{
		if (!CollisionOverlap(list, List)) Collision->GetObj()->CollisionRelease(list->GetObj());
	}
}

//=============================================================================
// �R���W�����̏Փ˂̎d���̔���
//=============================================================================
bool CCollisionDetection::CollisionOverlap(CCollision* list, std::list<CCollision*> _list)
{
	for each (CCollision* List in _list)
	{
		if (list == List) return true;
	}
	return false;
}

//=============================================================================
// �d�����
//=============================================================================
bool CCollisionDetection::Overlap(CCollision* Collision, CCollision* _Collision)
{
	if (Collision == _Collision) return false;

	for each (auto list in Collision->GetObj()->GetCollisionList())
	{
		if (_Collision != list) continue;
		return false;
	}
	return true;
}

//=============================================================================
// �r�ˏ���
//=============================================================================
void CCollisionDetection::Rejection(CCollision* Collision)
{
	for each (auto list in Collision->m_Rejection2D)
	{
		if (list.Collision->GetDetection() == false)
		{
			Collision->GetObj()->m_Transform->Pos.x += sinf(list.Angle) * list.Length;
			Collision->GetObj()->m_Transform->Pos.z += cosf(list.Angle) * list.Length;
		}
		else
		{
			Collision->GetObj()->m_Transform->Pos.x += sinf(list.Angle) * (list.Length * 0.5f);
			Collision->GetObj()->m_Transform->Pos.z += cosf(list.Angle) * (list.Length * 0.5f);
		}
	}
}