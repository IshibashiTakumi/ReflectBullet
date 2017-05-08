//=============================================================================
// 画面遷移
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "modeManager.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"
#include "resource.h"
#include "texture.h"
#include "ShaderManager.h"
#include "shader.h"
#include "forwardShader2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ALPHA_AMOUNT (0.012f)

//=============================================================================
// グローバル変数
//=============================================================================
CFade* CFade::Instance = NULL;	//インスタンス初期化

//=============================================================================
// オブジェクトクラスの生成
//=============================================================================
CFade::CFade()
{
	m_NextMode = NULL;
	m_fade = FADE_IN;
	m_VtxBuff = NULL;	//頂点バッファへのポインタの初期化
	m_Texture = NULL;	//テクスチャへのポインタの初期化
}

//=============================================================================
// オブジェクトクラスの破棄
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// Fadeの初期化
//=============================================================================
void CFade::Init(D3DXCOLOR color, const string& TexName, const string& MaskName)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	m_colorFade = color;	//フェードの初期化
	m_fade = FADE_IN;		//フェード状態の初期化

							 //頂点ブッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY, //確保するバッファサイズ
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED, //使用する頂点フォーマット
								&m_VtxBuff,
								NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	//テクスチャの読み込み
	m_Texture = *CResource::Get<CTexture>(TexName);
	m_Mask = *CResource::Get<CTexture>(MaskName);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//背景の初期化
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	m_VtxBuff->Unlock();
}

//=============================================================================
// Fadeの解放
//=============================================================================
void CFade::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//頂点バッファの解放
}

//=============================================================================
// Fadeの更新
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	if (m_fade == FADE_IN)
	{
		m_colorFade.a -= ALPHA_AMOUNT;

		if (m_colorFade.a <= 0.0f)
		{
			m_colorFade.a = 0.0f;
			m_fade = FADE_NONE;
		}
	}

	else if (m_fade == FADE_OUT)
	{
		m_colorFade.a += ALPHA_AMOUNT;

		if (m_colorFade.a >= 1.0f)
		{
			m_colorFade.a = 1.0f;

			m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

			pVtx[0].col = m_colorFade;
			pVtx[1].col = m_colorFade;
			pVtx[2].col = m_colorFade;
			pVtx[3].col = m_colorFade;

			m_VtxBuff->Unlock();

			CModeManager::GetInstance()->SetMode(m_NextMode); //モードセット
			m_fade = FADE_IN;
		}
	}

	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	m_VtxBuff->Unlock();
}

//=============================================================================
// Fadeの描画
//=============================================================================
void CFade::Draw(int pass)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得 
	CShaderManager::GetInstance()->Find<CForwardShader2D>();	//シェーダの取得

	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //データ間隔

	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	float Criteria = 1.0f - m_colorFade.a;
	CShaderManager::GetInstance()->Begin<CForwardShader2D>(pass, m_Texture, m_Mask, Criteria);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	CShaderManager::GetInstance()->End();
}

//=============================================================================
// Fadeの開始
//=============================================================================
void CFade::Start(CMode *NextMode)
{
	m_NextMode = NextMode;
	m_fade = FADE_OUT;
}

//=============================================================================
// Fadeの取得
//=============================================================================
FADE CFade::GetFade(void)
{
	return m_fade;
}