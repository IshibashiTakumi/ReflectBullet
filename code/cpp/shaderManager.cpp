//=============================================================================
// �V�F�[�_�Ǘ��N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
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
// �O���[�o���ϐ�
//=============================================================================
CShaderManager* CShaderManager::Instance = NULL;	//�C���X�^���X

//=============================================================================
// �V�F�[�_�N���X�̐���
//=============================================================================
void CShaderManager::Init(void)
{
	m_List.push_back(CShader::Create<CShader2D>((string)"Shader2D.cso"));
	m_List.push_back(CShader::Create<CShader3D>((string)"Shader.cso"));
	m_List.push_back(CShader::Create<CShaderX>((string)"ShaderX.cso"));
	m_List.push_back(CShader::Create<CForwardShader2D>((string)"ForwardShader2D.cso"));
}

//=============================================================================
// �V�F�[�_�N���X�̔j��
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
// �`��I��
//=============================================================================
void CShaderManager::End(void)
{
	m_Current->End();
}
