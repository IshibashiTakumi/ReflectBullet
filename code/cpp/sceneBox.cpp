//=============================================================================
// �{�b�N�X�`��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "sceneBox.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "camera.h"
#include "cameraManager.h"
#include "input.h"
#include "inputKeyboard.h"
#include "shaderManager.h"
#include "shader.h"
#include "shader3D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SIZE_MAX (50.0f)

//=============================================================================
// �I�u�W�F�N�g�N���X�̐���
//=============================================================================
CSceneBox::CSceneBox(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_VtxBuff = NULL;	//���_�o�b�t�@�|�C���^�̏�����
	m_Texture = NULL;	//�e�N�X�`���|�C���^�̏�����
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̔j��
//=============================================================================
CSceneBox::~CSceneBox()
{

}

//=============================================================================
// ������
//=============================================================================
void CSceneBox::Init(D3DXVECTOR3 Size, string& Texture, string& NormalMap, D3DXCOLOR color)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�����_���[�̎擾

	//�e�N�X�`���̓ǂݍ���
	m_Texture = *CResource::Get<CTexture>(Texture);
	m_NormalMap = *CResource::Get<CTexture>(NormalMap);

	//���_�u�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (VERTEX_NUM * 6),
		D3DUSAGE_WRITEONLY, //�m�ۂ���o�b�t�@�T�C�Y
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED, //�g�p���钸�_�t�H�[�}�b�g
		&m_VtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0); //���_���ւ̃|�C���^���擾

	for (int nCnt = 0; nCnt < (VERTEX_NUM * 6); nCnt++)
	{
		pVtx[nCnt].col = color;
	}

	D3DXVECTOR3 _Size = D3DXVECTOR3(Size.x * 0.5f, Size.y * 0.5f, Size.z * 0.5f);

	//���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, _Size.z / SIZE_MAX);
	pVtx[3].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.z / SIZE_MAX);

	pVtx[0].pos = D3DXVECTOR3(_Size.x, _Size.y, -_Size.z);
	pVtx[1].pos = D3DXVECTOR3(-_Size.x, _Size.y, -_Size.z);
	pVtx[2].pos = D3DXVECTOR3(_Size.x, _Size.y, _Size.z);
	pVtx[3].pos = D3DXVECTOR3(-_Size.x, _Size.y, _Size.z);

	for (int count = 0; count < VERTEX_NUM; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//����
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, _Size.z / SIZE_MAX);
	pVtx[7].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.z / SIZE_MAX);

	pVtx[4].pos = D3DXVECTOR3(_Size.x, -_Size.y, _Size.z);
	pVtx[5].pos = D3DXVECTOR3(-_Size.x, -_Size.y, _Size.z);
	pVtx[6].pos = D3DXVECTOR3(_Size.x, -_Size.y, -_Size.z);
	pVtx[7].pos = D3DXVECTOR3(-_Size.x, -_Size.y, -_Size.z);

	for (int count = VERTEX_NUM; count < VERTEX_NUM * 2; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//����
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[11].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[8].pos = D3DXVECTOR3(-_Size.x, _Size.y, _Size.z);
	pVtx[9].pos = D3DXVECTOR3(-_Size.x, _Size.y, -_Size.z);
	pVtx[10].pos = D3DXVECTOR3(-_Size.x, -_Size.y, _Size.z);
	pVtx[11].pos = D3DXVECTOR3(-_Size.x, -_Size.y, -_Size.z);

	for (int count = VERTEX_NUM * 2; count < VERTEX_NUM * 3; count++) pVtx[count].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	//�O��
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[15].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[12].pos = D3DXVECTOR3(_Size.x, _Size.y, _Size.z);
	pVtx[13].pos = D3DXVECTOR3(-_Size.x, _Size.y, _Size.z);
	pVtx[14].pos = D3DXVECTOR3(_Size.x, -_Size.y, _Size.z);
	pVtx[15].pos = D3DXVECTOR3(-_Size.x, -_Size.y, _Size.z);

	for (int count = VERTEX_NUM * 3; count < VERTEX_NUM * 4; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//�E��
	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[19].tex = D3DXVECTOR2(_Size.z / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[16].pos = D3DXVECTOR3(_Size.x, _Size.y, -_Size.z);
	pVtx[17].pos = D3DXVECTOR3(_Size.x, _Size.y, _Size.z);
	pVtx[18].pos = D3DXVECTOR3(_Size.x, -_Size.y, -_Size.z);
	pVtx[19].pos = D3DXVECTOR3(_Size.x, -_Size.y, _Size.z);

	for (int count = VERTEX_NUM * 4; count < VERTEX_NUM * 5; count++) pVtx[count].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//����
	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[21].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(0.0f, _Size.y / SIZE_MAX);
	pVtx[23].tex = D3DXVECTOR2(_Size.x / SIZE_MAX, _Size.y / SIZE_MAX);

	pVtx[20].pos = D3DXVECTOR3(-_Size.x, _Size.y, -_Size.z);
	pVtx[21].pos = D3DXVECTOR3(_Size.x, _Size.y, -_Size.z);
	pVtx[22].pos = D3DXVECTOR3(-_Size.x, -_Size.y, -_Size.z);
	pVtx[23].pos = D3DXVECTOR3(_Size.x, -_Size.y, -_Size.z);

	for (int count = VERTEX_NUM * 5; count < VERTEX_NUM * 6; count++) pVtx[count].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	m_VtxBuff->Unlock();
}

//=============================================================================
// ���
//=============================================================================
void CSceneBox::Uninit(void)
{
	ResourceRelease(m_VtxBuff);	//���_�o�b�t�@�̉��
}

//=============================================================================
// �`��
//=============================================================================
void CSceneBox::Draw(int num)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾 
	CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();		//�J�����̎擾
	CShaderManager::GetInstance()->Find<CShader3D>();	//�V�F�[�_�̎擾

	//���[���h�}�g���b�N�X�̐ݒ�
	SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_3D)); //�f�[�^�Ԋu

	pDevice->SetFVF(FVF_VERTEX_3D);	//���_�t�H�[�}�b�g�̐ݒ�

	CShaderManager::GetInstance()->Begin<CShader3D>(num, m_Transform->mtxWorld, pCamera->m_MtxView, pCamera->m_MtxProjection, m_Texture, m_NormalMap);

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (4 * nCnt), 2); 
	}

	CShaderManager::GetInstance()->End();
}

