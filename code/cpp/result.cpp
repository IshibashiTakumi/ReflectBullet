//=============================================================================
// リザルト
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "resource.h"
#include "object.h"
#include "scene2D.h"
#include "behavior.h"
#include "sound.h"
#include "font.h"
#include "fontBehavior.h"

//=============================================================================
// ゲームの初期化
//=============================================================================
void CResult::Init(void)
{
	CSound::GetInstance()->PlaySound(SOUND_LABEL_BGM002);
	CObject::Create("object", "object", new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f)), CScene::Create<CScene2D>(new CTransform(), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), (string)"result.jpg", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), true));

	CFont* Font = (CFont*)CScene::Create<CFont>(new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.92f, 0.0f)), D3DXVECTOR2(300.0f, 80.0f), (string)"Press Enter", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	CObject::Create("", "font", new CTransform(), Font, CBehavior::Create<CFontBehavior>(Font, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 0.02f));

	CObject::Create("", "font", new CTransform(), CScene::Create<CFont>(new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.2f, 0.0f)), D3DXVECTOR2(600.0f, 130.0f), (string)"Clear Time", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)));

	FILE *fp;

	fp = fopen("./data/time.txt", "r");
	int time = 0;
	if (fp != NULL) fscanf(fp, "TIME = %d", &time);
	fclose(fp);
	Font = (CFont*)CScene::Create<CFont>(new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.55f, 0.0f)), D3DXVECTOR2(280.0f, 190.0f), std::to_string(120 - time), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	CObject::Create("", "font", new CTransform(), Font);
}

//=============================================================================
// ゲームの解放
//=============================================================================
void CResult::Uninit(void)
{
	CSound::GetInstance()->StopSound();
}

//=============================================================================
// ゲームの更新
//=============================================================================
void CResult::Update(void)
{
	CInput* pInput = CInput::GetInstance();

	if (CFade::GetInstance()->GetFade() == FADE_NONE)
	{
		if (pInput->GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			CSound::GetInstance()->PlaySound(SOUND_LABEL_SE_000);
			CFade::GetInstance()->Start(new CTitle);
		}
	}
}

//=============================================================================
// ゲームの描画
//=============================================================================
void CResult::Draw(void)
{
	
}