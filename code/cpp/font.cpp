//=============================================================================
// 文字描画
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "font.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "ShaderManager.h"
#include "shader.h"
#include "forwardShader2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define WIDTH_FONT_NUM ( 10 )									//フォントの横の文字数
#define HEIGHT_FONT_NUM ( 7 )									//フォントの高さの文字数
#define FONTINTERVAL_WIDTH ( 1.0f / (float)WIDTH_FONT_NUM )		//テクスチャの横描画間隔
#define FONTINTERVAL_HEIGHT ( 1.0f / (float)HEIGHT_FONT_NUM )	//テクスチャの高さ描画間隔
#define FONT_TYPE_MAX ( WIDTH_FONT_NUM * HEIGHT_FONT_NUM + 1 )	//フォント種類の最大数

//=============================================================================
// グローバル変数
//=============================================================================
string CFont::m_Font = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ,.!?abcdefghijklmnopqrstuvwxyz:-#/";	//入力文字の種類

//=============================================================================
// クラスの生成
//=============================================================================
CFont::CFont(CTransform* Transform) : CScene(Transform, PRIORITY_2D)
{
	m_VtxBuff = NULL;	//頂点バッファへのポインタの初期化
	m_Texture = NULL;	//テクスチャへのポインタの初期化
}

//=============================================================================
// クラスの破棄
//=============================================================================
CFont::~CFont()
{
	
}

//=============================================================================
// 2Dポリゴン初期化
//=============================================================================
void CFont::Init(D3DXVECTOR2 Size, string word, D3DXCOLOR color)
{
	
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	m_Size.x = Size.x;
	m_Size.y = Size.y;

	m_WordMax = word.size();

	float Width, Height, Angle, Length;
	Width = ((m_Size.x / m_WordMax) * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transformで変形した幅
	Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transformで変形した高さ
	Angle = atan2f(Width, Height);							//対角線の角度
	Length = sqrtf(Width * Width + Height * Height) * 0.5f; //対角線の長さ

	//テクスチャの読み込み
	m_Texture = *CResource::Get<CTexture>("font.png");

	//頂点ブッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (VERTEX_NUM * m_WordMax),
		D3DUSAGE_WRITEONLY, //確保するバッファサイズ
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, //使用する頂点フォーマット
		&m_VtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	D3DXVECTOR2 tex = Vec2Init();
	float width = m_Size.x / m_WordMax;
	float pos = ((m_LocalTransform->Pos.x - (m_Size.x * 0.5f)) + (width * 0.5f));
	for (int count = 0; count < m_WordMax; count++)
	{
		//テクスチャ座標の設定
		if (SetScan(word[count], tex))
		{
			pVtx[count * 4 + 0].tex = D3DXVECTOR2(tex.x, tex.y);
			pVtx[count * 4 + 1].tex = D3DXVECTOR2(tex.x + FONTINTERVAL_WIDTH, tex.y);
			pVtx[count * 4 + 2].tex = D3DXVECTOR2(tex.x, tex.y + FONTINTERVAL_HEIGHT);
			pVtx[count * 4 + 3].tex = D3DXVECTOR2(tex.x + FONTINTERVAL_WIDTH, tex.y + FONTINTERVAL_HEIGHT);
		}
		else
		{
			for (int cnt = 0; cnt < 4; cnt++) pVtx[count * 4 + cnt].tex = Vec2Init();
		}

		pVtx[count * 4 + 0].pos.x = (pos + (width * count)) - sinf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 0].pos.y = m_LocalTransform->Pos.y - cosf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 0].pos.z = 0.0f;
		pVtx[count * 4 + 1].pos.x = (pos + (width * count)) + sinf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 1].pos.y = m_LocalTransform->Pos.y - cosf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 1].pos.z = 0.0f;
		pVtx[count * 4 + 2].pos.x = (pos + (width * count)) - sinf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 2].pos.y = m_LocalTransform->Pos.y + cosf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 2].pos.z = 0.0f;
		pVtx[count * 4 + 3].pos.x = (pos + (width * count)) + sinf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 3].pos.y = m_LocalTransform->Pos.y + cosf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 3].pos.z = 0.0f;
	}
	
	for (int count = 0; count < VERTEX_NUM * m_WordMax; count++)
	{
		pVtx[count].rhw = 1.0f;		//座標変換用係数の設定
		pVtx[count].col = color;	//頂点カラーの設定
	}

	m_VtxBuff->Unlock();
}

//=============================================================================
// 2Dポリゴン解放
//=============================================================================
void CFont::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//頂点バッファの解放 
}

//=============================================================================
// 2Dポリゴン更新
//=============================================================================
void CFont::Update(void)
{
	//float Width, Height, Angle, Length;
	//Width = (m_Size.x * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transformで変形した幅
	//Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transformで変形した高さ
	//Angle = atan2f(Width, Height);							//対角線の角度
	//Length = sqrtf(Width * Width + Height * Height) * 0.5f; //対角線の長さ

	//VERTEX_2D *pVtx;
	//m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	//pVtx[0].pos.x = m_Transform->Pos.x - sinf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[0].pos.y = m_Transform->Pos.y - cosf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[0].pos.z = 0.0f;
	//pVtx[1].pos.x = m_Transform->Pos.x + sinf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[1].pos.y = m_Transform->Pos.y - cosf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[1].pos.z = 0.0f;
	//pVtx[2].pos.x = m_Transform->Pos.x - sinf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[2].pos.y = m_Transform->Pos.y + cosf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[2].pos.z = 0.0f;
	//pVtx[3].pos.x = m_Transform->Pos.x + sinf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[3].pos.y = m_Transform->Pos.y + cosf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[3].pos.z = 0.0f;

	//m_VtxBuff->Unlock();
}

//=============================================================================
// 2Dポリゴン描画
//=============================================================================
void CFont::Draw(int pass)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得 
	CShaderManager::GetInstance()->Find<CForwardShader2D>();	//シェーダの取得

																//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //データ間隔

	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	CShaderManager::GetInstance()->Begin<CForwardShader2D>(pass, m_Texture);

	for (int wordCount = 0; wordCount < m_WordMax; wordCount++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //プリミティブの種類
			wordCount * 4, //最初の頂点のインデックス
			2); //描画するプリミティブ
	}

	CShaderManager::GetInstance()->End();
}

//=============================================================================
// UV座標走査
//=============================================================================
bool CFont::SetScan(char font, D3DXVECTOR2& tex)
{
	for (int count = 0; count < m_Font.size(); count++)
	{
		if (m_Font[count] == font)
		{
			//テクスチャ座標の割り振り(左上座標)
			tex.x = (count % WIDTH_FONT_NUM) * FONTINTERVAL_WIDTH;
			tex.y = (count / WIDTH_FONT_NUM) * FONTINTERVAL_HEIGHT;

			return true;
		}
	}

	return false;
}

//=============================================================================
// 色変更
//=============================================================================
void CFont::SetColor(D3DXCOLOR color)
{
	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	for (int count = 0; count < VERTEX_NUM * m_WordMax; count++)
	{
		pVtx[count].col = color;	//頂点カラーの設定
	}

	m_VtxBuff->Unlock();
}