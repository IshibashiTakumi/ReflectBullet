//=============================================================================
// �^�C���`��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "time.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "object.h"
#include "mode.h"
#include "fade.h"
#include "title.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TIMEINTERVAL_WIDTH ( 0.1f )								//�e�N�X�`���̉��`��Ԋu
#define TIMEINTERVAL_HEIGHT ( 1.0f )							//�e�N�X�`���̍����`��Ԋu

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �I�u�W�F�N�g�N���X�̐���
//=============================================================================
CTime::CTime(CTransform* Transform) : CScene(Transform, PRIORITY_2D)
{
	m_VtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^�̏�����
	m_Texture = NULL;	//�e�N�X�`���ւ̃|�C���^�̏�����

	m_nCounterTimeAnim = 0; //�A�j���[�V�����J�E���^�[�̏�����
	m_nPatternTimeAnim = 0; //�A�j���[�V�����p�^�[��No�̏�����
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̔j��
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// ������
//=============================================================================
void CTime::Init(int digit, int time, D3DXVECTOR2 size, string texName)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾

	m_LimitTime = time;
	float IntervalWidth = size.x / digit; //�^�C���Ԋu�̌v�Z�p
	m_Digit = digit;

	//���_�u�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (VERTEX_NUM * m_Digit),
		D3DUSAGE_WRITEONLY, //�m�ۂ���o�b�t�@�T�C�Y
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED, //�g�p���钸�_�t�H�[�}�b�g
		&m_VtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

											 //�e�N�X�`���̓ǂݍ���
	m_Texture = *CResource::Get<CTexture>(texName);

	float pos = (m_LocalTransform->Pos.x - size.x * 0.5f) + IntervalWidth * 0.5f;

	for (int nCount = 0; nCount < m_Digit; nCount++)
	{
		pVtx[0 + nCount * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + nCount * 4].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2 + nCount * 4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + nCount * 4].tex = D3DXVECTOR2(0.1f, 1.0f);

		//�ʒu�̏�����
		pVtx[0 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) - (IntervalWidth * 0.5f), m_LocalTransform->Pos.y - (size.y * 0.5f), 0.0f);
		pVtx[1 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) + (IntervalWidth * 0.5f), m_LocalTransform->Pos.y - (size.y * 0.5f), 0.0f);
		pVtx[2 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) - (IntervalWidth * 0.5f), m_LocalTransform->Pos.y + (size.y * 0.5f), 0.0f);
		pVtx[3 + nCount * 4].pos = D3DXVECTOR3((pos + (IntervalWidth * nCount)) + (IntervalWidth * 0.5f), m_LocalTransform->Pos.y + (size.y * 0.5f), 0.0f);

		pVtx[0 + nCount * 4].rhw = 1.0f;
		pVtx[1 + nCount * 4].rhw = 1.0f;
		pVtx[2 + nCount * 4].rhw = 1.0f;
		pVtx[3 + nCount * 4].rhw = 1.0f;

		pVtx[0 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
		pVtx[1 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
		pVtx[2 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
		pVtx[3 + nCount * 4].col = D3DCOLOR_RGBA(20, 100, 255, 255);
	}

	//�e�N�X�`���̈ʒu�v�Z
	for (int nCount = 0; nCount < m_Digit; nCount++)
	{
		float Count = (float)m_Digit - (nCount + 1);

		int Time = (int)(m_LimitTime / pow(10, Count)) % 10;

		pVtx[0 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[1 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
		pVtx[2 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[3 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
	}

	m_VtxBuff->Unlock();
}
//=============================================================================
// ���
//=============================================================================
void CTime::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//���_�o�b�t�@�̉�� 
}
//=============================================================================
// �X�V
//=============================================================================
void CTime::Update(void)
{
	VERTEX_2D *pVtx;

	float oldg_nTime; //��O�̃^�C���̒l
	float Count;
	int Time;

	if (m_LimitTime > 0) oldg_nTime = m_LimitTime;
	else oldg_nTime = 0;


	//�e�N�X�`���̏���
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̈ʒu�v�Z
	for (int nCount = 0; nCount < m_Digit; nCount++)
	{
		Count = (float)m_Digit - (nCount + 1);

		Time = (int)(oldg_nTime / pow(10, Count)) % 10;

		pVtx[0 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[1 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
		pVtx[2 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH;
		pVtx[3 + nCount * 4].tex.x = Time * TIMEINTERVAL_WIDTH + TIMEINTERVAL_WIDTH;
	}

	m_VtxBuff->Unlock();

	if (m_LimitTime <= 1)
	{
		CFade::GetInstance()->Start(new CTitle);
	}

	m_LimitTime -= FrameTime();
}
//=============================================================================
// �`��
//=============================================================================
void CTime::Draw(int pass)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0,
		m_VtxBuff,
		0,
		sizeof(VERTEX_2D)); //�f�[�^�Ԋu

							//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_Texture);

	//�|���S���̕`��
	for (int Count = 0; Count < m_Digit; Count++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
			Count * 4, //�ŏ��̒��_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
	}
}