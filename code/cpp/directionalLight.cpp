//=============================================================================
// 平行光源
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "directionalLight.h"
#include "renderer.h"


//=============================================================================
// クラスの生成
//=============================================================================
CDirectionalLight::CDirectionalLight(D3DXCOLOR color, D3DXVECTOR3 Vec, int Number)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 
	D3DXVECTOR3 vecDir;

	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = D3DLIGHT_DIRECTIONAL; //平行光源
	m_Light.Diffuse = color; //光の色
	vecDir = Vec; //光の向き
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);
	pDevice->SetLight(Number, &m_Light); //ライトの設定
	pDevice->LightEnable(Number, TRUE); //ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE); //主電源
}

//=============================================================================
// クラスの破棄
//=============================================================================
CDirectionalLight::~CDirectionalLight()
{

}