//=============================================================================
// 2DMapの当たり判定
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
// 構造体
//=============================================================================
typedef struct
{
	int Number;
	class CCollision* Collision;	//対象
}MAP_PANEL;

//=============================================================================
// 前方宣言
//=============================================================================
class CCollisionCircle;

//=============================================================================
// クラスの定義
//=============================================================================
class CCollision2DMap : public CCollision
{
public:

	//コンストラクタ・デストラクタ
	//=============================================================================
	CCollision2DMap(CTransform* Transform, bool Detection);
	~CCollision2DMap();

	//基本的な関数の宣言
	//=============================================================================
	void Init(float Size, string& FileName);
	void Uninit(void);
	void Draw(void);

	//ダブルディスパッチに必要な宣言
	//=============================================================================
	virtual void CollisionDetection(CCollision* other) { other->DetectionAction(this); }

	bool MapToCircle(CCollision2DMap* Map, CCollisionCircle* Circle, D3DXVECTOR3 &Point);
	void SquareToCircle(int num, int MapState, float Size, CCollisionCircle * Circle, D3DXVECTOR2 &Point);

	//変数
	//=============================================================================
	float m_Size;	//マスサイズ
	int m_Width, m_Height;
	list<int> m_Map;
	list<MAP_PANEL> m_MapPanel;

protected:

	//ダブルディスパッチの実行部
	//=============================================================================
	virtual void DetectionAction(CCollision2DMap* other);
	virtual void DetectionAction(CCollisionCircle* other);
	virtual void DetectionAction(CCollisionSquare* other) {};
};