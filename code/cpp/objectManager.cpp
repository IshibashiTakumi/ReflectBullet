//=============================================================================
// �I�u�W�F�N�g�Ǘ��N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "objectManager.h"
#include "object.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CObjectManager* CObjectManager::Instance = NULL;	//�C���X�^���X

//=============================================================================
// ���ׂẲ��
//=============================================================================
void CObjectManager::UninitAll(void)
{
	for each (auto list in m_List)
	{
		list->Uninit();
		delete list;
	}
	m_List.clear();
	m_ReleaseList.clear();
}

//=============================================================================
// ���ׂĂ̍X�V
//=============================================================================
void CObjectManager::UpdateAll(void)
{
	ReleaseList();
	for each (auto list in m_List)
	{
		list->Update();
	}
}

//=============================================================================
// ���ׂĂ̕`��
//=============================================================================
void CObjectManager::DrawAll(void)
{
	for each (auto list in m_List)
	{
		list->Draw();
	}
}

//=============================================================================
// �폜�o�^
//=============================================================================
void CObjectManager::Release(CObject* Object)
{
	m_ReleaseList.push_back(Object);
}

CObject * CObjectManager::FindName(const string & Name)
{
	for each (auto list in m_List)
	{
		if (list->GetName() != Name) continue;
		return list;
	}
	return nullptr;
}

list<CObject*> CObjectManager::FindTag(const string& Tag)
{
	list<CObject*> List;
	List.clear();
	for each (auto list in m_List)
	{
		if (list->GetTag() != Tag) continue;
		List.push_back(list);
	}
	return List;
}

//=============================================================================
// �o�^���ꂽ���̂��폜
//=============================================================================
void CObjectManager::ReleaseList(void)
{
	for each (auto list in m_ReleaseList)
	{
		for (auto itr = m_List.begin(); itr != m_List.end(); itr++)
		{
			if (list == (*itr))
			{
				itr = m_List.erase(itr);
				list->Uninit();
				delete list;
				break;
			}
		}
	}
	m_ReleaseList.clear();
}