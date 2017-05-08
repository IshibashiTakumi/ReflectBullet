//=============================================================================
// Shader2D�N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "shader2D.h"
#include "renderer.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CShader2D::CShader2D()
{
	
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CShader2D::~CShader2D()
{

}

//=============================================================================
// �`��J�n
//=============================================================================
void CShader2D::Begin(int pass, LPDIRECT3DTEXTURE9& shadow, LPDIRECT3DTEXTURE9& position, LPDIRECT3DTEXTURE9& normal, LPDIRECT3DTEXTURE9& texture, LPDIRECT3DTEXTURE9& specular)
{
	m_Effect->SetTexture("g_ShadowMap", shadow);
	m_Effect->SetTexture("g_PositionMap", position);
	m_Effect->SetTexture("g_NormalMap", normal);
	m_Effect->SetTexture("g_DiffuseMap", texture);
	m_Effect->SetTexture("g_SpecularMap", specular);

	m_Effect->Begin(NULL, 0);	// �e�N�j�b�N�J�n 
	m_Effect->BeginPass(pass);		//�p�X�̎w��
}

//=============================================================================
// �`��I��
//=============================================================================
void CShader2D::End(void)
{
	m_Effect->EndPass();
	m_Effect->End();
}
