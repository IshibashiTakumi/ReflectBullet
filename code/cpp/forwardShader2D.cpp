//=============================================================================
// Shader2Dクラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "forwardShader2D.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"

//=============================================================================
// グローバル変数
//=============================================================================
#define NOISE_SIZE (0.04f)
#define NOISE_ADD (0.05f)

//=============================================================================
// クラスの生成
//=============================================================================
LPDIRECT3DTEXTURE9 CForwardShader2D::m_Texture = NULL;	//インスタンス

//=============================================================================
// クラスの生成
//=============================================================================
CForwardShader2D::CForwardShader2D()
{
	m_Texture = *CResource::Get<CTexture>("TextureNone.jpg");
}

//=============================================================================
// クラスの破棄
//=============================================================================
CForwardShader2D::~CForwardShader2D()
{

}

//=============================================================================
// 描画開始
//=============================================================================
void CForwardShader2D::Begin(int pass, LPDIRECT3DTEXTURE9& texture, LPDIRECT3DTEXTURE9& mask, float Criteria, bool Noise)
{
	m_Effect->SetTexture("g_Texture", texture);
	m_Effect->SetTexture("g_Mask", mask);
	m_Effect->SetFloat("g_Criteria", Criteria);

	if (Noise)
	{
		m_Angle += NOISE_ADD;
		m_Angle = RotCorrection(m_Angle);
		m_Effect->SetFloat("g_Amplitude", (NOISE_SIZE * sinf(m_Angle)));
		m_Effect->SetFloat("g_Seed", (rand() % 1000) / 1000.0f);
	}
	else
	{
		m_Effect->SetFloat("g_Amplitude", 0.0f);
		m_Effect->SetFloat("g_Seed", 0.0f);
	}

	m_Effect->Begin(NULL, 0);	// テクニック開始 
	m_Effect->BeginPass(pass);		//パスの指定
}

//=============================================================================
// 描画終了
//=============================================================================
void CForwardShader2D::End(void)
{
	m_Effect->EndPass();
	m_Effect->End();
}
