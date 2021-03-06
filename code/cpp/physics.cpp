//=============================================================================
// 物理演算基底クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "physics.h"
#include "physicsManager.h"
#include "object.h"

//=============================================================================
// クラスの生成
//=============================================================================
CPhysics::CPhysics()
{
	CPhysicsManager::GetInstance()->SetPhysics(this);
}

//=============================================================================
// クラスの破棄
//=============================================================================
CPhysics::~CPhysics()
{

}

//=============================================================================
// オブジェクト単体を破棄する
//=============================================================================
void CPhysics::Release(void)
{
	CPhysicsManager::GetInstance()->Release(this);
}


