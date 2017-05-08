//=============================================================================
// Shader���N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "shader.h"
#include "renderer.h"
using namespace directory;

//=============================================================================
// �N���X�̐���
//=============================================================================
CShader::CShader()
{
	
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CShader::~CShader()
{

}


//=============================================================================
// �V�F�[�_�N���X�̐���
//=============================================================================
void CShader::Init(string& FileName)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�����_���[�̎擾

	// �G�t�F�N�g�ǂݍ���
	D3DXCreateEffectFromFile(pDevice, (Shader_Directory + FileName).c_str(), 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &m_Effect, &m_Error);
	if (m_Error)
	{
		// �R���p�C���G���[���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA((const char*)m_Error->GetBufferPointer());
		OutputDebugStringA("\n");
	}
	else
	{
		// �悭�킩��Ȃ��G���[
		OutputDebugStringA("�Ȃ񂩃G�t�F�N�g�ǂݍ��݂ŃG���[�o����B\n");
	}
}

//=============================================================================
// �V�F�[�_�N���X�̔j��
//=============================================================================
void CShader::Uninit(void)
{
	ResourceRelease(m_Effect);
	ResourceRelease(m_Error);
}

//=============================================================================
// �`��J�n
//=============================================================================
void CShader::Begin(void)
{
	
}

//=============================================================================
// �`��I��
//=============================================================================
void CShader::End(void)
{
	
}