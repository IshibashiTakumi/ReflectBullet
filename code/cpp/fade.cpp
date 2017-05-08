//=============================================================================
// ��ʑJ��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "modeManager.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"
#include "resource.h"
#include "texture.h"
#include "ShaderManager.h"
#include "shader.h"
#include "forwardShader2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ALPHA_AMOUNT (0.012f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CFade* CFade::Instance = NULL;	//�C���X�^���X������

//=============================================================================
// �I�u�W�F�N�g�N���X�̐���
//=============================================================================
CFade::CFade()
{
	m_NextMode = NULL;
	m_fade = FADE_IN;
	m_VtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^�̏�����
	m_Texture = NULL;	//�e�N�X�`���ւ̃|�C���^�̏�����
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̔j��
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// Fade�̏�����
//=============================================================================
void CFade::Init(D3DXCOLOR color, const string& TexName, const string& MaskName)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	m_colorFade = color;	//�t�F�[�h�̏�����
	m_fade = FADE_IN;		//�t�F�[�h��Ԃ̏�����

							 //���_�u�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY, //�m�ۂ���o�b�t�@�T�C�Y
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED, //�g�p���钸�_�t�H�[�}�b�g
								&m_VtxBuff,
								NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	//�e�N�X�`���̓ǂݍ���
	m_Texture = *CResource::Get<CTexture>(TexName);
	m_Mask = *CResource::Get<CTexture>(MaskName);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�w�i�̏�����
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	m_VtxBuff->Unlock();
}

//=============================================================================
// Fade�̉��
//=============================================================================
void CFade::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//���_�o�b�t�@�̉��
}

//=============================================================================
// Fade�̍X�V
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	if (m_fade == FADE_IN)
	{
		m_colorFade.a -= ALPHA_AMOUNT;

		if (m_colorFade.a <= 0.0f)
		{
			m_colorFade.a = 0.0f;
			m_fade = FADE_NONE;
		}
	}

	else if (m_fade == FADE_OUT)
	{
		m_colorFade.a += ALPHA_AMOUNT;

		if (m_colorFade.a >= 1.0f)
		{
			m_colorFade.a = 1.0f;

			m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

			pVtx[0].col = m_colorFade;
			pVtx[1].col = m_colorFade;
			pVtx[2].col = m_colorFade;
			pVtx[3].col = m_colorFade;

			m_VtxBuff->Unlock();

			CModeManager::GetInstance()->SetMode(m_NextMode); //���[�h�Z�b�g
			m_fade = FADE_IN;
		}
	}

	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	m_VtxBuff->Unlock();
}

//=============================================================================
// Fade�̕`��
//=============================================================================
void CFade::Draw(int pass)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾 
	CShaderManager::GetInstance()->Find<CForwardShader2D>();	//�V�F�[�_�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //�f�[�^�Ԋu

	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	float Criteria = 1.0f - m_colorFade.a;
	CShaderManager::GetInstance()->Begin<CForwardShader2D>(pass, m_Texture, m_Mask, Criteria);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	CShaderManager::GetInstance()->End();
}

//=============================================================================
// Fade�̊J�n
//=============================================================================
void CFade::Start(CMode *NextMode)
{
	m_NextMode = NextMode;
	m_fade = FADE_OUT;
}

//=============================================================================
// Fade�̎擾
//=============================================================================
FADE CFade::GetFade(void)
{
	return m_fade;
}