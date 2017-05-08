//=============================================================================
// 当たり判定実行クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CCollision;
class CCollisionCircle;
class CCollision2DMap;
class CCollisionSquare;

//=============================================================================
// クラスの定義
//=============================================================================
class CCollisionDetection
{
public:
	//インスタンスを返す
	static CCollisionDetection* GetInstance() { return Instance == NULL ? Instance = new CCollisionDetection() : Instance; };

	void CollisionDetection(void);	//あたり判定管理
	void CollisionState(CCollision* Collision);
	bool CollisionOverlap(CCollision* list, std::list<CCollision*> _list);		//衝突重複判定
	bool Overlap(CCollision* Collision, CCollision* _Collision);				//重複判断

	void CircleToCircle(CCollisionCircle* Circle, CCollisionCircle* _Circle);	//円同士のあたり判定
	void CircleToSquare(CCollisionCircle* Circle, CCollisionSquare* Square);	//円と四角のあたり判定
	void SquareToSquare(CCollisionSquare* Square, CCollisionSquare* _Square);	//四角同士のあたり判定
	//void SphereToAabb(CCollisionSphere* Sphere, CCollisionAabb* Aabb);		//SphereとAabbのあたり判定
	//void AabbToAabb(CCollisionAabb* Aabb, CCollisionAabb* _Aabb);		//SphereとAabbのあたり判定

private:
	static  CCollisionDetection* Instance;	//インスタンス

	CCollisionDetection();
	~CCollisionDetection();

	void Rejection(CCollision* Collision);

	void HitCollision(CCollision* Collision, CCollision* _Collision);	//コリジョンとコリジョンが当たった時の処理
};
