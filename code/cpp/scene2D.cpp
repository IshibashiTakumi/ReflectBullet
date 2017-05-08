//=============================================================================
// 2D�`��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "ShaderManager.h"
#include "shader.h"
#include "forwardShader2D.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CScene2D::CScene2D(CTransform* Transform) : CScene(Transform, PRIORITY_2D)
{
	m_VtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^�̏�����
	m_Texture = NULL;	//�e�N�X�`���ւ̃|�C���^�̏�����
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 2D�|���S��������
//=============================================================================
void CScene2D::Init(D3DXVECTOR2 Size, string& TexName, D3DXCOLOR color, bool Noise)
{

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	m_Size.x = Size.x;
	m_Size.y = Size.y;

	m_Noise = Noise;
	m_Criteria = 0.0f;

	float Width, Height, Angle, Length;
	Width = (m_Size.x * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transform�ŕό`������
	Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transform�ŕό`��������
	Angle = atan2f(Width, Height);							//�Ίp���̊p�x
	Length = sqrtf(Width * Width + Height * Height) * 0.5f; //�Ίp���̒���

															//�e�N�X�`���̓ǂݍ���
	m_Texture = *CResource::Get<CTexture>(TexName);
	m_Mask = *CResource::Get<CTexture>("TextureNone.jpg");

	//���_�u�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
		D3DUSAGE_WRITEONLY, //�m�ۂ���o�b�t�@�T�C�Y
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, //�g�p���钸�_�t�H�[�}�b�g
		&m_VtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

											 //�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�|���S���̏�����
	pVtx[0].pos.x = m_LocalTransform->Pos.x - sinf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[0].pos.y = m_LocalTransform->Pos.y - cosf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_LocalTransform->Pos.x + sinf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[1].pos.y = m_LocalTransform->Pos.y - cosf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_LocalTransform->Pos.x - sinf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[2].pos.y = m_LocalTransform->Pos.y + cosf(Angle - m_LocalTransform->Rot.z) * Length;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_LocalTransform->Pos.x + sinf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[3].pos.y = m_LocalTransform->Pos.y + cosf(Angle + m_LocalTransform->Rot.z) * Length;
	pVtx[3].pos.z = 0.0f;

	//���W�ϊ��p�W���̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	m_VtxBuff->Unlock();
}

//=============================================================================
// 2D�|���S�����
//=============================================================================
void CScene2D::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//���_�o�b�t�@�̉�� 
}

//=============================================================================
// 2D�|���S���X�V
//=============================================================================
void CScene2D::Update(void)
{
	float Width, Height, Angle, Length;
	Width = (m_Size.x * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transform�ŕό`������
	Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transform�ŕό`��������
	Angle = atan2f(Width, Height);							//�Ίp���̊p�x
	Length = sqrtf(Width * Width + Height * Height) * 0.5f; //�Ίp���̒���

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	pVtx[0].pos.x = m_Transform->Pos.x - sinf(Angle + m_Transform->Rot.z) * Length;
	pVtx[0].pos.y = m_Transform->Pos.y - cosf(Angle + m_Transform->Rot.z) * Length;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_Transform->Pos.x + sinf(Angle - m_Transform->Rot.z) * Length;
	pVtx[1].pos.y = m_Transform->Pos.y - cosf(Angle - m_Transform->Rot.z) * Length;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_Transform->Pos.x - sinf(Angle - m_Transform->Rot.z) * Length;
	pVtx[2].pos.y = m_Transform->Pos.y + cosf(Angle - m_Transform->Rot.z) * Length;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_Transform->Pos.x + sinf(Angle + m_Transform->Rot.z) * Length;
	pVtx[3].pos.y = m_Transform->Pos.y + cosf(Angle + m_Transform->Rot.z) * Length;
	pVtx[3].pos.z = 0.0f;

	m_VtxBuff->Unlock();
}

//=============================================================================
// 2D�|���S���`��
//=============================================================================
void CScene2D::Draw(int pass)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾 
	CShaderManager::GetInstance()->Find<CForwardShader2D>();	//�V�F�[�_�̎擾

																//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //�f�[�^�Ԋu

	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	CShaderManager::GetInstance()->Begin<CForwardShader2D>(pass, m_Texture, m_Mask, m_Criteria, m_Noise);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
		0, //�ŏ��̒��_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u

	CShaderManager::GetInstance()->End();
}