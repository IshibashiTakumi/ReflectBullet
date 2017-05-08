//=============================================================================
// �`��Ǘ��N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "sceneManager.h"
#include "scene.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CSceneManager* CSceneManager::Instance = NULL;	//�C���X�^���X

//=============================================================================
// �N���X�̐���
//=============================================================================
CSceneManager::CSceneManager()
{
	for (int count = 0; count < PRIORITY_MAX; count++)
	{
		m_List[count].clear();
	}
	m_ReleaseList.clear();
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CSceneManager::~CSceneManager()
{

}

//=============================================================================
// ���ׂẲ��
//=============================================================================
void CSceneManager::UninitAll(void)
{
	for (int Priority = 0; Priority < PRIORITY_MAX; Priority++)
	{
		for each (auto list in m_List[Priority])
		{
			list->Uninit();
			delete list;
		}
		m_List[Priority].clear();
	}
	m_ReleaseList.clear();
}

//=============================================================================
// ���ׂĂ̍X�V
//=============================================================================
void CSceneManager::UpdateAll(void)
{
	ReleaseList();
	for (int Priority = 0; Priority < PRIORITY_MAX; Priority++)
	{
		for each (auto list in m_List[Priority])
		{
			list->Transformation();
			list->Update();
		}
	}
}

//=============================================================================
// ���ׂĂ̕`��
//=============================================================================
void CSceneManager::DrawAll(void)
{
	for (int Priority = 0; Priority < PRIORITY_MAX; Priority++)
	{
		for each (auto list in m_List[Priority])
		{
			list->Begin();
			list->Draw(1);
			list->End();
		}
	}
}

//=============================================================================
// �w��̕`��
//=============================================================================
void CSceneManager::PriorityDraw(PRIORITY Priority, int pass)
{
	for each (auto list in m_List[Priority])
	{
		list->Begin();
		list->Draw(pass);
		list->End();
	}
}

//=============================================================================
//  �폜�o�^
//=============================================================================
void CSceneManager::Release(CScene* Scene)
{
	m_ReleaseList.push_back(Scene);
}

//=============================================================================
// �o�^���ꂽ���̂��폜
//=============================================================================
void CSceneManager::ReleaseList(void)
{
	for each (auto list in m_ReleaseList)
	{
		for (auto itr = m_List[GetPriority(list)].begin(); itr != m_List[GetPriority(list)].end(); itr++)
		{
			if (list == (*itr))
			{
				itr = m_List[GetPriority(list)].erase(itr);
				list->Uninit();
				delete list;
				break;
			}
		}
	}
	m_ReleaseList.clear();
}