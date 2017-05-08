//=============================================================================
// ShaderAlphaMask3Dクラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "shaderAlphaMask3D.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 CShaderAlphaMask3D::m_Texture = NULL;	//インスタンス
LPDIRECT3DTEXTURE9 CShaderAlphaMask3D::m_Mask = NULL;	//インスタンス

//=============================================================================
// クラスの生成
//=============================================================================
CShaderAlphaMask3D::CShaderAlphaMask3D()
{
	m_Texture = *CResource::Get<CTexture>("TextureNone.jpg");
	m_Mask = *CResource::Get<CTexture>("TextureNone.jpg");
}

//=============================================================================
// クラスの破棄
//=============================================================================
CShaderAlphaMask3D::~CShaderAlphaMask3D()
{

}

//=============================================================================
// 描画開始
//=============================================================================
void CShaderAlphaMask3D::Begin(int pass, D3DXMATRIX& world, D3DXMATRIX& view, D3DXMATRIX& proj, LPDIRECT3DTEXTURE9& texture, LPDIRECT3DTEXTURE9& mask, float Criteria)
{
	// エフェクト設定
	m_Effect->SetMatrix("g_world", &world);
	m_Effect->SetMatrix("g_view", &view);
	m_Effect->SetMatrix("g_proj", &proj);
	m_Effect->SetTexture("g_texture", texture);
	m_Effect->SetTexture("g_MaskTex", mask);
	m_Effect->SetFloat("g_Criteria", Criteria);

	m_Effect->Begin(NULL, 0);	// テクニック開始 
	m_Effect->BeginPass(3);		//パスの指定
}

//=============================================================================
// 描画終了
//=============================================================================
void CShaderAlphaMask3D::End(void)
{
	m_Effect->EndPass();
	m_Effect->End();
}
