//=============================================================================
// AIの攻撃
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "aiStateAttack.h"
#include "renderer.h"
#include "object.h"
#include "aiStateStop.h"
#include "aiStateMovement.h"
#include "destroyBehavior.h"
#include "bulletBehavior.h"
#include "collisionCircle.h"
#include "sceneX.h"
#include "sound.h"

//=============================================================================
// クラスの生成
//=============================================================================
CAiStateAttack::CAiStateAttack() : CAiState()
{
	
}

//=============================================================================
// クラスの破棄
//=============================================================================
CAiStateAttack::~CAiStateAttack()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CAiStateAttack::Init(CObject* Object, CObject* _Object, vector<vector<int>>* List, float Size, float interval)
{
	m_Object = Object;
	m_Target = _Object;
	m_Size = Size;
	m_ThreatLevelMap = List;
	m_Interval = interval;
	m_IntervalCount = interval;
}

//=============================================================================
// 解放
//=============================================================================
void CAiStateAttack::Uninit(void)
{

}

//=============================================================================
// 更新
//=============================================================================
void CAiStateAttack::Update(void)
{
	m_IntervalCount += FrameTime();
	if (m_IntervalCount >= m_Interval)
	{
		CSound::GetInstance()->PlaySound(SOUND_LABEL_SE_001);
		m_IntervalCount = 0;
		float angle = ((D3DX_PI * 2) / 6);
		for (int count = 0; count < 6; count++)
		{
			CObject::Create("bullet", "enemyBullet", new CTransform(m_Object->m_Transform->Pos + D3DXVECTOR3(sinf(angle * count) * 80.0f, 0.0f, cosf(angle * count) * 80.0f)),
				CScene::Create<CSceneX>(new CTransform(), (string)"enemybullet.x"),
				CCollision::Create<CCollisionCircle>(new CTransform(), true, 10.0f),
				CBehavior::Create<CBulletBehavior>(angle * count, 3.0f),
				CBehavior::Create<CDestroyBehavior>(6.0f));
		}
	}

	int x, y;
	x = m_Object->m_Transform->Pos.x / m_Size;
	y = m_Object->m_Transform->Pos.z / m_Size;

	if ((*m_ThreatLevelMap)[y][x] > 12)
	{
		CAiState::Change(this, CAiState::Create<CAiStateStop>(m_Object, m_Target, m_ThreatLevelMap, m_Size));
	}
	else if ((*m_ThreatLevelMap)[y][x] > 4)
	{
		CAiState::Change(this, CAiState::Create<CAiStateMovement>(m_Object, m_Target, m_ThreatLevelMap, m_Size));
	}
	
}