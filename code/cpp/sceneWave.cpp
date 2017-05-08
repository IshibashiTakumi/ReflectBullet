//=============================================================================
// 3D描画
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "sceneWave.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "camera.h"
#include "cameraManager.h"
#include "object.h"
#include "objectManager.h"

//=============================================================================
// クラスの生成
//=============================================================================
CSceneWave::CSceneWave(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_VtxBuff = NULL;	//頂点バッファポインタの初期化
	m_Texture = NULL;	//テクスチャポインタの初期化
}

//=============================================================================
// クラスの破棄
//=============================================================================
CSceneWave::~CSceneWave()
{

}

//=============================================================================
//  初期化
//=============================================================================
void CSceneWave::Init(D3DXVECTOR2 Size, string& TexName, D3DXCOLOR color, D3DXVECTOR2 tex)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance() -> GetDevice( ); //デバイスの取得 

	//テクスチャの読み込み
	m_Texture = *CResource::Get<CTexture>(TexName);

	//頂点ブッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_NUM,
		D3DUSAGE_WRITEONLY, //確保するバッファサイズ
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED, //使用する頂点フォーマット
		&m_VtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	m_VtxBuff -> Lock( 0, 0, ( void** )&pVtx, 0 ); //頂点情報へのポインタを取得

	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2(tex.x, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, tex.y);
	pVtx[ 3 ].tex = D3DXVECTOR2(tex.x, tex.y);

	float Width = Size.x * 0.5f, Depth = Size.y * 0.5f;
	pVtx[ 0 ].pos = D3DXVECTOR3( -Width, 0, Depth);
	pVtx[ 1 ].pos = D3DXVECTOR3(Width, 0, Depth);
	pVtx[ 2 ].pos = D3DXVECTOR3( -Width, 0, -Depth);
	pVtx[ 3 ].pos = D3DXVECTOR3(Width, 0, -Depth);

	for (int Count = 0; Count < VERTEX_NUM; Count++)
	{
		pVtx[Count].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[Count].col = color;
	}

	m_VtxBuff -> Unlock( );
}

//=============================================================================
// 解放
//=============================================================================
void CSceneWave::Uninit( void )
{
	ResourceRelease(m_VtxBuff);	//頂点バッファの解放 
}

//=============================================================================
// 描画
//=============================================================================
void CSceneWave::Draw(int num)
{
	
	//LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance() -> GetDevice( ); //デバイスの取得 

	////ワールドマトリックスの設定
	//SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);
	//
	////ワールドマトッリクスの設定
	//pDevice -> SetTransform( D3DTS_WORLD, &m_Transform->mtxWorld );

	////頂点バッファをデータストリームにバインド
	//pDevice -> SetStreamSource( 0,
	//							m_VtxBuff,
	//							0,
	//							sizeof( VERTEX_3D ) ); //データ間隔

	////頂点フォーマットの設定
	//pDevice -> SetFVF( FVF_VERTEX_3D );

	////テクスチャの設定
	//pDevice -> SetTexture( 0, m_Texture );

	//pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, //プリミティブの種類
	//							0, //最初の頂点のインデックス
	//							2 ); //描画するプリミティブ数








	//LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 
	//ID3DXEffect* pEffect = CRenderer::GetInstance()->GetEffect();
	//CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();

	//D3DXMATRIX mtxScl, mtxRot, mtxTrans;

	////ワールドマトリックスの設定
	//SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);

	////ワールドマトッリクスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_Transform->mtxWorld);

	////頂点バッファをデータストリームにバインド
	//pDevice->SetStreamSource(0,
	//	m_VtxBuff,
	//	0,
	//	sizeof(VERTEX_3D)); //データ間隔

	//						//頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_3D);

	//// エフェクト設定
	//pEffect->SetMatrix("g_world", &m_Transform->mtxWorld);
	//pEffect->SetMatrix("g_view", &pCamera->m_MtxView);
	//pEffect->SetMatrix("g_proj", &pCamera->m_MtxProjection);

	//pEffect->SetTexture("g_texture", m_Texture);

	//for each (auto list in CScreenTexManager::GetInstance()->GetList())
	//{
	//	pEffect->SetTexture("g_shadowMap", list->GetTexture());
	//}

	//LPDIRECT3DTEXTURE9 Texture = *CResource::Get<CTexture>("NormalMap.jpg");
	//pEffect->SetTexture("g_NormalTex", Texture);
	//pEffect->SetTexture("g_SpecularTex", *CResource::Get<CTexture>("Specular.jpg"));

	//D3DXVECTOR3 Vec[3] = { D3DXVECTOR3(1.0f, -1.0f, -0.5f) , D3DXVECTOR3(-1.0f, 1.0f, 0.65f) , D3DXVECTOR3(0.0f, 0.0f, -0.5f) };
	//m_color[0] = m_color[1] = m_color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//D3DXCOLOR(0.05f, 0.05f, 0.05f, 1.0f)

	//static float texmove = 0.0f;
	//texmove += 0.005;
	//pEffect->SetFloatArray("g_texmove", &texmove, 1);

	//pEffect->SetFloatArray("g_lightVec", (float*)Vec, 9);
	//pEffect->SetFloatArray("g_color", (float*)m_color, 12);
	//pEffect->SetFloatArray("g_CameraPos", (float*)pCamera->m_PosV, 3);

	//D3DXVECTOR2 fog;
	//fog.x = pCamera->far_z / (pCamera->far_z - pCamera->near_z);
	//fog.y = -1.0f / (pCamera->far_z - pCamera->near_z);
	//pEffect->SetFloatArray("g_Fog", (float*)fog, 2);

	//pEffect->Begin(NULL, 0);	// テクニック開始 
	//pEffect->BeginPass(num);		//パスの指定

	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //プリミティブの種類
	//	0, //最初の頂点のインデックス
	//	2); //描画するプリミティブ数

	//pEffect->EndPass();
	//pEffect->End();
}
