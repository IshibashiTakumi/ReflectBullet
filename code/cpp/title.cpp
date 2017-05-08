//=============================================================================
// Title
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "tutorial.h"
#include "resource.h"
#include "object.h"
#include "scene.h"
#include "scene2D.h"
#include "behavior.h"
#include "sound.h"
#include "font.h"
#include "fontBehavior.h"

//=============================================================================
// タイトルの初期化
//=============================================================================
void CTitle::Init(void)
{
	CSound::GetInstance()->PlaySound(SOUND_LABEL_BGM000);
	CObject::Create("object", "object", new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f)), CScene::Create<CScene2D>(new CTransform(), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), (string)"result.jpg", D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f), true));
	CObject::Create("", "font", new CTransform(), CScene::Create<CFont>(new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f)), D3DXVECTOR2(700.0f, 130.0f), (string)"ReflectBullet", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));

	CFont* Font = (CFont*)CScene::Create<CFont>(new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f, 0.0f)), D3DXVECTOR2(400.0f, 100.0f), (string)"Press Enter", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject::Create("", "font", new CTransform(), Font, CBehavior::Create<CFontBehavior>(Font, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.02f));
}

//=============================================================================
// タイトルの解放
//=============================================================================
void CTitle::Uninit(void)
{
	
}

//=============================================================================
// タイトルの更新
//=============================================================================
void CTitle::Update(void)
{
	CInput* pInput = CInput::GetInstance();

	if (CFade::GetInstance()->GetFade() == FADE_NONE)
	{
		if (pInput->GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			CSound::GetInstance()->PlaySound(SOUND_LABEL_SE_000);
			CFade::GetInstance()->Start(new CTutorial);
		}
	}
}

//=============================================================================
// タイトルの描画
//=============================================================================
void CTitle::Draw(void)
{
	
}