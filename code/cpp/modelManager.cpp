//=============================================================================
// Model�Ǘ��N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "modelManager.h"
#include "model.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CModelManager* CModelManager::Instance = NULL;	//�C���X�^���X

//=============================================================================
// ����
//=============================================================================
CModel* CModelManager::Find(const string& FileName)
{
	if (m_Search.count(FileName) == 0) return NULL;
	return m_Search.find(FileName)->second;
}

//=============================================================================
// ����
//=============================================================================
void CModelManager::Create(const string& FileName)
{
	if (m_Search.count(FileName) != 0)  return;
	CModel* model = CModel::Create(FileName);
	m_Scan.push_back(model);
	m_Search.insert(unordered_map<string, CModel*>::value_type(FileName, model));
}

//=============================================================================
// �S�ĉ��
//=============================================================================
void CModelManager::ReleaseAll(void)
{
	for each ( auto list in m_Scan) delete list;
	m_Scan.clear();
	m_Search.clear();
}