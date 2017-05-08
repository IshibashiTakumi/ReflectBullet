//=============================================================================
// 2D描画
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CScene2D : public CScene
{
public:

	CScene2D(CTransform* Transform);
	~CScene2D();

	void Init(D3DXVECTOR2 Size, string& TexName, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), bool Noise = false);
	void Uninit(void);
	void Update(void);
	void Draw(int pass);

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_Texture; //テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_Mask; //テクスチャへのポインタ
	D3DXVECTOR2 m_Size;
	float m_Criteria;
	bool m_Noise;
};