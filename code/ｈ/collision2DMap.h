//=============================================================================
// 2DMap�̓����蔻��
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SPHERE_COLOR (D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f))

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	int Number;
	class CCollision* Collision;	//�Ώ�
}MAP_PANEL;

//=============================================================================
// �O���錾
//=============================================================================
class CCollisionCircle;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CCollision2DMap : public CCollision
{
public:

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CCollision2DMap(CTransform* Transform, bool Detection);
	~CCollision2DMap();

	//��{�I�Ȋ֐��̐錾
	//=============================================================================
	void Init(float Size, string& FileName);
	void Uninit(void);
	void Draw(void);

	//�_�u���f�B�X�p�b�`�ɕK�v�Ȑ錾
	//=============================================================================
	virtual void CollisionDetection(CCollision* other) { other->DetectionAction(this); }

	bool MapToCircle(CCollision2DMap* Map, CCollisionCircle* Circle, D3DXVECTOR3 &Point);
	void SquareToCircle(int num, int MapState, float Size, CCollisionCircle * Circle, D3DXVECTOR2 &Point);

	//�ϐ�
	//=============================================================================
	float m_Size;	//�}�X�T�C�Y
	int m_Width, m_Height;
	list<int> m_Map;
	list<MAP_PANEL> m_MapPanel;

protected:

	//�_�u���f�B�X�p�b�`�̎��s��
	//=============================================================================
	virtual void DetectionAction(CCollision2DMap* other);
	virtual void DetectionAction(CCollisionCircle* other);
	virtual void DetectionAction(CCollisionSquare* other) {};
};