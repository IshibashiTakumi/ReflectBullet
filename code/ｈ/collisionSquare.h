//=============================================================================
// 円の当たり判定
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "collision.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SPHERE_COLOR (D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f))

//=============================================================================
// 前方宣言
//=============================================================================
class CCollision2DMap;
class CCollisionCircle;

//=============================================================================
// クラスの定義
//=============================================================================
class CCollisionSquare : public CCollision
{
public:

	//コンストラクタ・デストラクタ
	//=============================================================================
	CCollisionSquare(CTransform* Transform, bool Detection);
	~CCollisionSquare();

	//基本的な関数の宣言
	//=============================================================================
	void Init(D3DXVECTOR2 Size);
	void Uninit(void);
	void Draw(void);

	//ダブルディスパッチに必要な宣言
	//=============================================================================
	virtual void CollisionDetection(CCollision* other) { other->DetectionAction(this); }

	static bool SquareToSquare(CCollisionSquare * Square, CCollisionSquare * _Square);
	static bool SquareToCircle(CCollisionSquare * Square, CCollisionCircle * Circle);
	static void ClosestPtPointSquare(D3DXVECTOR3 &Point, CCollisionSquare * Square, D3DXVECTOR2 &_Point);
	//static bool SquareDirection(D3DXVECTOR3 &Point, CCollisionSquare * Square);

	//変数
	//=============================================================================
	D3DXVECTOR2 m_Size;	//マスサイズ

protected:

	////ダブルディスパッチの実行部
	////=============================================================================
	virtual void DetectionAction(CCollisionSquare* other);
	virtual void DetectionAction(CCollision2DMap* other);
	virtual void DetectionAction(CCollisionCircle* other);
};