//=============================================================================
// オブジェクト管理クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "objectManager.h"
#include "object.h"

//=============================================================================
// グローバル変数
//=============================================================================
CObjectManager* CObjectManager::Instance = NULL;	//インスタンス

//=============================================================================
// すべての解放
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
// すべての更新
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
// すべての描画
//=============================================================================
void CObjectManager::DrawAll(void)
{
	for each (auto list in m_List)
	{
		list->Draw();
	}
}

//=============================================================================
// 削除登録
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
// 登録されたものを削除
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