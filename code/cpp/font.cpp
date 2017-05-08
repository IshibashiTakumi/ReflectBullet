//=============================================================================
// �����`��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "font.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "ShaderManager.h"
#include "shader.h"
#include "forwardShader2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WIDTH_FONT_NUM ( 10 )									//�t�H���g�̉��̕�����
#define HEIGHT_FONT_NUM ( 7 )									//�t�H���g�̍����̕�����
#define FONTINTERVAL_WIDTH ( 1.0f / (float)WIDTH_FONT_NUM )		//�e�N�X�`���̉��`��Ԋu
#define FONTINTERVAL_HEIGHT ( 1.0f / (float)HEIGHT_FONT_NUM )	//�e�N�X�`���̍����`��Ԋu
#define FONT_TYPE_MAX ( WIDTH_FONT_NUM * HEIGHT_FONT_NUM + 1 )	//�t�H���g��ނ̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
string CFont::m_Font = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ,.!?abcdefghijklmnopqrstuvwxyz:-#/";	//���͕����̎��

//=============================================================================
// �N���X�̐���
//=============================================================================
CFont::CFont(CTransform* Transform) : CScene(Transform, PRIORITY_2D)
{
	m_VtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^�̏�����
	m_Texture = NULL;	//�e�N�X�`���ւ̃|�C���^�̏�����
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CFont::~CFont()
{
	
}

//=============================================================================
// 2D�|���S��������
//=============================================================================
void CFont::Init(D3DXVECTOR2 Size, string word, D3DXCOLOR color)
{
	
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	m_Size.x = Size.x;
	m_Size.y = Size.y;

	m_WordMax = word.size();

	float Width, Height, Angle, Length;
	Width = ((m_Size.x / m_WordMax) * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transform�ŕό`������
	Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transform�ŕό`��������
	Angle = atan2f(Width, Height);							//�Ίp���̊p�x
	Length = sqrtf(Width * Width + Height * Height) * 0.5f; //�Ίp���̒���

	//�e�N�X�`���̓ǂݍ���
	m_Texture = *CResource::Get<CTexture>("font.png");

	//���_�u�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (VERTEX_NUM * m_WordMax),
		D3DUSAGE_WRITEONLY, //�m�ۂ���o�b�t�@�T�C�Y
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, //�g�p���钸�_�t�H�[�}�b�g
		&m_VtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	D3DXVECTOR2 tex = Vec2Init();
	float width = m_Size.x / m_WordMax;
	float pos = ((m_LocalTransform->Pos.x - (m_Size.x * 0.5f)) + (width * 0.5f));
	for (int count = 0; count < m_WordMax; count++)
	{
		//�e�N�X�`�����W�̐ݒ�
		if (SetScan(word[count], tex))
		{
			pVtx[count * 4 + 0].tex = D3DXVECTOR2(tex.x, tex.y);
			pVtx[count * 4 + 1].tex = D3DXVECTOR2(tex.x + FONTINTERVAL_WIDTH, tex.y);
			pVtx[count * 4 + 2].tex = D3DXVECTOR2(tex.x, tex.y + FONTINTERVAL_HEIGHT);
			pVtx[count * 4 + 3].tex = D3DXVECTOR2(tex.x + FONTINTERVAL_WIDTH, tex.y + FONTINTERVAL_HEIGHT);
		}
		else
		{
			for (int cnt = 0; cnt < 4; cnt++) pVtx[count * 4 + cnt].tex = Vec2Init();
		}

		pVtx[count * 4 + 0].pos.x = (pos + (width * count)) - sinf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 0].pos.y = m_LocalTransform->Pos.y - cosf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 0].pos.z = 0.0f;
		pVtx[count * 4 + 1].pos.x = (pos + (width * count)) + sinf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 1].pos.y = m_LocalTransform->Pos.y - cosf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 1].pos.z = 0.0f;
		pVtx[count * 4 + 2].pos.x = (pos + (width * count)) - sinf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 2].pos.y = m_LocalTransform->Pos.y + cosf(Angle - m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 2].pos.z = 0.0f;
		pVtx[count * 4 + 3].pos.x = (pos + (width * count)) + sinf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 3].pos.y = m_LocalTransform->Pos.y + cosf(Angle + m_LocalTransform->Rot.z) * Length;
		pVtx[count * 4 + 3].pos.z = 0.0f;
	}
	
	for (int count = 0; count < VERTEX_NUM * m_WordMax; count++)
	{
		pVtx[count].rhw = 1.0f;		//���W�ϊ��p�W���̐ݒ�
		pVtx[count].col = color;	//���_�J���[�̐ݒ�
	}

	m_VtxBuff->Unlock();
}

