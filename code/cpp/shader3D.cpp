//=============================================================================
// Shader2D�N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "shader3D.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CShader3D::m_Texture = NULL;	//�C���X�^���X
LPDIRECT3DTEXTURE9 CShader3D::m_Normal = NULL;	//�C���X�^���X

//=============================================================================
// �N���X�̐���
//=============================================================================
CShader3D::CShader3D()
{
	m_Texture = *CResource::Get<CTexture>("TextureNone.jpg");
	m_Normal = *CResource::Get<CTexture>("NormalNone.jpg");
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CShader3D::~CShader3D()
{

}

//=============================================================================
// �`��J�n
//=============================================================================
void CShader3D::Begin(int pass, D3DXMATRIX& world, D3DXMATRIX& view, D3DXMATRIX& proj, LPDIRECT3DTEXTURE9& texture, LPDIRECT3DTEXTURE9& normal)
{
	// �G�t�F�N�g�ݒ�
	m_Effect->SetMatrix("g_world", &world);
	m_Effect->SetMatrix("g_view", &view);
	m_Effect->SetMatrix("g_proj", &proj);
	m_Effect->SetTexture("g_texture", texture);
	m_Effect->SetTexture("g_NormalTex", normal);

	m_Effect->Begin(NULL, 0);	// �e�N�j�b�N�J�n 
	m_Effect->BeginPass(pass);		//�p�X�̎w��
}

//=============================================================================
// �`��I��
//=============================================================================
void CShader3D::End(void)
{
	m_Effect->EndPass();
	m_Effect->End();
}
