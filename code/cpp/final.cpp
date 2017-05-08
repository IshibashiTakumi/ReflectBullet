//=============================================================================
// 2D描画
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "final.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"

#include "deferredShader.h"

#include "camera.h"
#include "cameraManager.h"

#include "ShaderManager.h"
#include "shader.h"
#include "shader2D.h"

//=============================================================================
// クラスの生成
//=============================================================================
CFinal::CFinal(CTransform* Transform) : CScene(Transform, PRIORITY_2D)
{
	m_VtxBuff = NULL;	//頂点バッファへのポインタの初期化
	m_Texture = NULL;	//テクスチャへのポインタの初期化
}

//=============================================================================
// クラスの破棄
//=============================================================================
CFinal::~CFinal()
{
	
}

//=============================================================================
// 2Dポリゴン初期化
//=============================================================================
void CFinal::Init(D3DXVECTOR2 Size, string& TexName, LPDIRECT3DTEXTURE9 Texture, D3DXCOLOR color)
{
	
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	m_Size.x = Size.x;
	m_Size.y = Size.y;

	float Width, Height, Angle, Length;
	Width = (m_Size.x * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transformで変形した幅
	Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transformで変形した高さ
	Angle = atan2f(Width, Height);							//対角線の角度
	Length = sqrtf(Width * Width + Height * Height) * 0.5f; //対角線の長さ

	//テクスチャの読み込み
	m_Texture = Texture;

	//頂点ブッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
		D3DUSAGE_WRITEONLY, //確保するバッファサイズ
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, //使用する頂点フォーマット
		&m_VtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

												  //テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//ポリゴンの初期化
	pVtx[0].pos.x = m_LocalTransform->Pos.x - sinf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[0].pos.y = m_LocalTransform->Pos.y - cosf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[0].pos.z = 0.0f;			
	pVtx[1].pos.x = m_LocalTransform->Pos.x + sinf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[1].pos.y = m_LocalTransform->Pos.y - cosf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[1].pos.z = 0.0f;			
	pVtx[2].pos.x = m_LocalTransform->Pos.x - sinf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[2].pos.y = m_LocalTransform->Pos.y + cosf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[2].pos.z = 0.0f;			
	pVtx[3].pos.x = m_LocalTransform->Pos.x + sinf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[3].pos.y = m_LocalTransform->Pos.y + cosf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[3].pos.z = 0.0f;

	//座標変換用係数の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	m_VtxBuff->Unlock();
}

//=============================================================================
// 2Dポリゴン解放
//=============================================================================
void CFinal::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//頂点バッファの解放 
}

//=============================================================================
// 2Dポリゴン更新
//=============================================================================
void CFinal::Update(void)
{
	float Width, Height, Angle, Length;
	Width = (m_Size.x * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transformで変形した幅
	Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transformで変形した高さ
	Angle = atan2f(Width, Height);							//対角線の角度
	Length = sqrtf(Width * Width + Height * Height) * 0.5f; //対角線の長さ

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //頂点情報へのポインタを取得

	pVtx[0].pos.x = m_Transform->Pos.x - sinf(Angle + m_Transform->Rot.z) * Length;
	pVtx[0].pos.y = m_Transform->Pos.y - cosf(Angle + m_Transform->Rot.z) * Length;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_Transform->Pos.x + sinf(Angle - m_Transform->Rot.z) * Length;
	pVtx[1].pos.y = m_Transform->Pos.y - cosf(Angle - m_Transform->Rot.z) * Length;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_Transform->Pos.x - sinf(Angle - m_Transform->Rot.z) * Length;
	pVtx[2].pos.y = m_Transform->Pos.y + cosf(Angle - m_Transform->Rot.z) * Length;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_Transform->Pos.x + sinf(Angle + m_Transform->Rot.z) * Length;
	pVtx[3].pos.y = m_Transform->Pos.y + cosf(Angle + m_Transform->Rot.z) * Length;
	pVtx[3].pos.z = 0.0f;

	m_VtxBuff->Unlock();
}

//=============================================================================
// 2Dポリゴン描画
//=============================================================================
void CFinal::Draw(int num)
{
	num = 1;
	LPDIRECT3DTEXTURE9 tex[RENDERTARGET_MAX];
	for (int count = 0; count < RENDERTARGET_MAX; count++) tex[count] = CDeferredShader::GetInstance()->GetTexture(count);

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得 
	CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();		//カメラの取得
	CShaderManager::GetInstance()->Find<CShader2D>();	//シェーダの取得
																			//ワールドマトリックスの設定
	SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);

	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //データ間隔

	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	CShaderManager::GetInstance()->Begin<CShader2D>(num, tex[0], tex[1], tex[2], tex[3]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	CShaderManager::GetInstance()->End();
}