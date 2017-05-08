//=============================================================================
// 描画管理クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "sceneManager.h"
#include "scene.h"

//=============================================================================
// グローバル変数
//=============================================================================
CSceneManager* CSceneManager::Instance = NULL;	//インスタンス

//=============================================================================
// クラスの生成
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
// クラスの破棄
//=============================================================================
CSceneManager::~CSceneManager()
{

}

//=============================================================================
// すべての解放
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
// すべての更新
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
// すべての描画
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
// 指定の描画
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
//  削除登録
//=============================================================================
void CSceneManager::Release(CScene* Scene)
{
	m_ReleaseList.push_back(Scene);
}

//=============================================================================
// 登録されたものを削除
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