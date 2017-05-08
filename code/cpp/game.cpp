//=============================================================================
// Game
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "resource.h"
#include "object.h"
#include "objectManager.h"
#include "scene2D.h"
#include "scene3D.h"
#include "collision.h"
#include "sceneBox.h"
#include "camera.h"
#include "cameraController.h"
#include "cameraOperation.h"
#include "cameraManager.h"
#include "template.h"
#include "joyStick.h"
#include "pointLight.h"
#include "moveBehavior.h"
#include "multipurposeCamera.h"
#include "destroyBehavior.h"
#include "stage.h"
#include "time.h"
#include "sound.h"
#include "deferredShader.h"
#include "zTexRenderer.h"

//=============================================================================
// ゲームの初期化
//=============================================================================
void CGame::Init(void)
{
	CSound::GetInstance()->PlaySound(SOUND_LABEL_BGM001);

	CTemplate::Create<CStage>("");

	m_Time = (CTime*)CScene::Create<CTime>(new CTransform(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.06f, 0.0f)), 3, 120, D3DXVECTOR2(100.0f, 50.0f), (string)"number000.png");
	CObject::Create("", "time", new CTransform(), m_Time);
}

//=============================================================================
// ゲームの解放
//=============================================================================
void CGame::Uninit(void)
{
	CSound::GetInstance()->StopSound();
	CManager::GetInstance()->camera[0]->SetController(CTemplate::Create<CCameraOperation>(CManager::GetInstance()->camera[0]));

	FILE *fp;
	fp = fopen("./data/time.txt", "w");

	if (fp != NULL)
	{
		fprintf(fp, "TIME = %d", (int)m_Time->GetTime());
	}

	fclose(fp);
}

//=============================================================================
// ゲームの更新
//=============================================================================
void CGame::Update(void)
{
	CInput* pInput = CInput::GetInstance();

	if (CFade::GetInstance()->GetFade() == FADE_NONE)
	{
		if(CObjectManager::GetInstance()->FindTag("enemy").size() == 0)
		{
			CFade::GetInstance()->Start(new CResult);
		}
		else if (CObjectManager::GetInstance()->FindTag("player").size() == 0)
		{
			CFade::GetInstance()->Start(new CTitle);
		}
	}
}

//=============================================================================
// ゲームの描画
//=============================================================================
void CGame::Draw(void)
{

}