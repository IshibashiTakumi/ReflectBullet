//=============================================================================
// Lightの管理
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "lightManager.h"
#include "light.h"
#include "directionalLight.h"
#include "template.h"

#include "shaderManager.h"
#include "shader.h"
#include "shader2D.h"

//=============================================================================
// グローバル変数
//=============================================================================
CLightManager* CLightManager::Instance = NULL;	//インスタンス

//=============================================================================
// 全てのLightの作製
//=============================================================================
void CLightManager::CreateAll(void)
{
	/*CTemplate::Create<CDirectionalLight>(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, -1.0f, -0.5f), 0);
	CTemplate::Create<CDirectionalLight>(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 1.0f, 0.65f), 1);
	CTemplate::Create<CDirectionalLight>(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, -0.5f), 2);*/

	/*CTemplate::Create<CDirectionalLight>(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXVECTOR3(1.0f, -1.0f, -0.5f), 0);
	CTemplate::Create<CDirectionalLight>(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXVECTOR3(-1.0f, 1.0f, 0.65f), 1);
	CTemplate::Create<CDirectionalLight>(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, -0.5f), 2);*/
}

//=============================================================================
// 全てのLightの解放
//=============================================================================
void CLightManager::UninitAll(void)
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
// 全てのLight更新
//=============================================================================
void CLightManager::UpdateAll(void)
{
	CShader* shader = CShaderManager::GetInstance()->Find<CShader2D>();

	D3DXVECTOR3 Vec[3] = { D3DXVECTOR3(1.0f, -1.0f, -0.5f) , D3DXVECTOR3(-1.0f, 1.0f, 0.65f) , D3DXVECTOR3(0.0f, 0.0f, -0.5f) };
	D3DXCOLOR color[3];
	color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	color[1] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	color[2] = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	shader->Get()->SetFloatArray("g_lightVec", (float*)Vec, 9);
	shader->Get()->SetFloatArray("g_color", (float*)color, 12);

	for each (auto list in m_List)
	{
		list->Update();
	}
	ReleaseList();
}

//=============================================================================
// 削除リストに登録
//=============================================================================
void CLightManager::Release(CLight* Light)
{
	m_ReleaseList.push_back(Light);
}

//=============================================================================
// 指定されたLightの解放
//=============================================================================
void CLightManager::ReleaseList(void)
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