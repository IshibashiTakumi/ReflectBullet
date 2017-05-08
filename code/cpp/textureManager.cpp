//=============================================================================
// Texture�Ǘ��N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "textureManager.h"
#include "texture.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CTextureManager* CTextureManager::Instance = NULL;	//�C���X�^���X

//=============================================================================
// ����
//=============================================================================
CTexture * CTextureManager::Find(const string& FileName)
{
	if (m_Search.count(FileName) == 0) return NULL;
	return m_Search.find(FileName)->second;
}

//=============================================================================
// ����
//=============================================================================
void CTextureManager::Create(const string& FileName)
{
	if (m_Search.count(FileName) != 0)  return;
	CTexture* texture = new CTexture(FileName);
	m_Scan.push_back(texture);
	m_Search.insert(unordered_map<string, CTexture*>::value_type(FileName, texture));
}

//=============================================================================
// ���
//=============================================================================
void CTextureManager::ReleaseAll(void)
{
	for each ( auto list in m_Scan) delete list;
	m_Scan.clear();
	m_Search.clear();
}
