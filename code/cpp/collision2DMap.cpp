//=============================================================================
// 2DMapの当たり判定
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "collision2DMap.h"
#include "collisionDetection.h"
#include "collisionCircle.h"
#include "object.h"
#include "renderer.h"

//=============================================================================
// クラスの生成
//=============================================================================
CCollision2DMap::CCollision2DMap(CTransform* Transform, bool Detection) : CCollision(Transform, Detection)
{

}

//=============================================================================
// クラスの破棄
//=============================================================================
CCollision2DMap::~CCollision2DMap()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CCollision2DMap::Init(float Size, string& FileName)
{
	m_Size = Size;

	int temp;
	m_Width = 0, m_Height = 0;
	//ファイルの読み込み
	ifstream file(FileName);
	if (file)
	{
		string str;
		while (getline(file, str))
		{
			m_Width = 0;
			string token;
			istringstream stream(str);
			while (getline(stream, token, ','))
			{
				temp = stoi(token);
				m_Map.push_back(temp);
				m_Width++;
			}
			m_Height++;
		}
	}
}

//=============================================================================
// 解放
//=============================================================================
void CCollision2DMap::Uninit(void)
{

}

//=============================================================================
// 描画
//=============================================================================
void CCollision2DMap::Draw(void)
{
	
}

//=============================================================================
// あたり判定の実行部(2DMapとのあたり判定)
//=============================================================================
void CCollision2DMap::DetectionAction(CCollision2DMap * other)
{

}

//=============================================================================
// あたり判定の実行部(円とのあたり判定)
//=============================================================================
void CCollision2DMap::DetectionAction(CCollisionCircle * other)
{

}


//=============================================================================
//	球がAabbに交差している場合は真を返し、そうでない場合は偽を返す
//  球の中心に対するAabb上の最近接点である点も返す
//=============================================================================
bool CCollision2DMap::MapToCircle(CCollision2DMap * Map, CCollisionCircle * Circle, D3DXVECTOR3 &Point)
{
	//球の中心に対する最近接点であるAabb上にある点Pointを見つける
	int num = 0;
	D3DXVECTOR2 Pos;
	for each (auto list in Map->m_Map)
	{
		/*if (SquareToCircle(num, list, Map->m_Size, Circle, Pos))
		{
			NEAR_POINT Near = { Pos, Circle };
			Map->m_Rejection2D.push_back(Near);
		}*/
		num++;
	}

	//球とAabbが交差するのは、球の中心から点Pointまでの(平方した)距離が(平方した)球の半径よりも小さい場合
	D3DXVECTOR3 vec = Point - Circle->m_Transform->Pos;
	return Vec3Length(vec) <= Circle->m_Radius * Circle->m_Radius;
}

//=============================================================================
//	与えられた点Pointに対して、Aabb上もしくは中にあるPointの最近接点_Pointを返す
//=============================================================================
void CCollision2DMap::SquareToCircle(int num, int MapState, float Size, CCollisionCircle * Circle, D3DXVECTOR2 &Point)
{
	//float point[2] = { Point.x, Point.y }, _point[2];
	//D3DXVECTOR2 Min = Aabb->m_Transform->Pos.x + Aabb->m_Min.x, Max = Aabb->m_Transform->Pos + Aabb->m_Max;
	//float min[3] = { Min.x, Min.y, Min.z }, max[3] = { Max.x, Max.y, Max.z };

	////各座標軸に対して、点の座標値がボックスの外側にある場合に
	////ボックスまで点をクランプ、そうでなければそのまま
	//for (int count = 0; count < 2; count++)
	//{
	//	if (point[count] < min[count]) point[count] = min[count];	// point[count] = max(point[count], min[i]);
	//	if (point[count] > max[count]) point[count] = max[count];	// point[count] = min(point[count], max[i]);
	//	_point[count] = point[count];
	//}
	//Point = D3DXVECTOR2(_point[0], _point[1]);
}
