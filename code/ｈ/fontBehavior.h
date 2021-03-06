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
class CFont;

//=============================================================================
// クラスの定義
//=============================================================================
class CFontBehavior : public CBehavior
{
public:
	//コンストラクタ・デストラクタ
	//=============================================================================
	CFontBehavior();
	~CFontBehavior();

	//継承したすべてのオブジェクトに対して行う関数
	//=============================================================================
	void Init(CFont* Font, D3DXCOLOR color, float interval);
	void Uninit(void);
	void Update(void);

	//設定・取得関数
	//=============================================================================
	CFont* m_Font;
	D3DXCOLOR m_Color;
	float m_Interval;
	float m_Counter;
};