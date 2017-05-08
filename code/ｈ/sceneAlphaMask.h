//=============================================================================
// 3D描画
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CSceneAlphaMask : public CScene
{
public:
	CSceneAlphaMask(CTransform* Transform);
	~CSceneAlphaMask();

	void Init(D3DXVECTOR2 Size, string& Texture, string& Mask, float Criteria = 0.0f, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2 tex = D3DXVECTOR2(1.0f, 1.0f));
	void Uninit(void);
	void Draw(int num);

	float m_Criteria;

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_Texture;		//テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_Mask;		//法線マップへのポインタ
};