//=============================================================================
// Xモデル描画
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "sceneX.h"
#include "resource.h"
#include "model.h"
#include "modelX.h"
#include "renderer.h"
#include "camera.h"
#include "cameraManager.h"

#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "object.h"
#include "objectManager.h"

#include "shaderManager.h"
#include "shader.h"
#include "shaderX.h"

//=============================================================================
// クラスの生成
//=============================================================================
CSceneX::CSceneX(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_Transform = Transform;
	m_LocalTransform = new CTransform();
}

//=============================================================================
// クラスの破棄
//=============================================================================
CSceneX::~CSceneX()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CSceneX::Init(const string& FileName)
{
	m_ModelX = **CResource::Get<CModel>(FileName);
}


//=============================================================================
// 解放
//=============================================================================/
void CSceneX::Uninit(void)
{
	
}

//=============================================================================
// 描画
//=============================================================================/
void CSceneX::Draw(int num)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得 
	CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();		//カメラの取得
	CShaderManager::GetInstance()->Find<CShaderX>();	//シェーダの取得

	//ワールドマトリックスの設定
	SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);

	for (int nCntMat = 0; nCntMat < (int)m_ModelX->NumMat; nCntMat++)
	{
		CShaderManager::GetInstance()->Begin<CShaderX>(num, m_Transform->mtxWorld, pCamera->m_MtxView, pCamera->m_MtxProjection, m_ModelX->MeshMat[nCntMat], m_ModelX->MeshTex[nCntMat]);

		m_ModelX->Mesh->DrawSubset(nCntMat);				// メッシュを描画

		CShaderManager::GetInstance()->End();
	}
}