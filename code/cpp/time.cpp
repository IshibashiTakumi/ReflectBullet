//=============================================================================
// タイム描画
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "time.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "object.h"
#include "mode.h"
#include "fade.h"
#include "title.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TIMEINTERVAL_WIDTH ( 0.1f )								//テクスチャの横描画間隔
#define TIMEINTERVAL_HEIGHT ( 1.0f )							//テクスチャの高さ描画間隔

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// オブジェクトクラスの生成
//=============================================================================
CTime::CTime(CTransform* Transform) : CScene(Transform, PRIORITY_2D)
{
	m_VtxBuff = NULL;	//頂点バッファへのポインタの初期化
	m_Texture = NULL;	//テクスチャへのポインタの初期化

	m_nCounterTimeAnim = 0; //アニメーションカウンターの初期化
	m_nPatternTimeAnim = 0; //アニメーションパターンNoの初期化
}

//=============================================================================
// オブジェクトクラスの破棄
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CTime::Init(int digit, int time, D3DXVECTOR2 size, string texName)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得

	m_LimitTime = time;
	float IntervalWidth = size.x / digit; //タイム間隔の計算用
	m_Digit = digit;

	//頂点ブッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (VERTEX_NUM * m_Digit),
		D3DUSAGE_WRITEONLY, //確保するバッファサイズ
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, //使用する頂点フォーマット
		&m_VtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

											 //テクスチャの読み込み
	m_Texture = *CResource::Get<CTexture>(texName);

	float pos = (m_LocalTransform->Pos.x - size.x * 0.5f) + IntervalWidth * 0.5f;

	for (int nCount = 0; nCount < m_Digit; nCount++)
	{
		pVtx[0 + nCount * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + nCount * 4].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2 + nCount * 4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + nCount * 4].tex = D3DXVECTOR2(0.1f, 1.0f);

		//位置の初期化
		pVtx[0 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) - (IntervalWidth * 0.5f), m_LocalTransform->Pos.y - (size.y * 0.5f), 0.0f);
		pVtx[1 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) + (IntervalWidth * 0.5f), m_LocalTransform->Pos.y - (size.y * 0.5f), 0.0f);
		pVtx[2 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) - (IntervalWidth * 0.5f), m_LocalTransform->Pos.y + (size.y * 0.5f), 0.0f);
		pVtx[3 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) + (IntervalWidth * 0.5f), m_LocalTransform->Pos.y + (size.y * 0.5f), 0.0f);

		pVtx[0 + nCount * 4].rhw = 1.0f;
		pVtx[1 + nCount * 4].rhw = 1.0f;
		pVtx[2 + nCount * 4].rhw = 1.0f;
		pVtx[3 + nCount * 4].rhw = 1.0f;

		pVtx[0 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
		pVtx[1 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
		pVtx[2 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
		pVtx[3 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
	}

	//テクスチャの位置計算
	for (int nCount = 0; nCount < m_Digit; nCount++)
	{
		float Count = (float)m_Digit - (nCount + 1);

		int Time = (int)(m_LimitTime / pow(10, Count)) % 10;

		pVtx[0 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[1 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
		pVtx[2 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[3 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
	}

	m_VtxBuff->Unlock();
}
//=============================================================================
// 解放
//=============================================================================
void CTime::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//頂点バッファの解放 
}
//=============================================================================
// 更新
//=============================================================================
void CTime::Update(void)
{
	VERTEX_2D *pVtx;

	float oldg_nTime; //一個前のタイムの値
	float Count;
	int Time;

	if (m_LimitTime > 0) oldg_nTime = m_LimitTime;
	else oldg_nTime = 0;


	//テクスチャの処理
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの位置計算
	for (int nCount = 0; nCount < m_Digit; nCount++)
	{
		Count = (float)m_Digit - (nCount + 1);

		Time = (int)(oldg_nTime / pow(10, Count)) % 10;

		pVtx[0 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[1 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
		pVtx[2 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[3 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
	}

	m_VtxBuff->Unlock();

	if (m_LimitTime <= 1)
	{
		CFade::GetInstance()->Start(new CTitle);
	}

	m_LimitTime -= FrameTime();
}
//=============================================================================
// 描画
//=============================================================================
void CTime::Draw(int pass)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0,
		m_VtxBuff,
		0,
		sizeof(VERTEX_2D)); //データ間隔

							//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_Texture);

	//ポリゴンの描画
	for (int Count = 0; Count < m_Digit; Count++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //プリミティブの種類
			Count * 4, //最初の頂点のインデックス
			2); //描画するプリミティブ数
	}
}