#ifndef _DRAWUTILITY_H_
#define _DRAWUTILITY_H_

//=============================================================================
// タイトル	便利関数
// ファイル: drawUtility.h
// 作成者:   石橋拓巳
// 作成日:   2016/12/1
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "d3dx9.h"

//=============================================================================
//
//	Matrix
//
//=============================================================================

//=============================================================================
//	スケールをマトリクスに反映
//=============================================================================
static inline void SetMatrixScal(D3DXMATRIX &matrix, D3DXVECTOR3 scl)
{
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixScaling(&mtx, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);
}
//=============================================================================
//	回転をマトリクスに反映
//=============================================================================
static inline void SetMatrixRot(D3DXMATRIX &matrix, D3DXVECTOR3 rot)
{
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationYawPitchRoll(&mtx, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);
}
//=============================================================================
//	位置をマトリクスに反映
//=============================================================================
static inline void SetMatrixPos(D3DXMATRIX &matrix, D3DXVECTOR3 pos)
{
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&matrix, &matrix, &mtx);
}

//=============================================================================
//	スケール・回転・位置をマトリクスに反映
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