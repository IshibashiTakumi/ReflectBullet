//=============================================================================
// 描画の準備
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "shaderManager.h"
#include "deferredShader.h"
#include "zTexRenderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
namespace renderer_define
{
	static const float START_FOG = 3000.0f;	//フォグの開始地点
	static const float END_FOG = 25000.0f;	//フォグの終了地点
}
using namespace renderer_define;

//=============================================================================
// グローバル変数
//=============================================================================
CRenderer* CRenderer::Instance = NULL;	//インスタンス初期化

//=============================================================================
// クラスの生成
//=============================================================================
CRenderer::CRenderer()
{
	m_D3D = NULL;	 //DirectX3Dオブジェクトへのポインタ初期化
	m_D3DDevice = NULL;	//DirectX3Dデバイスへのポインタ初期化
}

//=============================================================================
// クラスの破棄
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_D3D == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //画面の幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; //画面の高さ
	d3dpp.BackBufferFormat = d3ddm.Format; //バックバッファの形式
	d3dpp.BackBufferCount = 1; //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE; //デプスバッファとステンシルバッファを作成する
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; //デプスバッファとして16ビットを使用する
	d3dpp.Windowed = bWindow; //( ウインドウモード / フルスクリーン )
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成
	if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, //描画
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, //頂点処理
		&d3dpp,
		&m_D3DDevice)))
	{
		if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_D3DDevice)))
		{
			if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_D3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステート設定
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //カリング方法
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); //アルファーブレンドの設定
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	////フォグの設定
	float StartFog = START_FOG;	//開始位置
	float EndFog = END_FOG;		//終了位置
	m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //フォグ：ON
	m_D3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(255, 255, 255, 255)); //白色で不透明
	m_D3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);      //頂点モード
	m_D3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);     //テーブルモード
	m_D3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&StartFog)); //開始位置
	m_D3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&EndFog));     //終了位置

	//サンプラーステートの設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); //テクスチャの縮小時の補間設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //テクスチャの拡大時の補間設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); //テクスチャ(U値)繰り返しに設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); //テクスチャ(V値)繰り返しに設定

	//テクスチャステージステートの設定
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DVERTEXELEMENT9 mDecl[] = 
	{ { 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
	{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0 },
	{ 0,24,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0 },
	{ 0,36,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0 },
	{ 0,48,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 }, 
		D3DDECL_END() };

	m_D3DDevice->CreateVertexDeclaration(mDecl, &mVertexDeclaration);

	m_D3DDevice->GetRenderTarget(0, &m_BackBufferSurface);
	m_D3DDevice->GetDepthStencilSurface(&m_Zbuffer); 
	m_D3DDevice->GetViewport(&m_Viewport);

	CShaderManager::GetInstance()->Init();
	CDeferredShader::GetInstance()->Init();
	CZTexRenderer::GetInstance()->Init();

	return S_OK;
}

//=============================================================================
// デバイスの解放
//=============================================================================
void CRenderer::Uninit(void)
{
	CShaderManager::GetInstance()->Uninit();
	CDeferredShader::GetInstance()->Uninit();
	CZTexRenderer::GetInstance()->Uninit();

	ResourceRelease(m_D3DDevice);
	ResourceRelease(m_D3D);

	ResourceRelease(m_BackBufferSurface); 
	ResourceRelease(m_Zbuffer);
}

//=============================================================================
// 描画開始
//=============================================================================
void CRenderer::Begin(void)
{
	m_D3DDevice->SetViewport(&m_Viewport);
	m_D3DDevice->SetRenderTarget(0, m_BackBufferSurface);
	for (int count = 0; count < 3; count++)
	{
		m_D3DDevice->SetRenderTarget(count + 1, NULL);
	}
	m_D3DDevice->SetDepthStencilSurface(m_Zbuffer);

	//画面のクリア
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	SUCCEEDED(m_D3DDevice->BeginScene());	//描画開始
}

//=============================================================================
// 描画終了
//=============================================================================
void CRenderer::End(void)
{
	m_D3DDevice->EndScene(); //描画終了

	m_D3DDevice->Present(NULL, NULL, NULL, NULL); //バックバッファとフロントバッファの入れ替え
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_D3DDevice;
}