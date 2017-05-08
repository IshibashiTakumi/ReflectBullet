//=============================================================================
// 当たり判定基底クラス
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "transform.h"

//=============================================================================
// 構造体
//=============================================================================
//typedef struct
//{
//	D3DXVECTOR2 Pos;				//近時点
//	float Length;					//排斥長さ
//	float Angle;					//排斥角度
//	class CCollision* Collision;	//対象
//}REJECTION_2D;

typedef struct
{
	D3DXVECTOR2 Pos;				//近時点
	float Length;					//排斥長さ
	float Angle;					//排斥角度
	class CCollision* Collision;	//対象
}REJECTION_2D;

//=============================================================================
// 前方宣言
//=============================================================================
class CCollision2DMap;
class CCollisionCircle;
class CCollisionSquare;
class CObject;

//=============================================================================
// クラスの定義
//=============================================================================
class CCollision
{
public:

	//コンストラクタ・デストラクタ
	//=============================================================================
	CCollision(CTransform* Transform, bool Detection);
	~CCollision();

	//基本関数
	//=============================================================================
	virtual void Init(void) { };		//初期化
	virtual void Uninit(void) = 0;		//解放
	virtual void Update(void);			//更新
	virtual void Draw(void) = 0;		//描画
	virtual void Transformation(void);	//位置修正
	
	//ダブルディスパッチに必要な宣言
	//=============================================================================
	virtual void CollisionDetection(CCollision* other) = 0;
	virtual void DetectionAction(CCollision2DMap* other) = 0;
	virtual void DetectionAction(CCollisionCircle* other) = 0;
	virtual void DetectionAction(CCollisionSquare* other) = 0;

	//設定・取得関数
	//=============================================================================
	CObject* GetObj(void) { return m_Object; }											//オブジェクト
	bool GetDetection(void) { return m_Detection; }										//検出
	void SetList(CCollision* Collision) { return m_List.push_back(Collision); }			//衝突判定用リスト
	void SetOldList(CCollision* Collision) { return m_OldList.push_back(Collision); }	//衝突判定用リスト
	static list<CCollision*> GetList(CCollision* Collision) { return Collision->m_List; }			//衝突判定用リスト
	static list<CCollision*> GetOldList(CCollision* Collision) { return Collision->m_OldList; }		//衝突判定用リスト

	//変数
	//=============================================================================
	CTransform* m_Transform;
	CTransform* m_LocalTransform;
	list<REJECTION_2D> m_Rejection2D;	//排斥処理情報2D

	//生成関数
	//=============================================================================
	template<class Class, class ...Argument>
	static CCollision* Create(CTransform* transform, bool Detection, Argument ...argument)
	{
		Class* Collision = new Class(transform, Detection);
		Collision->Init(argument...);
		return Collision;
	}

	template<class Class, class ...Argument>
	static CCollision* _Create(CTransform* transform, bool Detection, Argument*... argument)
	{
		Class* Collision = new Class(transform, Detection);
		Collision->Init(argument...);
		return Collision;
	}

protected:
	//変数
	//=============================================================================
	CObject* m_Object;					//オブジェクト情報
	bool m_Detection;					//検出実行判定

	void CollisionSwap(std::list<CCollision*>* list, std::list<CCollision*>* _list);

	//リストポインタ
	//=============================================================================
	list<CCollision*> m_List;		//衝突判定用リスト情報
	list<CCollision*> m_OldList;	//衝突判定用リスト情報
	unordered_map<CCollision*, CCollision*> m_Search;			//検索用

private:
	//CObjectで呼び出すための処理(friend)
	//=============================================================================
	friend static void SetObject(CCollision* Collision, CObject* Object) { Collision->m_Object = Object; }
};