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
class CScene3D : public CScene
{
public:
	CScene3D(CTransform* Transform);
	~CScene3D();

	void Init(D3DXVECTOR2 Size, string& Texture, string& NormalMap = (string)"NormalNone.jpg", D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2 tex = D3DXVECTOR2(1.0f, 1.0f));
	void Uninit(void);
	void Draw(int num);

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_Texture;		//テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_NormalMap;		//法線マップへのポインタ
};