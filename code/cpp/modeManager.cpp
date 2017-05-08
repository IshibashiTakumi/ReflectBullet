//=============================================================================
// ���[�h�Ǘ��N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
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
// �O���[�o���ϐ�
//=============================================================================
CModeManager* CModeManager::Instance = NULL;	//�C���X�^���X

//=============================================================================
// ���ׂẲ��
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
// ���ׂĂ̍X�V
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
// ���ׂĂ̕`��
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
// ���[�h�̐ݒ�
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