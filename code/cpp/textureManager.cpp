//=============================================================================
// Texture管理クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "textureManager.h"
#include "texture.h"

//=============================================================================
// グローバル変数
//=============================================================================
CTextureManager* CTextureManager::Instance = NULL;	//インスタンス

//=============================================================================
// 検索
//=============================================================================
CTexture * CTextureManager::Find(const string& FileName)
{
	if (m_Search.count(FileName) == 0) return NULL;
	return m_Search.find(FileName)->second;
}

//=============================================================================
// 生成
//=============================================================================
void CTextureManager::Create(const string& FileName)
{
	if (m_Search.count(FileName) != 0)  return;
	CTexture* texture = new CTexture(FileName);
	m_Scan.push_back(texture);
	m_Search.insert(unordered_map<string, CTexture*>::value_type(FileName, texture));
}

//=============================================================================
// 解放
//=============================================================================
void CTextureManager::ReleaseAll(void)
{
	for each ( auto list in m_Scan) delete list;
	m_Scan.clear();
	m_Search.clear();
}
