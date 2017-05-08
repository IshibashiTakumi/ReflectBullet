//=============================================================================
// ���C�t
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "lifeBehavior.h"
#include "renderer.h"
#include "objectManager.h"
#include "object.h"
#include "aiState.h"
#include "aiStateStop.h"
#include "aiStateMovement.h"
#include "aiStateAttack.h"
#include "sceneAlphaMask.h"
#include "bulletBehavior.h"
#include "deathBehavior.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CLifeBehavior::CLifeBehavior() : CBehavior()
{

}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CLifeBehavior::~CLifeBehavior()
{

}

//=============================================================================
// ������
//=============================================================================
void CLifeBehavior::Init(float Life, string& tagName)
{
	m_LifeMax = Life;
	m_Life = Life;
	m_AlphaMask = NULL;
	m_TagName = tagName;
	m_Use = false;
	m_use = false;
}

//=============================================================================
// ���
//=============================================================================
void CLifeBehavior::Uninit(void)
{
	
}

//=============================================================================
// �X�V
//=============================================================================
void CLifeBehavior::Update(void)
{
	if (!m_Use)
	{
		m_AlphaMask = Find<CSceneAlphaMask>(m_Object->GetSceneList());
		m_Use = true;
	}
	m_AlphaMask->m_Criteria = 1.0f - (m_Life / m_LifeMax);

	if (m_Life <= 0 && m_use == false)
	{
		CBehavior* Behavior = CBehavior::Create<CDeathBehavior>();
		m_Object->Attach(Behavior);
		m_use = true;
	}
}

//=============================================================================
// ���������u��
//=============================================================================
void CLifeBehavior::CollisionTrigger(CObject * Object)
{
	if (Object->GetTag() == m_TagName)
	{
		CBulletBehavior* bullet = Find<CBulletBehavior>(Object->GetBehaviorList());
		m_Life -= bullet->m_Power;
	}
}

//=============================================================================
// ������Â��Ă���
//=============================================================================
void CLifeBehavior::CollisionEnter(CObject * Object)
{

}

//=============================================================================
// ���ꂽ�u��
void CLifeBehavior::CollisionRelease(CObject * Object)
{

}
