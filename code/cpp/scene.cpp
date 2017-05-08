//=============================================================================
// Scene基底クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "sceneManager.h"
#include "object.h"
#include "renderer.h"

//=============================================================================
// クラスの生成
//=============================================================================
CScene::CScene(CTransform* Transform, PRIORITY Priority)
{
	m_Priority = Priority;
	m_Light = true;
	m_Cull = D3DCULL_CCW;

	m_LocalTransform = Transform;
	m_Transform = new CTransform();

	CSceneManager::GetInstance()->SetObject(Priority, this);	//登録
}

//=============================================================================
// クラスの破棄
//=============================================================================
CScene::~CScene()
{
	delete m_Transform;
	delete m_LocalTransform;
}

//=============================================================================
// 位置修正
//=============================================================================
void CScene::Transformation(void)
{
	m_Transform->Pos = (m_Object->m_Transform->Pos + m_LocalTransform->Pos);
	m_Transform->Rot = (m_Object->m_Transform->Rot + m_LocalTransform->Rot);
	m_Transform->Scl = D3DXVECTOR3(m_Object->m_Transform->Scl.x * m_LocalTransform->Scl.x,
											   	m_Object->m_Transform->Scl.y * m_LocalTransform->Scl.y,
												m_Object->m_Transform->Scl.z * m_LocalTransform->Scl.z);
}

//=============================================================================
// 描画開始
//=============================================================================
void CScene::Begin(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	pDevice->SetRenderState(D3DRS_CULLMODE, m_Cull); //カリング方法
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); // ライティングを無効化する
}

//=============================================================================
// 描画終了
//=============================================================================
void CScene::End(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリング方法
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE); // ライティングを無効化する
}
