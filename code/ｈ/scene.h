//=============================================================================
// Scene基底クラス
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "sceneManager.h"
#include "transform.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CObject;

//=============================================================================
// クラスの定義
//=============================================================================
class CScene
{
public:
	//コンストラクタ・デストラクタ
	//=============================================================================
	CScene(CTransform* Transform, PRIORITY Priority);
	~CScene();

	//基本関数
	//=============================================================================
	virtual void Init(void) { }			//初期化
	virtual void Uninit(void) = 0;		//解放
	virtual void Update(void) {};		//更新
	virtual void Draw(int num) = 0;		//描画
	virtual void Transformation(void);	//位置修正
	void Begin(void);					//描画開始
	void End(void);						//描画終了

	//設定・取得関数
	//=============================================================================
	CObject* GetObj(void) { return m_Object; };	//オブジェクト
	void SetCull(D3DCULL Cull) { m_Cull = Cull; };	//カリング設定
	void SetLight(bool Light) { m_Light = Light; };	//カリング設定

	//変数
	//=============================================================================
	CTransform* m_Transform;
	CTransform* m_LocalTransform;

	//生成関数
	//=============================================================================
	template<class Class, class ...Argument>
	static CScene* Create(CTransform* transform, Argument ...argument)
	{
		Class* Scene = new Class(transform);
		Scene->Init(argument...);
		return Scene;
	}

protected:
	//変数
	//=============================================================================
	CObject* m_Object;		//オブジェクトタイプ
	D3DCULL m_Cull;			//カリング
	bool m_Light;			//ライティング

private:
	//CSceneManagerで呼び出すための処理(friend)
	//=============================================================================
	PRIORITY m_Priority;
	friend static PRIORITY GetPriority(CScene* Scene) { return Scene->m_Priority; }

	//CObjectで呼び出すための処理(friend)
	//=============================================================================
	friend static void SetObject(CScene* Scene, CObject* Object) { Scene->m_Object = Object; }
};