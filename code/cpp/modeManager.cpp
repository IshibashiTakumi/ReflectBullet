//=============================================================================
// モード管理クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "modeManager.h"
#include "mode.h"
#include "objectManager.h"
#include "sceneManager.h"
#include "collisionManager.h"
#include "behaviorManager.h"
#include "physicsManager.h"
#include "collisionDetection.h"
#include "pointLightManager.h"
#include "deferredShader.h"

//=============================================================================
// グローバル変数
//=============================================================================
CModeManager* CModeManager::Instance = NULL;	//インスタンス

//=============================================================================
// すべての解放
//=============================================================================
void CModeManager::Uninit(void)
{
	m_Mode->Uninit();

	CPointLightManager::GetInstance()->UninitAll();
	CCollisionManager::GetInstance()->UninitAll();
	CObjectManager::GetInstance()->UninitAll();
	CBehaviorManager::GetInstance()->UninitAll();
	CPhysicsManager::GetInstance()->UninitAll();
	CSceneManager::GetInstance()->UninitAll();
}

//=============================================================================
// すべての更新
//=============================================================================
void CModeManager::Update(void)
{
	m_Mode->Update();

	CPointLightManager::GetInstance()->UpdateAll();
	CCollisionManager::GetInstance()->UpdateAll();
	CObjectManager::GetInstance()->UpdateAll();
	CPhysicsManager::GetInstance()->UpdateAll();
	CSceneManager::GetInstance()->UpdateAll();
	CBehaviorManager::GetInstance()->UpdateAll();
	CCollisionDetection::GetInstance()->CollisionDetection();
}

//=============================================================================
// すべての描画
//=============================================================================
void CModeManager::Draw(void)
{
	CPointLightManager::GetInstance()->DrawAll();
	CDeferredShader::GetInstance()->Draw(1);
	m_Mode->Draw();
	//CObjectManager::GetInstance()->DrawAll();
	CSceneManager::GetInstance()->PriorityDraw(PRIORITY_2D);
}

//=============================================================================
// モードの設定
//=============================================================================
void CModeManager::SetMode(CMode* Mode)
{
	if (m_Mode != NULL)
	{
		Uninit();
		delete m_Mode;
		m_Mode = NULL;
	}
	m_Mode = Mode;
	m_Mode->Init();
}