//=============================================================================
// 遅延シェーダ
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "deferredShader.h"
#include "renderer.h"
#include "camera.h"
#include "cameraManager.h"
#include "ShaderManager.h"
#include "shader.h"
#include "shader2D.h"
#include "zTexRenderer.h"

//=============================================================================
// グローバル変数
//=============================================================================
CDeferredShader* CDeferredShader::Instance = NULL;	//インスタンス初期化

//=============================================================================
// クラスの生成
//=============================================================================
CDeferredShader::CDeferredShader()
{

}

//=============================================================================
// クラスの破棄
//=============================================================================
CDeferredShader::~CDeferredShader()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CDeferredShader::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &m_Texture[0], NULL);
	m_Texture[0]->GetSurfaceLevel(0, &m_Surface[0]);

	for (int count = 1; count < RENDERTARGET_MAX; count++)
	{
		pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_Texture[count], NULL);
		m_Texture[count]->GetSurfaceLevel(0, &m_Surface[count]);
	}

	pDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &m_Zbuffer, NULL);

	//頂点ブッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,D3DPOOL_MANAGED, &m_VtxBuff, NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//ポリゴンの初期化
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for (int count = 0; count < VERTEX_NUM; count++)
	{
		pVtx[count].rhw = 1.0f;		//座標変換用係数の設定
		pVtx[count].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//頂点カラーの設定
	}
}

//=============================================================================
// デバイスの解放
//=============================================================================
void CDeferredShader::Uninit(void)
{
	for (int count = 0; count < RENDERTARGET_MAX; count++)
	{
		ResourceRelease(m_Texture[count]);
		ResourceRelease(m_Surface[count]);
	}
	ResourceRelease(m_Zbuffer);
	DestroyInstance();
}

//=============================================================================
// 描画開始
//=============================================================================
void CDeferredShader::Begin(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	//画面のクリア
	for (int count = 0; count < RENDERTARGET_MAX; count++) pDevice->SetRenderTarget(count, m_Surface[count]);

	pDevice->SetDepthStencilSurface(m_Zbuffer);

	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	SUCCEEDED(pDevice->BeginScene());	//描画開始
}

//=============================================================================
// 生成したテクスチャを使った最終結果描画
//=============================================================================
void CDeferredShader::Draw(int pass)
{
	LPDIRECT3DTEXTURE9 tex[RENDERTARGET_MAX];
	for (int count = 0; count < RENDERTARGET_MAX; count++) tex[count] = CDeferredShader::GetInstance()->GetTexture(count);
	LPDIRECT3DTEXTURE9 depth = CZTexRenderer::GetInstance()->GetTexture();

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得 
	CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();		//カメラの取得
	CShaderManager::GetInstance()->Find<CShader2D>();	//シェーダの取得

	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //データ間隔

	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	CShaderManager::GetInstance()->Begin<CShader2D>(pass, depth, m_Texture[0], m_Texture[1], m_Texture[2], m_Texture[3]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	CShaderManager::GetInstance()->End();
}

//=============================================================================
// 描画終了
//=============================================================================
void CDeferredShader::End(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	pDevice->EndScene(); //描画終了
}