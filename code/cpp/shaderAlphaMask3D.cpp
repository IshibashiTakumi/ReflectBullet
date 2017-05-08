//=============================================================================
// ShaderAlphaMask3D�N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "shaderAlphaMask3D.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CShaderAlphaMask3D::m_Texture = NULL;	//�C���X�^���X
LPDIRECT3DTEXTURE9 CShaderAlphaMask3D::m_Mask = NULL;	//�C���X�^���X

//=============================================================================
// �N���X�̐���
//=============================================================================
CShaderAlphaMask3D::CShaderAlphaMask3D()
{
	m_Texture = *CResource::Get<CTexture>("TextureNone.jpg");
	m_Mask = *CResource::Get<CTexture>("TextureNone.jpg");
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CShaderAlphaMask3D::~CShaderAlphaMask3D()
{

}

//=============================================================================
// �`��J�n
//=============================================================================
void CShaderAlphaMask3D::Begin(int pass, D3DXMATRIX& world, D3DXMATRIX& view, D3DXMATRIX& proj, LPDIRECT3DTEXTURE9& texture, LPDIRECT3DTEXTURE9& mask, float Criteria)
{
	// �G�t�F�N�g�ݒ�
	m_Effect->SetMatrix("g_world", &world);
	m_Effect->SetMatrix("g_view", &view);
	m_Effect->SetMatrix("g_proj", &proj);
	m_Effect->SetTexture("g_texture", texture);
	m_Effect->SetTexture("g_MaskTex", mask);
	m_Effect->SetFloat("g_Criteria", Criteria);

	m_Effect->Begin(NULL, 0);	// �e�N�j�b�N�J�n 
	m_Effect->BeginPass(3);		//�p�X�̎w��
}

//=============================================================================
// �`��I��
//=============================================================================
void CShaderAlphaMask3D::End(void)
{
	m_Effect->EndPass();
	m_Effect->End();
}
