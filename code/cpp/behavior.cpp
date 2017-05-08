//=============================================================================
// Behavior基底クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "behavior.h"
#include "behaviorManager.h"
#include "object.h"

//=============================================================================
// クラスの生成
//=============================================================================
CBehavior::CBehavior()
{
	CBehaviorManager::GetInstance()->SetBehavior(this);
}
//=============================================================================
// クラスの破棄
//=============================================================================
CBehavior::~CBehavior()
{

}

//=============================================================================
// オブジェクト単体を破棄する
//=============================================================================
void CBehavior::Release(void)
{
	CBehaviorManager::GetInstance()->Release(this);
}
