//=============================================================================
// Z�e�N�X�`�����������_���[
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "zTexRenderer.h"
#include "renderer.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CZTexRenderer* CZTexRenderer::Instance = NULL;	//�C���X�^���X������

//=============================================================================
// �N���X�̐���
//=============================================================================
CZTexRenderer::CZTexRenderer()
{

}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CZTexRenderer::~CZTexRenderer()
{

}

//=============================================================================
// ������
//=============================================================================
void CZTexRenderer::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_Texture, NULL);
	m_Texture->GetSurfaceLevel(0, &m_Surface);

	pDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_Zbuffer, NULL);
}

//=============================================================================
// �f�o�C�X�̉��
//=============================================================================
void CZTexRenderer::Uninit(void)
{
	ResourceRelease(m_Texture);
	ResourceRelease(m_Surface);
	ResourceRelease(m_Zbuffer);
	DestroyInstance();
}

//=============================================================================
// �`��J�n
//=============================================================================
void CZTexRenderer::Begin(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	//��ʂ̃N���A
	pDevice->SetRenderTarget(0, m_Surface);
	for (int count = 1; count < RENDERTARGET_MAX; count++) pDevice->SetRenderTarget(count, NULL);

	pDevice->SetDepthStencilSurface(m_Zbuffer);

	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	SUCCEEDED(pDevice->BeginScene());	//�`��J�n
}

//=============================================================================
// �`��I��
//=============================================================================
void CZTexRenderer::End(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	pDevice->EndScene(); //�`��I��
}