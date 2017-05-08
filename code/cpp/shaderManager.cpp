//=============================================================================
// シェーダ管理クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "shaderManager.h"
#include "shader.h"
#include "shader2D.h"
#include "shader3D.h"
#include "shaderX.h"
#include "forwardShader2D.h"

//=============================================================================
// グローバル変数
//=============================================================================
CShaderManager* CShaderManager::Instance = NULL;	//インスタンス

//=============================================================================
// シェーダクラスの生成
//=============================================================================
void CShaderManager::Init(void)
{
	m_List.push_back(CShader::Create<CShader2D>((string)"Shader2D.cso"));
	m_List.push_back(CShader::Create<CShader3D>((string)"Shader.cso"));
	m_List.push_back(CShader::Create<CShaderX>((string)"ShaderX.cso"));
	m_List.push_back(CShader::Create<CForwardShader2D>((string)"ForwardShader2D.cso"));
}

//=============================================================================
// シェーダクラスの破棄
//=============================================================================
void CShaderManager::Uninit(void)
{
	for each (auto list in m_List)
	{
		list->Uninit();
	}
	m_List.clear();
}

//=============================================================================
// 描画終了
//=============================================================================
void CShaderManager::End(void)
{
	m_Current->End();
}
