//=============================================================================
// Resource基底クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "model.h"
#include "modelX.h"
#include "resource.h"
#include "renderer.h"
#include "manager.h"

using namespace directory;

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// クラスの生成
//=============================================================================
CModelX::CModelX(const string &FileName)
{
	
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //デバイスの取得 

	m_ModelX = new ModelX;

	m_ModelX->Mesh = NULL;		//メッシュ情報の初期化
	m_ModelX->BuffMat = NULL;	//マテリアル情報の初期化
	m_ModelX->MeshMat = NULL;	//マテリアル情報の初期化
	m_ModelX->MeshTex = NULL;	//メッシュのテクスチャの初期化

	//Xファイルの読み込み
	D3DXLoadMeshFromX((Model_Directory + FileName).c_str(),	//読み込むファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_ModelX->BuffMat,		//マテリアル情報
		NULL,
		&m_ModelX->NumMat,		//マテリアルの数
		&m_ModelX->Mesh);		//メッシュ情報

						// マテリアル情報を取り出す
	D3DXMATERIAL*	d3Mat = (D3DXMATERIAL*)m_ModelX->BuffMat->GetBufferPointer();
	m_ModelX->MeshMat = new D3DMATERIAL9[m_ModelX->NumMat];		// メッシュ情報を確保
	m_ModelX->MeshTex = new LPDIRECT3DTEXTURE9[m_ModelX->NumMat];// テクスチャを確保
	for (int nCntMat = 0; nCntMat < (int)m_ModelX->NumMat; nCntMat++)
	{
		m_ModelX->MeshMat[nCntMat] = d3Mat[nCntMat].MatD3D;			// マテリアル情報セット
		m_ModelX->MeshTex[nCntMat] = NULL;	// テクスチャ初期化
									// 使用しているテクスチャがあれば読み込む
		if (d3Mat[nCntMat].pTextureFilename != NULL && lstrlen(d3Mat[nCntMat].pTextureFilename) > 0)
		{
			// テクスチャ読み込み
			D3DXCreateTextureFromFile(
				pDevice,
				d3Mat[nCntMat].pTextureFilename,
				&m_ModelX->MeshTex[nCntMat]);
		}
	}
}

//=============================================================================
// クラスの破棄
//=============================================================================
CModelX::~CModelX()
{
	if (m_ModelX->Mesh != NULL)
	{
		m_ModelX->Mesh->Release(); //メッシュの解放
		m_ModelX->Mesh = NULL;
	}

	if (m_ModelX->BuffMat != NULL)
	{
		m_ModelX->BuffMat->Release(); //マテリアルの解放
		m_ModelX->BuffMat = NULL;
	}

	for (int nCntMat = 0; nCntMat < (int)m_ModelX->NumMat; nCntMat++)
	{
		ResourceRelease(m_ModelX->MeshTex[nCntMat]);
	}

	delete[] m_ModelX->MeshTex;
	m_ModelX->MeshTex = NULL;
	delete[] m_ModelX->MeshMat;
	m_ModelX->MeshMat = NULL;
	delete m_ModelX;
}

//CModelX::operator CModelX*() const
//{
//	return *this;
//}

CModelX::operator ModelX*() const
{
	//自身が存在しなかったらnullptrを返す
	if (this == nullptr) return nullptr;
	return m_ModelX;
}