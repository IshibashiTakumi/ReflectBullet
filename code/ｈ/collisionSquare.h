//=============================================================================
// �~�̓����蔻��
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
// �O���錾
//=============================================================================
class CCollision2DMap;
class CCollisionCircle;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CCollisionSquare : public CCollision
{
public:

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CCollisionSquare(CTransform* Transform, bool Detection);
	~CCollisionSquare();

	//��{�I�Ȋ֐��̐錾
	//=============================================================================
	void Init(D3DXVECTOR2 Size);
	void Uninit(void);
	void Draw(void);

	//�_�u���f�B�X�p�b�`�ɕK�v�Ȑ錾
	//=============================================================================
	virtual void CollisionDetection(CCollision* other) { other->DetectionAction(this); }

	static bool SquareToSquare(CCollisionSquare * Square, CCollisionSquare * _Square);
	static bool SquareToCircle(CCollisionSquare * Square, CCollisionCircle * Circle);
	static void ClosestPtPointSquare(D3DXVECTOR3 &Point, CCollisionSquare * Square, D3DXVECTOR2 &_Point);
	//static bool SquareDirection(D3DXVECTOR3 &Point, CCollisionSquare * Square);

	//�ϐ�
	//=============================================================================
	D3DXVECTOR2 m_Size;	//�}�X�T�C�Y

protected:

	////�_�u���f�B�X�p�b�`�̎��s��
	////=============================================================================
	virtual void DetectionAction(CCollisionSquare* other);
	virtual void DetectionAction(CCollision2DMap* other);
	virtual void DetectionAction(CCollisionCircle* other);
};