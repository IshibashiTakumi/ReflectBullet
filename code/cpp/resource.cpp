//=============================================================================
// Resource基底クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "resource.h"
#include "textureManager.h"
#include "texture.h"
#include "modelManager.h"
#include "model.h"

//=============================================================================
// グローバル変数
//==================================sss===========================================

//=============================================================================
// リソース
//=============================================================================
const string CResource::m_TexturePath[] =
{
	"TextureNone.jpg",	//シェーダ時にテクスチャを使用しないときに使用
	"NormalNone.jpg",	//シェーダ時に法線マッピングを使用しないときに使用
	"ceiling.jpg",
	"font.png",
	"number000.png",
	"title.jpg",
	"result.jpg",
	"tutorial.png",
	"metal003.jpg",
	"metal004.jpg",
	"metal005.jpg",
	"metal003_normal.jpg",
	"metal004_normal.jpg",
	"metal005_normal.jpg",
	"mask.jpg",
	"box.jpg",
	"gauge.png",
	"gaugeMask.jpg",
};
const string CResource::m_ModelPath[] =
{
	"bullet.x",
	"enemybullet.x",
	"player.x",
	"enemy.x",
	"tree.x",
};

//=============================================================================
// リソース読み込み
//=============================================================================
void CResource::Load(void)
{
	for each (auto name in m_TexturePath)
	{
		CTextureManager::GetInstance()->Create(name);
	}
	for each (auto name in m_ModelPath)
	{
		CModelManager::GetInstance()->Create(name);
	}
}

//=============================================================================
// リソース解放
//=============================================================================
void CResource::Unload(void)
{
	CTextureManager::GetInstance()->ReleaseAll();	
	CModelManager::GetInstance()->ReleaseAll();	
}

template<>
CTexture* CResource::Get(const string &FileName)
{
	return CTextureManager::GetInstance()->Find(FileName);
}

template<>
CModel* CResource::Get(const string &FileName)
{
	return CModelManager::GetInstance()->Find(FileName);
}

