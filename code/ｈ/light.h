//=============================================================================
// Lightの基底クラス
//=============================================================================
#pragma once

//=============================================================================
// クラスの定義
//=============================================================================
class CLight
{
public:
	//コンストラクタ・デストラクタ
	//=============================================================================
	CLight();
	~CLight();

	//基本
	//=============================================================================
	virtual void Init(void) {};		//初期化
	virtual void Uninit(void) {};	//解放
	virtual void Update(void) {};	//更新
	virtual void Draw(void) {};		//描画

protected:
	D3DLIGHT9 m_Light; //ライト情報
};