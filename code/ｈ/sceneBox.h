//=============================================================================
// ボックス描画
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CSceneBox : public CScene
{
public:

	CSceneBox(CTransform* Transform);
	~CSceneBox();

	void Init(D3DXVECTOR3 Size, string& Texture, string& NormalMap = (string)"NormalNone.jpg", D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void Uninit(void);
	void Draw(int num);
private:

	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_Texture;	//テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_NormalMap;		//法線マップへのポインタ
};
