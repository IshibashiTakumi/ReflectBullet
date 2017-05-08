//=============================================================================
// ボックス描画
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "sceneBox.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "camera.h"
#include "cameraManager.h"
#include "input.h"
#include "inputKeyboard.h"
#include "shaderManager.h"
#include "shader.h"
#include "shader3D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SIZE_MAX (50.0f)

//=============================================================================
// オブジェクトクラスの生成
//=============================================================================
CSceneBox::CSceneBox(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_VtxBuff = NULL;	//頂点バッファポインタの初期化
	m_Texture = NULL;	//テクスチャポインタの初期化
}

//=============================================================================
// オブジェクトクラスの破棄
//=============================================================================
CSceneBox::~CSceneBox()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CSceneBox::Init(D3DXVECTOR3 Size, string& Texture, string& NormalMap, D3DXCOLOR color)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//レンダラーの取得

	//テクスチャの読み込み
	m_Texture = *CResource::Get<CTexture>(Texture);
	m_NormalMap = *CResource::Get<CTexture>(NormalMap);

	//頂点ブッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (VERTEX_NUM * 6),
		D3DUSAGE_WRITEONLY, //確保するバッファサイズ
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED, //使用する頂点フォーマット
		&m_VtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	for (int nCnt = 0; nCnt < (VERTEX_NUM * 6); nCnt++)
	{
		pVtx[nCnt].col = color;
	}

	D3DXVECTOR3 _Size = D3DXVECTOR3(Size.x * 0.5f, Size.y * 0.5f, Size.z * 0.5f);

	//上面
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, _Size.z / SIZE_MAX);
	pVtx[3].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.z / SIZE_MAX);

	pVtx[0].pos = D3DXVECTOR3(_Size.x, _Size.y, -_Size.z);
	pVtx[1].pos = D3DXVECTOR3(-_Size.x, _Size.y, -_Size.z);
	pVtx[2].pos = D3DXVECTOR3(_Size.x, _Size.y, _Size.z);
	pVtx[3].pos = D3DXVECTOR3(-_Size.x, _Size.y, _Size.z);

	for (int count = 0; count < VERTEX_NUM; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//下面
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, _Size.z / SIZE_MAX);
	pVtx[7].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.z / SIZE_MAX);

	pVtx[4].pos = D3DXVECTOR3(_Size.x, -_Size.y, _Size.z);
	pVtx[5].pos = D3DXVECTOR3(-_Size.x, -_Size.y, _Size.z);
	pVtx[6].pos = D3DXVECTOR3(_Size.x, -_Size.y, -_Size.z);
	pVtx[7].pos = D3DXVECTOR3(-_Size.x, -_Size.y, -_Size.z);

	for (int count = VERTEX_NUM; count < VERTEX_NUM * 2; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//左面
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[11].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[8].pos = D3DXVECTOR3(-_Size.x, _Size.y, _Size.z);
	pVtx[9].pos = D3DXVECTOR3(-_Size.x, _Size.y, -_Size.z);
	pVtx[10].pos = D3DXVECTOR3(-_Size.x, -_Size.y, _Size.z);
	pVtx[11].pos = D3DXVECTOR3(-_Size.x, -_Size.y, -_Size.z);

	for (int count = VERTEX_NUM * 2; count < VERTEX_NUM * 3; count++) pVtx[count].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	//前面
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[15].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[12].pos = D3DXVECTOR3(_Size.x, _Size.y, _Size.z);
	pVtx[13].pos = D3DXVECTOR3(-_Size.x, _Size.y, _Size.z);
	pVtx[14].pos = D3DXVECTOR3(_Size.x, -_Size.y, _Size.z);
	pVtx[15].pos = D3DXVECTOR3(-_Size.x, -_Size.y, _Size.z);

	for (int count = VERTEX_NUM * 3; count < VERTEX_NUM * 4; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//右面
	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[19].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[16].pos = D3DXVECTOR3(_Size.x, _Size.y, -_Size.z);
	pVtx[17].pos = D3DXVECTOR3(_Size.x, _Size.y, _Size.z);
	pVtx[18].pos = D3DXVECTOR3(_Size.x, -_Size.y, -_Size.z);
	pVtx[19].pos = D3DXVECTOR3(_Size.x, -_Size.y, _Size.z);

	for (int count = VERTEX_NUM * 4; count < VERTEX_NUM * 5; count++) pVtx[count].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//後ろ面
	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[21].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[23].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[20].pos = D3DXVECTOR3(-_Size.x, _Size.y, -_Size.z);
	pVtx[21].pos = D3DXVECTOR3(_Size.x, _Size.y, -_Size.z);
	pVtx[22].pos = D3DXVECTOR3(-_Size.x, -_Size.y, -_Size.z);
	pVtx[23].pos = D3DXVECTOR3(_Size.x, -_Size.y, -_Size.z);

	for (int count = VERTEX_NUM * 5; count < VERTEX_NUM * 6; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	m_VtxBuff->Unlock();
}

//=============================================================================
// 解放
//=============================================================================
void CSceneBox::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//頂点バッファの解放
}

//=============================================================================
// 描画
//=============================================================================
void CSceneBox::Draw(int num)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得 
	CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();		//カメラの取得
	CShaderManager::GetInstance()->Find<CShader3D>();	//シェーダの取得

	//ワールドマトリックスの設定
	SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);

	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_3D)); //データ間隔

	pDevice->SetFVF(FVF_VERTEX_3D);	//頂点フォーマットの設定

	CShaderManager::GetInstance()->Begin<CShader3D>(num, m_Transform->mtxWorld, pCamera->m_MtxView, pCamera->m_MtxProjection, m_Texture, m_NormalMap);

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (4 * nCnt), 2); 
	}

	CShaderManager::GetInstance()->End();
}

