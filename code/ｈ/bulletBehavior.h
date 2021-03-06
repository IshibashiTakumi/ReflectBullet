//=============================================================================
// プレイヤーの行動
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "behavior.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CObject;

//=============================================================================
// クラスの定義
//=============================================================================
class CBulletBehavior : public CBehavior
{
public:

	//コンストラクタ・デストラクタ
	//=============================================================================
	CBulletBehavior();
	~CBulletBehavior();

	//継承したすべてのオブジェクトに対して行う関数
	//=============================================================================
	void Init(float Angle, float power);
	void Uninit(void);
	void Update(void);

	//衝突
	//=============================================================================
	void CollisionTrigger(CObject* Object);		//衝突時
	void CollisionEnter(CObject* Object);		//衝突継続時
	void CollisionRelease(CObject* Object);		//衝突終了時

	//設定・取得関数
	//=============================================================================
	float m_DirectionRot;
	D3DXVECTOR3 m_Pos;
	float m_Power;
};