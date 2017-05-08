//=============================================================================
// 3D描画
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "camera.h"
#include "cameraManager.h"
#include "object.h"
#include "objectManager.h"
#include "shaderManager.h"
#include "shader.h"
#include "shader3D.h"

//=============================================================================
// クラスの生成
//=============================================================================
CScene3D::CScene3D(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_VtxBuff = NULL;	//頂点バッファポインタの初期化
	m_Texture = NULL;	//テクスチャポインタの初期化
}

//=============================================================================
// クラスの破棄
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
//  初期化
//=============================================================================
void CScene3D::Init(D3DXVECTOR2 Size, string& Texture, string& NormalMap, D3DXCOLOR color, D3DXVECTOR2 tex)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance() -> GetDevice( ); //デバイスの取得 

	//テクスチャの読み込み
	m_Texture = *CResource::Get<CTexture>(Texture);
	m_NormalMap = *CResource::Get<CTexture>(NormalMap);

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
void CScene3D::Uninit( void )
{
	ResourceRelease(m_VtxBuff);	//頂点バッファの解放 
}

//=============================================================================
// 描画
//=============================================================================
void CScene3D::Draw(int num)
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

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); 

	CShaderManager::GetInstance()->End();
}
