//=============================================================================
// 破壊する
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "destroyBehavior.h"
#include "object.h"

//=============================================================================
// クラスの生成
//=============================================================================
CDestroyBehavior::CDestroyBehavior()
{

}

//=============================================================================
// クラスの破棄
//=============================================================================
CDestroyBehavior::~CDestroyBehavior()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CDestroyBehavior::Init(float TimeLimit)
{
	m_TimeLimit = TimeLimit;
}

//=============================================================================
// 解放
//=============================================================================
void CDestroyBehavior::Uninit(void)
{

}

//=============================================================================
// 更新
//=============================================================================
void CDestroyBehavior::Update(void)
{
	m_TimeLimit -= FrameTime();
	if (m_TimeLimit < 0.0f) m_Object->Destroy();
}	