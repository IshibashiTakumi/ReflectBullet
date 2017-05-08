//=============================================================================
// �~�̓����蔻��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "collisionSquare.h"
#include "collisionCircle.h"
#include "collisionDetection.h"
#include "object.h"
#include "renderer.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CCollisionSquare::CCollisionSquare(CTransform* Transform, bool Detection) : CCollision(Transform, Detection)
{

}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CCollisionSquare::~CCollisionSquare()
{

}

//=============================================================================
// ������
//=============================================================================
void CCollisionSquare::Init(D3DXVECTOR2 Size)
{
	m_Size = Size;
}

//=============================================================================
// ���
//=============================================================================
void CCollisionSquare::Uninit(void)
{

}

//=============================================================================
// �`��
//=============================================================================
void CCollisionSquare::Draw(void)
{
	
}

//=============================================================================
// �����蔻��̎��s��(�~�Ƃ̂����蔻��)
//=============================================================================
void CCollisionSquare::DetectionAction(CCollisionSquare * other)
{

}

//=============================================================================
// �����蔻��̎��s��(2DMap�Ƃ̂����蔻��)
//=============================================================================
void CCollisionSquare::DetectionAction(CCollision2DMap * other)
{

}

//=============================================================================
// �����蔻��̎��s��(�l�p�Ƃ̂����蔻��)
//=============================================================================
void CCollisionSquare::DetectionAction(CCollisionCircle * other)
{
	CCollisionDetection::GetInstance()->CircleToSquare(other, this);
}


//=============================================================================
//	�l�p���l�p�Ɍ������Ă���ꍇ�͐^��Ԃ��A�����łȂ��ꍇ�͋U��Ԃ�
//=============================================================================
bool CCollisionSquare::SquareToSquare(CCollisionSquare * Square, CCollisionSquare * _Square)
{
	D3DXVECTOR3 Pos = Square->m_Transform->Pos, _Pos = _Square->m_Transform->Pos;
	D3DXVECTOR2 Size = Square->m_Size * 0.5f, _Size = _Square->m_Size * 0.5f;
	D3DXVECTOR2 Sub;

	if (fabs(Pos.x - _Pos.x) > (Size.x + _Size.x)) return false;
	if (fabs(Pos.z - _Pos.z) > (Size.y + _Size.y)) return false;

	/*Sub.x = (Size.x + _Size.x) - fabs(Pos.x - _Pos.x);
	Sub.y = (Size.y + _Size.y) - fabs(Pos.z - _Pos.z);

	_Square->m_Transform->Pos.x += Sub.x;
	_Square->m_Transform->Pos.z += Sub.y;*/

	return true;
}

//=============================================================================
//	����Square�Ɍ������Ă���ꍇ�͐^��Ԃ��A�����łȂ��ꍇ�͋U��Ԃ�
//  ���̒��S�ɑ΂���Square��̍ŋߐړ_�ł���_���Ԃ�
//=============================================================================
bool CCollisionSquare::SquareToCircle(CCollisionSquare * Square, CCollisionCircle * Circle)
{
	D3DXVECTOR2 Point;	//�ߎ��_

	//���̒��S�ɑ΂���ŋߐړ_�ł���Square��ɂ���_Point��������
	ClosestPtPointSquare(Circle->m_Transform->Pos, Square, Point);

	//����Square����������̂́A���̒��S����_Point�܂ł�(��������)������(��������)���̔��a�����������ꍇ
	D3DXVECTOR2 vec = D3DXVECTOR2(Circle->m_Transform->Pos.x, Circle->m_Transform->Pos.z) - Point;
	if (Vec2Length(vec) <= Circle->m_Radius * Circle->m_Radius)
	{
		REJECTION_2D Rejection{ Point, Circle->m_Radius - Vec2LengthSq(vec), atan2f(vec.x, vec.y) + D3DX_PI, Circle };
		Square->m_Rejection2D.push_back(Rejection);
		REJECTION_2D _Rejection{ D3DXVECTOR2(Circle->m_Transform->Pos.x, Circle->m_Transform->Pos.z), Circle->m_Radius - Vec2LengthSq(vec), atan2f(vec.x, vec.y), Square };
		Circle->m_Rejection2D.push_back(_Rejection);
		return true;
	}
	return false;
}

//=============================================================================
//	�^����ꂽ�_Point�ɑ΂��āASquare��������͒��ɂ���Point�̍ŋߐړ__Point��Ԃ�
//=============================================================================
void CCollisionSquare::ClosestPtPointSquare(D3DXVECTOR3 &Point, CCollisionSquare * Square, D3DXVECTOR2 &_Point)
{
	float point[2] = { Point.x, Point.z }, _point[2];
	D3DXVECTOR2 size = Square->m_Size * 0.5f;
	D3DXVECTOR2 Min = D3DXVECTOR2(Square->m_Transform->Pos.x, Square->m_Transform->Pos.z) - size;
	D3DXVECTOR2 Max = D3DXVECTOR2(Square->m_Transform->Pos.x, Square->m_Transform->Pos.z) + size;
	float min[2] = { Min.x, Min.y }, max[2] = { Max.x, Max.y };

	//�e���W���ɑ΂��āA�_�̍��W�l���{�b�N�X�̊O���ɂ���ꍇ��
	//�{�b�N�X�܂œ_���N�����v�A�����łȂ���΂��̂܂�
	for (int count = 0; count < 2; count++)
	{
		if (point[count] < min[count]) point[count] = min[count];	// point[count] = max(point[count], min[i]);
		if (point[count] > max[count]) point[count] = max[count];	// point[count] = min(point[count], max[i]);
		_point[count] = point[count];
	}
	_Point = D3DXVECTOR2(_point[0], _point[1]);
}