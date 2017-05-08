//=============================================================================
// リザルト
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "resource.h"
#include "object.h"
#include "scene2D.h"
#include "behavior.h"
#include "sound.h"
#include "joyStick.h"
#include "font.h"
#include "fontBehavior.h"

//=============================================================================
// リザルトの初期化
//=============================================================================
void CTutorial::Init(void)
{
	CObject::Create("object", "object", new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f)), CScene::Create<CScene2D>(new CTransform(), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), (string)"result.jpg", D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f)));

	CObject::Create("object", "object", new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f)), CScene::Create<CScene2D>(new CTransform(), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), (string)"tutorial.png"));

	CFont* Font = (CFont*)CScene::Create<CFont>(new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.92f, 0.0f)), D3DXVECTOR2(300.0f, 80.0f), (string)"Press Enter", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject::Create("", "font", new CTransform(), Font, CBehavior::Create<CFontBehavior>(Font, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.02f));
}

//=============================================================================
// リザルトの解放
//=============================================================================
void CTutorial::Uninit(void)
{
	CSound::GetInstance()->StopSound();
}

//=============================================================================
// リザルトの更新
//=============================================================================
void CTutorial::Update(void)
{
	CInput* pInput = CInput::GetInstance();

	if (CFade::GetInstance()->GetFade() == FADE_NONE)
	{
		if (pInput->GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			CSound::GetInstance()->PlaySound(SOUND_LABEL_SE_000);
			CFade::GetInstance()->Start(new CGame);
		}
	}
}

//=============================================================================
// リザルトの描画
//=============================================================================
void CTutorial::Draw(void)
{
	
}