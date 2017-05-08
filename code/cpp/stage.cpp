//=============================================================================
// ステージ作成
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "stage.h"
#include "resource.h"
#include "object.h"
#include "sceneX.h"
#include "scene3D.h"
#include "scene2D.h"
#include "collision.h"
#include "sceneBox.h"
#include "template.h"
#include "camera.h"
#include "cameraController.h"
#include "cameraManager.h"
#include "time.h"
#include "camera.h"
#include "cameraManager.h"
#include "multipurposeCamera.h"
#include "moveBehavior.h"

#include "playerCamera.h"
#include "pointLight.h"
#include "goalBehavior.h"
#include "sceneWave.h"

#include "collisionCircle.h"
#include "collision2DMap.h"
#include "collisionSquare.h"

#include "manager.h"
#include "complianceCamera.h"

#include "aiBehavior.h"
#include "sceneAlphaMask.h"
#include "lifeBehavior.h"

//=============================================================================
// クラスの生成
//=============================================================================
CStage::CStage(const string& FileName)
{
	Generation();
}

//=============================================================================
// クラスの破棄
//=============================================================================
CStage::~CStage()
{

}

//=============================================================================
// 生成
//=============================================================================
void CStage::Generation(void)
{
	CObject::Create("object", "wall", new CTransform(),
		CCollision::Create<CCollision2DMap>(new CTransform(), false, 100.0f, (string)"./data/stage.csv"));

	int num_x = 0, num_y = 0;
	//ファイルの読み込み
	ifstream file("./data/stage.csv");
	if (file)
	{
		string str;
		while (getline(file, str)) 
		{
			num_x = 0;
			string token;
			istringstream stream(str);
			while (getline(stream, token, ',')) 
			{
				int temp = stoi(token);

				switch (temp)
				{
				case 0:
					CObject::Create("object", "floor", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 0.0f, CHIPSIZE * num_y)),
						CScene::Create<CScene3D>(new CTransform(), D3DXVECTOR2(100.0f, 100.0f), (string)"metal003.jpg", (string)"metal003_normal.jpg", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));
					break;
				case 1:
					CObject::Create("wall", "wall", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 50.0f, CHIPSIZE * num_y)),
						CScene::Create<CSceneBox>(new CTransform(), D3DXVECTOR3(100.0f, 100.0f, 100.0f), (string)"metal005.jpg", (string)"metal005_normal.jpg"),
						CCollision::Create<CCollisionSquare>(new CTransform(), false, D3DXVECTOR2(100.0f, 100.0f)));
					break;
				case 2:
					CObject::Create("", "", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 0.0f, CHIPSIZE * num_y)), CScene::Create<CSceneX>(new CTransform(), (string)"tree.x"));

					CObject::Create("object", "floor", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 0.0f, CHIPSIZE * num_y)),
						CScene::Create<CScene3D>(new CTransform(), D3DXVECTOR2(100.0f, 100.0f), (string)"metal003.jpg", (string)"metal003_normal.jpg", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));
					break;
				case 3:
				{
					CObject* Object = CObject::Create("player", "player", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 50.0f, CHIPSIZE * num_y)),
						CScene::Create<CSceneX>(new CTransform(), (string)"player.x"),
						CCollision::Create<CCollisionCircle>(new CTransform(), true, 50.0f),
						CCollision::Create<CCollisionCircle>(new CTransform(), false, 60.0f),
						CBehavior::Create<CMoveBehavior>((string)"./data/movementMap.csv", 100.0f),
						CBehavior::Create<CLifeBehavior>(100.0f, (string)"enemyBullet"),
						CScene::Create<CSceneAlphaMask>(new CTransform(D3DXVECTOR3(0.0f, 80.0f, 0.0f)), D3DXVECTOR2(70.0f, 70.0f), (string)"gauge.png", (string)"gaugeMask.jpg", 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)));
					CManager::GetInstance()->camera[0]->SetController(CCameraController::Create<CComplianceCamera>(CManager::GetInstance()->camera[0], Object, D3DXVECTOR3(-600.0f, 1000.0f, 0.0f)));

					CObject::Create("object", "floor", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 0.0f, CHIPSIZE * num_y)),
						CScene::Create<CScene3D>(new CTransform(), D3DXVECTOR2(100.0f, 100.0f), (string)"metal003.jpg", (string)"metal003_normal.jpg", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));
				}
					break;
				case 4:
				{
					CObject* Object = CObject::Create("enemy", "enemy", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 50.0f, CHIPSIZE * num_y)),
						CScene::Create<CSceneX>(new CTransform(), (string)"enemy.x"),
						CCollision::Create<CCollisionCircle>(new CTransform(), true, 50.0f),
						CCollision::Create<CCollisionCircle>(new CTransform(), false, 60.0f),
						CBehavior::Create<CAiBehavior>(100.0f),
						CBehavior::Create<CLifeBehavior>(100.0f, (string)"playerBullet"),
						CScene::Create<CSceneAlphaMask>(new CTransform(D3DXVECTOR3(0.0f, 80.0f, 0.0f)), D3DXVECTOR2(70.0f, 70.0f), (string)"gauge.png", (string)"gaugeMask.jpg", 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)));

					CObject::Create("object", "floor", new CTransform(D3DXVECTOR3(CHIPSIZE * num_x, 0.0f, CHIPSIZE * num_y)),
						CScene::Create<CScene3D>(new CTransform(), D3DXVECTOR2(100.0f, 100.0f), (string)"metal003.jpg", (string)"metal003_normal.jpg", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));
				}
					break;
				default:
					break;
				}
				num_x++;
			}
			num_y++;
		}
	}

	CObject::Create("object", "floor", new CTransform(D3DXVECTOR3((CHIPSIZE * 0.5f) * num_x, -1.0f, (CHIPSIZE * 0.5f) * num_y)),
		CScene::Create<CScene3D>(new CTransform(), D3DXVECTOR2((CHIPSIZE * 2) * num_x, (CHIPSIZE * 2) * num_y), (string)"box.jpg", (string)"NormalNone.jpg", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5, 5)));
}