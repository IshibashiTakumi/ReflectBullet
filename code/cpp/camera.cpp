//=============================================================================
// カメラの基底クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "cameraManager.h"
#include "cameraController.h"

#include "shaderManager.h"
#include "shader.h"
#include "shader2D.h"
#include "shader3D.h"
#include "shaderX.h"

//=============================================================================
// クラスの生成
//=============================================================================
CCamera::CCamera(float nearZ, float farZ)
{
	m_PosV = Vec3Init();
	m_PosR = Vec3Init();
	m_Rot = Vec3Init();
	m_VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_PosW = Vec3Init();
	CCameraManager::GetInstance()->SetList(this);
	transScreenToWorld();
	m_Projection = Perspective;
	m_Controller = NULL;
	near_z = nearZ;
	far_z = farZ;
}

//=============================================================================
// クラスの破棄
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CCamera::Init(void)
{

}

//=============================================================================
// 解放
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// 更新
//=============================================================================
void CCamera::Update(void)
{
	transScreenToWorld();
	if(m_Controller != NULL) m_Controller->Update();
}

//=============================================================================
// カメラの描画
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	D3DXMatrixIdentity(&m_MtxProjection); //プロジェクションマトリックスの初期化

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DX_PI * 0.25f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, near_z, far_z);
	/*if(m_Projection == Perspective)	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DX_PI * 0.25f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, NEAR_Z, FAR_Z);
	else if(m_Projection == Orthographic) D3DXMatrixOrthoLH(&m_MtxProjection, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, NEAR_Z, FAR_Z);*/
	
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProjection); //プロジェクションマトリックスの設定

	D3DXMatrixIdentity(&m_MtxView); //マトリックスの初期化

	D3DXMatrixLookAtLH(&m_MtxView, &m_PosV, &m_PosR, &m_VecU); //ビューマトリックスの作成

	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView); //ビューマトリックスの設定

	CShader* shader = CShaderManager::GetInstance()->Find<CShader3D>();
	shader->Get()->SetMatrix("g_LightView", &m_MtxView);
	shader->Get()->SetMatrix("g_LightProj", &m_MtxProjection);
	shader->Get()->SetFloatArray("g_CameraPos", (float*)m_PosV, 3);

	shader = CShaderManager::GetInstance()->Find<CShaderX>();
	shader->Get()->SetMatrix("g_LightView", &m_MtxView);
	shader->Get()->SetMatrix("g_LightProj", &m_MtxProjection);
	shader->Get()->SetFloatArray("g_CameraPos", (float*)m_PosV, 3);

	shader = CShaderManager::GetInstance()->Find<CShader2D>();
	shader->Get()->SetMatrix("g_LightView", &m_MtxView);
	shader->Get()->SetMatrix("g_LightProj", &m_MtxProjection);

	D3DXVECTOR3 vec = Vec3Nor(m_PosR - m_PosV);
	shader->Get()->SetFloatArray("g_light", (float*)vec, 3);
}

void CCamera::ReleaseController(void)
{
	if (m_Controller != NULL)
	{
		delete m_Controller;
		m_Controller = NULL;
	}
}

//=============================================================================
// 
//=============================================================================
void CCamera::SetController(CCameraController * Controller)
{
	ReleaseController();
	m_Controller = Controller;
}

//=============================================================================
// 
//=============================================================================
void CCamera::transScreenToWorld(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	// ビューポート行列を作成
	D3DXMATRIX vpMat;
	D3DXMatrixIdentity(&vpMat);

	D3DVIEWPORT9 vp;
	pDevice->GetViewport(&vp);

	vpMat._11 = (float)vp.Width / 2;
	vpMat._22 = -1.0f * (float)(vp.Height / 2);
	vpMat._33 = (float)vp.MaxZ - vp.MinZ;
	vpMat._41 = (float)(vp.X + vp.Width / 2);
	vpMat._42 = (float)(vp.Y + vp.Height / 2);
	vpMat._43 = vp.MinZ;

	// スクリーン位置をワールドへ
	m_PosW.x = (float)GetMousePos().x;
	m_PosW.y = (float)GetMousePos().y;
	m_PosW.z = 1.0f;

	D3DXMATRIX invMat, inv_proj, inv_view;
	D3DXMatrixInverse(&invMat, 0, &vpMat);
	D3DXMatrixInverse(&inv_proj, 0, &m_MtxProjection);
	D3DXMatrixInverse(&inv_view, 0, &m_MtxView);

	invMat *= inv_proj * inv_view;

	D3DXVec3TransformCoord(&m_PosW, &m_PosW, &invMat);
}