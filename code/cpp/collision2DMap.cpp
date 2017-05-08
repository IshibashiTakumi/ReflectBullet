//=============================================================================
// 2DMap�̓����蔻��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "collision2DMap.h"
#include "collisionDetection.h"
#include "collisionCircle.h"
#include "object.h"
#include "renderer.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CCollision2DMap::CCollision2DMap(CTransform* Transform, bool Detection) : CCollision(Transform, Detection)
{

}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CCollision2DMap::~CCollision2DMap()
{

}

//=============================================================================
// ������
//=============================================================================
void CCollision2DMap::Init(float Size, string& FileName)
{
	m_Size = Size;

	int temp;
	m_Width = 0, m_Height = 0;
	//�t�@�C���̓ǂݍ���
	ifstream file(FileName);
	if (file)
	{
		string str;
		while (getline(file, str))
		{
			m_Width = 0;
			string token;
			istringstream stream(str);
			while (getline(stream, token, ','))
			{
				temp = stoi(token);
				m_Map.push_back(temp);
				m_Width++;
			}
			m_Height++;
		}
	}
}

//=============================================================================
// ���
//=============================================================================
void CCollision2DMap::Uninit(void)
{

}

//=============================================================================
// �`��
//=============================================================================
void CCollision2DMap::Draw(void)
{
	
}

//=============================================================================
// �����蔻��̎��s��(2DMap�Ƃ̂����蔻��)
//=============================================================================
void CCollision2DMap::DetectionAction(CCollision2DMap * other)
{

}

//=============================================================================
// �����蔻��̎��s��(�~�Ƃ̂����蔻��)
//=============================================================================
void CCollision2DMap::DetectionAction(CCollisionCircle * other)
{

}


//=============================================================================
//	����Aabb�Ɍ������Ă���ꍇ�͐^��Ԃ��A�����łȂ��ꍇ�͋U��Ԃ�
//  ���̒��S�ɑ΂���Aabb��̍ŋߐړ_�ł���_���Ԃ�
//=============================================================================
bool CCollision2DMap::MapToCircle(CCollision2DMap * Map, CCollisionCircle * Circle, D3DXVECTOR3 &Point)
{
	//���̒��S�ɑ΂���ŋߐړ_�ł���Aabb��ɂ���_Point��������
	int num = 0;
	D3DXVECTOR2 Pos;
	for each (auto list in Map->m_Map)
	{
		/*if (SquareToCircle(num, list, Map->m_Size, Circle, Pos))
		{
			NEAR_POINT Near = { Pos, Circle };
			Map->m_Rejection2D.push_back(Near);
		}*/
		num++;
	}

	//����Aabb����������̂́A���̒��S����_Point�܂ł�(��������)������(��������)���̔��a�����������ꍇ
	D3DXVECTOR3 vec = Point - Circle->m_Transform->Pos;
	return Vec3Length(vec) <= Circle->m_Radius * Circle->m_Radius;
}

//=============================================================================
//	�^����ꂽ�_Point�ɑ΂��āAAabb��������͒��ɂ���Point�̍ŋߐړ__Point��Ԃ�
//=============================================================================
void CCollision2DMap::SquareToCircle(int num, int MapState, float Size, CCollisionCircle * Circle, D3DXVECTOR2 &Point)
{
	//float point[2] = { Point.x, Point.y }, _point[2];
	//D3DXVECTOR2 Min = Aabb->m_Transform->Pos.x + Aabb->m_Min.x, Max = Aabb->m_Transform->Pos + Aabb->m_Max;
	//float min[3] = { Min.x, Min.y, Min.z }, max[3] = { Max.x, Max.y, Max.z };

	////�e���W���ɑ΂��āA�_�̍��W�l���{�b�N�X�̊O���ɂ���ꍇ��
	////�{�b�N�X�܂œ_���N�����v�A�����łȂ���΂��̂܂�
	//for (int count = 0; count < 2; count++)
	//{
	//	if (point[count] < min[count]) point[count] = min[count];	// point[count] = max(point[count], min[i]);
	//	if (point[count] > max[count]) point[count] = max[count];	// point[count] = min(point[count], max[i]);
	//	_point[count] = point[count];
	//}
	//Point = D3DXVECTOR2(_point[0], _point[1]);
}
