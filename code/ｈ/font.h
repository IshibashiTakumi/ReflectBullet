//=============================================================================
// 文字描画
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CFont : public CScene
{
public:

	CFont(CTransform* Transform);
	~CFont();

	void Init(D3DXVECTOR2 Size, string word, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void Uninit(void);
	void Update(void);
	void Draw(int pass = 0);
	void SetColor(D3DXCOLOR color);
private:
	static string m_Font;
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_Texture; //テクスチャへのポインタ
	D3DXVECTOR2 m_Size;
	unsigned int m_WordMax;

	//走査関数
	bool SetScan(char font, D3DXVECTOR2& tex);
};