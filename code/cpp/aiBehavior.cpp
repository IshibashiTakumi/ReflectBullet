//=============================================================================
// プレイヤーの行動
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "aiBehavior.h"
#include "renderer.h"
#include "objectManager.h"
#include "object.h"
#include "aiState.h"
#include "aiStateStop.h"
#include "aiStateMovement.h"
#include "aiStateAttack.h"

#include "moveBehavior.h"

//=============================================================================
// グローバル変数
//=============================================================================
#define PLAYER_MOVE ( 2.0f )	//プレイヤーの移動量
#define PLAYER_RESISTANCE ( 0.2f )	//プレイヤーの移動量抵抗

//=============================================================================
// クラスの生成
//=============================================================================
CAiBehavior::CAiBehavior() : CBehavior()
{

}

//=============================================================================
// クラスの破棄
//=============================================================================
CAiBehavior::~CAiBehavior()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CAiBehavior::Init(float Size)
{
	m_Size = Size;
	m_State = AISTATE_NONE;
}

//=============================================================================
// 解放
//=============================================================================
void CAiBehavior::Uninit(void)
{
	m_AiState->Uninit();
	delete m_AiState;
}

//=============================================================================
// 更新
//=============================================================================
void CAiBehavior::Update(void)
{
	if (m_State == AISTATE_NONE)
	{
		m_Player = CObjectManager::GetInstance()->FindName("player");
		CMoveBehavior* MoveBehavior = CAiBehavior::Find<CMoveBehavior>(m_Player->GetBehaviorList());
		MoveBehavior->ThreatLevelMap();
		m_AiState = CAiState::Create<CAiStateStop>(m_Object, m_Player , &MoveBehavior->m_ThreatLevelMap, m_Size);
		m_State = AISTATE_STOP;
	}
	m_AiState->Update();
}

//=============================================================================
// 当たった瞬間
//=============================================================================
void CAiBehavior::CollisionTrigger(CObject * Object)
{
	
}

//=============================================================================
// 当たりつづけている
//=============================================================================
void CAiBehavior::CollisionEnter(CObject * Object)
{

}

//=============================================================================
// 離れた瞬間
void CAiBehavior::CollisionRelease(CObject * Object)
{

}
