//=============================================================================
// Shader2Dクラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "shaderX.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 CShaderX::m_Texture = NULL;	//インスタンス

//=============================================================================
// クラスの生成
//=============================================================================
CShaderX::CShaderX()
{
	m_Texture = *CResource::Get<CTexture>("TextureNone.jpg");
}

//=============================================================================
// クラスの破棄
//=============================================================================
CShaderX::~CShaderX()
{

}

//=============================================================================
// 描画開始
//=============================================================================
void CShaderX::Begin(int pass, D3DXMATRIX& world, D3DXMATRIX& view, D3DXMATRIX& proj, D3DMATERIAL9& material, LPDIRECT3DTEXTURE9& texture)
{
	// エフェクト設定
	m_Effect->SetMatrix("g_world", &world);
	m_Effect->SetMatrix("g_view", &view);
	m_Effect->SetMatrix("g_proj", &proj);

	m_Effect->SetFloatArray("g_Ambient", (float*)(&material.Ambient), 4);
	m_Effect->SetFloatArray("g_Diffuse", (float*)(&material.Diffuse), 4);
	m_Effect->SetFloatArray("g_Emissive", (float*)(&material.Emissive), 4);
	m_Effect->SetFloatArray("g_Power", (float*)(&material.Power), 1);
	m_Effect->SetFloatArray("g_Specular", (float*)(&material.Specular), 4);

	if(texture != NULL) m_Effect->SetTexture("g_texture", texture);
	else m_Effect->SetTexture("g_texture", m_Texture);

	m_Effect->Begin(NULL, 0);	// テクニック開始 
	m_Effect->BeginPass(pass);		//パスの指定
}

//=============================================================================
// 描画終了
//=============================================================================
void CShaderX::End(void)
{
	m_Effect->EndPass();
	m_Effect->End();
}
