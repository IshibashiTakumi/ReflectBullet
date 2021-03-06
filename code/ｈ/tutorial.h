//=============================================================================
// リザルト
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CTutorial : public CMode
{
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};