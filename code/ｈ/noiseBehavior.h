//=============================================================================
// ノイズの行動
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
class CNoiseBehavior : public CBehavior
{
public:

	//コンストラクタ・デストラクタ
	//=============================================================================
	CNoiseBehavior();
	~CNoiseBehavior();

	//継承したすべてのオブジェクトに対して行う関数
	//=============================================================================
	void Init(void);
	void Uninit(void);
	void Update(void);

	//衝突
	//=============================================================================
	void CollisionTrigger(CObject* Object);		//衝突時
	void CollisionEnter(CObject* Object);		//衝突継続時
	void CollisionRelease(CObject* Object);		//衝突終了時

	//設定・取得関数
	//=============================================================================


private:
	//変数
	//=============================================================================
	float m_Angle;
	ID3DXEffect *m_Effect;
};