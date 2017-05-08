//=============================================================================
// タイム描画
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

/*******************************************************************************
* クラスの定義
*******************************************************************************/
class CTime : public CScene
{
public:

	CTime(CTransform* Transform);
	~CTime();

	void Init(int digit, int time, D3DXVECTOR2 size, string texName);
	void Uninit(void);
	void Update(void);
	void Draw(int pass = 0);
	float GetTime(void) { return m_LimitTime; }

private:

	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_Texture; //テクスチャへのポインタ

	int m_nCounterTimeAnim;								//アニメーションカウンター
	int m_nPatternTimeAnim;								//アニメーションパターンNo
	float m_LimitTime;									//制限時間
	int m_Digit;										//タイムの桁数
};