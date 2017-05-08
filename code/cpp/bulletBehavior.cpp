//=============================================================================
// プレイヤーの行動
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "bulletBehavior.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "inputKeyboard.h"
#include "camera.h"
#include "cameraManager.h"
#include "object.h"
#include "collision.h"
#include "joyStick.h"
#include "mode.h"
#include "fade.h"

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// クラスの生成
//=============================================================================
CBulletBehavior::CBulletBehavior() : CBehavior()
{
	
}

//=============================================================================
// クラスの破棄
//=============================================================================
CBulletBehavior::~CBulletBehavior()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CBulletBehavior::Init(float Angle, float power)
{
	m_DirectionRot = Angle;
	m_Power = power;
}

//=============================================================================
// 解放
//=============================================================================
void CBulletBehavior::Uninit(void)
{

}

//=============================================================================
// 更新
//=============================================================================
void CBulletBehavior::Update(void)
{
	CInputKeyboard* Input = CInput::GetInstance()->GetKeyboard();

	D3DXVECTOR3 Pos, Rot;
	Pos = m_Object->m_Transform->Pos;
	Rot = m_Object->m_Transform->Rot;

	m_Pos = Pos;
	Rot.y = m_DirectionRot;

	Pos.x += sinf(Rot.y) * 10;
	Pos.z += cosf(Rot.y) * 10;

	m_Object->m_Transform->Pos = Pos;
	m_Object->m_Transform->Rot = Rot;
}

//=============================================================================
// 当たった瞬間
//=============================================================================
void CBulletBehavior::CollisionTrigger(CObject * Object)
{
	if (Object->GetTag() == "wall")
	{
		D3DXVECTOR2 pos, vec, _vec, vector;
		pos = D3DXVECTOR2(m_Object->m_Transform->Pos.x, m_Object->m_Transform->Pos.z);
		for each (auto list in Object->GetCollisionList())
		{
			for each (auto _list in list->m_Rejection2D)
			{
				vec = Vec2Nor(D3DXVECTOR2(m_Pos.x, m_Pos.z) - _list.Pos);
				_vec = Vec2Nor(pos - D3DXVECTOR2(m_Pos.x, m_Pos.z));
				vector = _vec + (2 * vec);
				m_DirectionRot = atan2f(vector.x, vector.y);
				break;
			}
		}
	}
	else if (Object->GetTag() == "enemy")
	{
		m_Object->Destroy();
	}
	else if (Object->GetTag() == "player")
	{
		m_Object->Destroy();
	}
}

//=============================================================================
// 当たりつづけている
//=============================================================================
void CBulletBehavior::CollisionEnter(CObject * Object)
{

}

//=============================================================================
// 離れた瞬間
//=============================================================================
void CBulletBehavior::CollisionRelease(CObject * Object)
{
	
}
