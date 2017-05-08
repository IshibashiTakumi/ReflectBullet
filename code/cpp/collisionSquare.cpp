//=============================================================================
// 円の当たり判定
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "collisionSquare.h"
#include "collisionCircle.h"
#include "collisionDetection.h"
#include "object.h"
#include "renderer.h"

//=============================================================================
// クラスの生成
//=============================================================================
CCollisionSquare::CCollisionSquare(CTransform* Transform, bool Detection) : CCollision(Transform, Detection)
{

}

//=============================================================================
// クラスの破棄
//=============================================================================
CCollisionSquare::~CCollisionSquare()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CCollisionSquare::Init(D3DXVECTOR2 Size)
{
	m_Size = Size;
}

//=============================================================================
// 解放
//=============================================================================
void CCollisionSquare::Uninit(void)
{

}

//=============================================================================
// 描画
//=============================================================================
void CCollisionSquare::Draw(void)
{
	
}

//=============================================================================
// あたり判定の実行部(円とのあたり判定)
//=============================================================================
void CCollisionSquare::DetectionAction(CCollisionSquare * other)
{

}

//=============================================================================
// あたり判定の実行部(2DMapとのあたり判定)
//=============================================================================
void CCollisionSquare::DetectionAction(CCollision2DMap * other)
{

}

//=============================================================================
// あたり判定の実行部(四角とのあたり判定)
//=============================================================================
void CCollisionSquare::DetectionAction(CCollisionCircle * other)
{
	CCollisionDetection::GetInstance()->CircleToSquare(other, this);
}


//=============================================================================
//	四角が四角に交差している場合は真を返し、そうでない場合は偽を返す
//=============================================================================
bool CCollisionSquare::SquareToSquare(CCollisionSquare * Square, CCollisionSquare * _Square)
{
	D3DXVECTOR3 Pos = Square->m_Transform->Pos, _Pos = _Square->m_Transform->Pos;
	D3DXVECTOR2 Size = Square->m_Size * 0.5f, _Size = _Square->m_Size * 0.5f;
	D3DXVECTOR2 Sub;

	if (fabs(Pos.x - _Pos.x) > (Size.x + _Size.x)) return false;
	if (fabs(Pos.z - _Pos.z) > (Size.y + _Size.y)) return false;

	/*Sub.x = (Size.x + _Size.x) - fabs(Pos.x - _Pos.x);
	Sub.y = (Size.y + _Size.y) - fabs(Pos.z - _Pos.z);

	_Square->m_Transform->Pos.x += Sub.x;
	_Square->m_Transform->Pos.z += Sub.y;*/

	return true;
}

//=============================================================================
//	球がSquareに交差している場合は真を返し、そうでない場合は偽を返す
//  球の中心に対するSquare上の最近接点である点も返す
//=============================================================================
bool CCollisionSquare::SquareToCircle(CCollisionSquare * Square, CCollisionCircle * Circle)
{
	D3DXVECTOR2 Point;	//近時点

	//球の中心に対する最近接点であるSquare上にある点Pointを見つける
	ClosestPtPointSquare(Circle->m_Transform->Pos, Square, Point);

	//球とSquareが交差するのは、球の中心から点Pointまでの(平方した)距離が(平方した)球の半径よりも小さい場合
	D3DXVECTOR2 vec = D3DXVECTOR2(Circle->m_Transform->Pos.x, Circle->m_Transform->Pos.z) - Point;
	if (Vec2Length(vec) <= Circle->m_Radius * Circle->m_Radius)
	{
		REJECTION_2D Rejection{ Point, Circle->m_Radius - Vec2LengthSq(vec), atan2f(vec.x, vec.y) + D3DX_PI, Circle };
		Square->m_Rejection2D.push_back(Rejection);
		REJECTION_2D _Rejection{ D3DXVECTOR2(Circle->m_Transform->Pos.x, Circle->m_Transform->Pos.z), Circle->m_Radius - Vec2LengthSq(vec), atan2f(vec.x, vec.y), Square };
		Circle->m_Rejection2D.push_back(_Rejection);
		return true;
	}
	return false;
}

//=============================================================================
//	与えられた点Pointに対して、Square上もしくは中にあるPointの最近接点_Pointを返す
//=============================================================================
void CCollisionSquare::ClosestPtPointSquare(D3DXVECTOR3 &Point, CCollisionSquare * Square, D3DXVECTOR2 &_Point)
{
	float point[2] = { Point.x, Point.z }, _point[2];
	D3DXVECTOR2 size = Square->m_Size * 0.5f;
	D3DXVECTOR2 Min = D3DXVECTOR2(Square->m_Transform->Pos.x, Square->m_Transform->Pos.z) - size;
	D3DXVECTOR2 Max = D3DXVECTOR2(Square->m_Transform->Pos.x, Square->m_Transform->Pos.z) + size;
	float min[2] = { Min.x, Min.y }, max[2] = { Max.x, Max.y };

	//各座標軸に対して、点の座標値がボックスの外側にある場合に
	//ボックスまで点をクランプ、そうでなければそのまま
	for (int count = 0; count < 2; count++)
	{
		if (point[count] < min[count]) point[count] = min[count];	// point[count] = max(point[count], min[i]);
		if (point[count] > max[count]) point[count] = max[count];	// point[count] = min(point[count], max[i]);
		_point[count] = point[count];
	}
	_Point = D3DXVECTOR2(_point[0], _point[1]);
}