//=============================================================================
// 2D�|���S�����
//=============================================================================
void CFont::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//���_�o�b�t�@�̉�� 
}

//=============================================================================
// 2D�|���S���X�V
//=============================================================================
void CFont::Update(void)
{
	//float Width, Height, Angle, Length;
	//Width = (m_Size.x * m_Transform->Scl.x) * cosf(m_Transform->Rot.y);	//Transform�ŕό`������
	//Height = (m_Size.y * m_Transform->Scl.y)* cosf(m_Transform->Rot.x);	//Transform�ŕό`��������
	//Angle = atan2f(Width, Height);							//�Ίp���̊p�x
	//Length = sqrtf(Width * Width + Height * Height) * 0.5f; //�Ίp���̒���

	//VERTEX_2D *pVtx;
	//m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	//pVtx[0].pos.x = m_Transform->Pos.x - sinf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[0].pos.y = m_Transform->Pos.y - cosf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[0].pos.z = 0.0f;
	//pVtx[1].pos.x = m_Transform->Pos.x + sinf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[1].pos.y = m_Transform->Pos.y - cosf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[1].pos.z = 0.0f;
	//pVtx[2].pos.x = m_Transform->Pos.x - sinf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[2].pos.y = m_Transform->Pos.y + cosf(Angle - m_Transform->Rot.z) * Length;
	//pVtx[2].pos.z = 0.0f;
	//pVtx[3].pos.x = m_Transform->Pos.x + sinf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[3].pos.y = m_Transform->Pos.y + cosf(Angle + m_Transform->Rot.z) * Length;
	//pVtx[3].pos.z = 0.0f;

	//m_VtxBuff->Unlock();
}

//=============================================================================
// 2D�|���S���`��
//=============================================================================
void CFont::Draw(int pass)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾 
	CShaderManager::GetInstance()->Find<CForwardShader2D>();	//�V�F�[�_�̎擾

																//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D)); //�f�[�^�Ԋu

	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	CShaderManager::GetInstance()->Begin<CForwardShader2D>(pass, m_Texture);

	for (int wordCount = 0; wordCount < m_WordMax; wordCount++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
			wordCount * 4, //�ŏ��̒��_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u
	}

	CShaderManager::GetInstance()->End();
}

//=============================================================================
// UV���W����
//=============================================================================
bool CFont::SetScan(char font, D3DXVECTOR2& tex)
{
	for (int count = 0; count < m_Font.size(); count++)
	{
		if (m_Font[count] == font)
		{
			//�e�N�X�`�����W�̊���U��(������W)
			tex.x = (count % WIDTH_FONT_NUM) * FONTINTERVAL_WIDTH;
			tex.y = (count / WIDTH_FONT_NUM) * FONTINTERVAL_HEIGHT;

			return true;
		}
	}

	return false;
}

//=============================================================================
// �F�ύX
//=============================================================================
void CFont::SetColor(D3DXCOLOR color)
{
	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	for (int count = 0; count < VERTEX_NUM * m_WordMax; count++)
	{
		pVtx[count].col = color;	//���_�J���[�̐ݒ�
	}

	m_VtxBuff->Unlock();
}