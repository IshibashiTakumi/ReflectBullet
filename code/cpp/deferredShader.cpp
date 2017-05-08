//=============================================================================
// �x���V�F�[�_
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "deferredShader.h"
#include "renderer.h"
#include "camera.h"
#include "cameraManager.h"
#include "ShaderManager.h"
#include "shader.h"
#include "shader2D.h"
#include "zTexRenderer.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CDeferredShader* CDeferredShader::Instance = NULL;	//�C���X�^���X������

//=============================================================================
// �N���X�̐���
//=============================================================================
CDeferredShader::CDeferredShader()
{

}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CDeferredShader::~CDeferredShader()
{

}

//=============================================================================
// ������
//=============================================================================
void CDeferredShader::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &m_Texture[0], NULL);
	m_Texture[0]->GetSurfaceLevel(0, &m_Surface[0]);

	for (int count = 1; count < RENDERTARGET_MAX; count++)
	{
		pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_Texture[count], NULL);
		m_Texture[count]->GetSurfaceLevel(0, &m_Surface[count]);
	}

	pDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &m_Zbuffer, NULL);

	//���_�u�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,D3DPOOL_MANAGED, &m_VtxBuff, NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�|���S���̏�����
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for (int count = 0; count < VERTEX_NUM; count++)
	{
		pVtx[count].rhw = 1.0f;		//���W�ϊ��p�W���̐ݒ�
		pVtx[count].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//���_�J���[�̐ݒ�
	}
}

//=============================================================================
// �f�o�C�X�̉��
//=============================================================================
void CDeferredShader::Uninit(void)
{
	for (int count = 0; count < RENDERTARGET_MAX; count++)
	{
		ResourceRelease(m_Texture[count]);
		ResourceRelease(m_Surface[count]);
	}
	ResourceRelease(m_Zbuffer);
	DestroyInstance();
}

//=============================================================================
// �`��J�n
//=============================================================================
void CDeferredShader::Begin(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	//��ʂ̃N���A
	for (int count = 0; count < RENDERTARGET_MAX; count++) pDevice->SetRenderTarget(count, m_Surface[count]);

	pDevice->SetDepthStencilSurface(m_Zbuffer);

	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	SUCCEEDED(pDevice->BeginScene());	//�`��J�n
}

//=============================================================================
// ���������e�N�X�`�����g�����ŏI���ʕ`��
//=============================================================================
void CDeferredShader::Draw(int pass)
{
	LPDIRECT3DTEXTURE9 tex[RENDERTARGET_MAX];
	for (int count = 0; count < RENDERTARGET_MAX; count++) tex[count] = CDeferredShader::GetInstance()->GetTexture(count);
	LPDIRECT3DTEXTURE9 depth = CZTexRenderer::GetInstance()->GetTexture();

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾 
	CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();		//�J�����̎擾
	CShaderManager::GetInstance()->Find<CShader2D>();	//�V�F�[�_�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //�f�[�^�Ԋu

	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	CShaderManager::GetInstance()->Begin<CShader2D>(pass, depth, m_Texture[0], m_Texture[1], m_Texture[2], m_Texture[3]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	CShaderManager::GetInstance()->End();
}

//=============================================================================
// �`��I��
//=============================================================================
void CDeferredShader::End(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	pDevice->EndScene(); //�`��I��
}