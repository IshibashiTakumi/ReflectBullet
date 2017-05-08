//=============================================================================
// 点光源
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "pointLightManager.h"
#include "pointLight.h"
#include "renderer.h"

#include "shaderManager.h"
#include "shader.h"
#include "shader2D.h"

//=============================================================================
// グローバル変数
//=============================================================================
CPointLightManager* CPointLightManager::Instance = NULL;	//インスタンス

//=============================================================================
// 解放
//=============================================================================
void CPointLightManager::UninitAll(void)
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
// 解放
//=============================================================================
void CPointLightManager::UpdateAll(void)
{
	for (int count = 0; count < POINTLIGHT_MAX; count++)
	{
		m_Pos[count] = Vec3Init();
		m_Color[count] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_Radius[count] = 0.0f;
	}

	int LightNum = 0;
	ReleaseList();
	for each (auto list in m_List)
	{
		list->Update();
		if (LightNum < POINTLIGHT_MAX)
		{
			m_Pos[LightNum] = list->m_Pos;
			m_Color[LightNum] = list->m_Color;
			m_Radius[LightNum] = list->m_Radius;
		}

		LightNum++;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CPointLightManager::DrawAll(void)
{
	//ID3DXEffect* pEffect = CRenderer::GetInstance()->GetEffect(1);
	//
	///*for (int count = 0; count < 50; count++)
	//{
	//	g_lightPos[count] = m_Pos[count];
	//	g_lightColor[count] = m_Color[count];
	//	g_lightRadius[count] = m_Radius[count];
	//}*/
	//pEffect->SetFloatArray("g_lightRadius", (float*)m_Radius, POINTLIGHT_MAX);
	//pEffect->SetFloatArray("g_lightPos", (float*)m_Pos, POINTLIGHT_MAX * 3);
	//pEffect->SetFloatArray("g_lightColor", (float*)m_Color, POINTLIGHT_MAX * 4);

	CShader* shader = CShaderManager::GetInstance()->Find<CShader2D>();

	D3DXVECTOR3 Vec[3] = { D3DXVECTOR3(1.0f, -1.0f, -0.5f) , D3DXVECTOR3(-1.0f, 1.0f, 0.65f) , D3DXVECTOR3(0.0f, 0.0f, -0.5f) };
	D3DXCOLOR color[3];
	color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	color[1] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	color[2] = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	shader->Get()->SetFloatArray("g_lightRadius", (float*)m_Radius, POINTLIGHT_MAX);
	shader->Get()->SetFloatArray("g_lightPos", (float*)m_Pos, POINTLIGHT_MAX * 3);
	shader->Get()->SetFloatArray("g_lightColor", (float*)m_Color, POINTLIGHT_MAX * 4);
}


//=============================================================================
// 削除登録
//=============================================================================
void CPointLightManager::Release(CPointLight* PointLight)
{
	m_ReleaseList.push_back(PointLight);
}

//=============================================================================
// 登録されたものを削除
//=============================================================================
void CPointLightManager::ReleaseList(void)
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
