#ifndef _DRAWUTILITY_H_
#define _DRAWUTILITY_H_

//=============================================================================
// �^�C�g��	�֗��֐�
// �t�@�C��: drawUtility.h
// �쐬��:   �΋���
// �쐬��:   2016/12/1
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "d3dx9.h"

//=============================================================================
//
//	Matrix
//
//=============================================================================

//=============================================================================
//	�X�P�[�����}�g���N�X�ɔ��f
//=============================================================================
static inline void SetMatrixScal(D3DXMATRIX &matrix, D3DXVECTOR3 scl)
{
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixScaling(&mtx, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);
}
//=============================================================================
//	��]���}�g���N�X�ɔ��f
//=============================================================================
static inline void SetMatrixRot(D3DXMATRIX &matrix, D3DXVECTOR3 rot)
{
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationYawPitchRoll(&mtx, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);
}
//=============================================================================
//	�ʒu���}�g���N�X�ɔ��f
//=============================================================================
static inline void SetMatrixPos(D3DXMATRIX &matrix, D3DXVECTOR3 pos)
{
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);
}

//=============================================================================
//	�X�P�[���E��]�E�ʒu���}�g���N�X�ɔ��f
//=============================================================================
static inline void SetMatrix(D3DXMATRIX &matrix, D3DXVECTOR3 scl, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	D3DXMatrixIdentity(&matrix);

	D3DXMATRIX mtx;
	D3DXMatrixScaling(&mtx, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);

	D3DXMatrixRotationYawPitchRoll(&mtx, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);

	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);
}

#endif