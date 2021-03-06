//=============================================================================
// Resource基底クラス
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 構造体
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class ModelX;

//=============================================================================
// クラスの定義
//=============================================================================
class CModelX : public CModel
{
public:

	//コンストラクタ・デストラクタ
	//=============================================================================
	CModelX(const string &FileName);
	~CModelX();

	//operator CModelX*() const;
	operator ModelX*() const;

private:
	ModelX *m_ModelX;

};

class ModelX
{
public:
	LPD3DXMESH Mesh;				//メッシュ情報
	LPD3DXBUFFER BuffMat;			//マテリアル情報
	DWORD NumMat;					//マテリアルの数
	D3DMATERIAL9* MeshMat;			//マテリアル情報
	LPDIRECT3DTEXTURE9*	MeshTex;	//メッシュのテクスチャ
};