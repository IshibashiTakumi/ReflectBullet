//=============================================================================
// Resource���N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"
#include "modelX.h"
#include "resource.h"
#include "renderer.h"
#include "manager.h"

using namespace directory;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �N���X�̐���
//=============================================================================
CModelX::CModelX(const string &FileName)
{
	
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	m_ModelX = new ModelX;

	m_ModelX->Mesh = NULL;		//���b�V�����̏�����
	m_ModelX->BuffMat = NULL;	//�}�e���A�����̏�����
	m_ModelX->MeshMat = NULL;	//�}�e���A�����̏�����
	m_ModelX->MeshTex = NULL;	//���b�V���̃e�N�X�`���̏�����

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX((Model_Directory + FileName).c_str(),	//�ǂݍ��ރt�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_ModelX->BuffMat,		//�}�e���A�����
		NULL,
		&m_ModelX->NumMat,		//�}�e���A���̐�
		&m_ModelX->Mesh);		//���b�V�����

						// �}�e���A���������o��
	D3DXMATERIAL*	d3Mat = (D3DXMATERIAL*)m_ModelX->BuffMat->GetBufferPointer();
	m_ModelX->MeshMat = new D3DMATERIAL9[m_ModelX->NumMat];		// ���b�V�������m��
	m_ModelX->MeshTex = new LPDIRECT3DTEXTURE9[m_ModelX->NumMat];// �e�N�X�`�����m��
	for (int nCntMat = 0; nCntMat < (int)m_ModelX->NumMat; nCntMat++)
	{
		m_ModelX->MeshMat[nCntMat] = d3Mat[nCntMat].MatD3D;			// �}�e���A�����Z�b�g
		m_ModelX->MeshTex[nCntMat] = NULL;	// �e�N�X�`��������
									// �g�p���Ă���e�N�X�`��������Γǂݍ���
		if (d3Mat[nCntMat].pTextureFilename != NULL && lstrlen(d3Mat[nCntMat].pTextureFilename) > 0)
		{
			// �e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFile(
				pDevice,
				d3Mat[nCntMat].pTextureFilename,
				&m_ModelX->MeshTex[nCntMat]);
		}
	}
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CModelX::~CModelX()
{
	if (m_ModelX->Mesh != NULL)
	{
		m_ModelX->Mesh->Release(); //���b�V���̉��
		m_ModelX->Mesh = NULL;
	}

	if (m_ModelX->BuffMat != NULL)
	{
		m_ModelX->BuffMat->Release(); //�}�e���A���̉��
		m_ModelX->BuffMat = NULL;
	}

	for (int nCntMat = 0; nCntMat < (int)m_ModelX->NumMat; nCntMat++)
	{
		ResourceRelease(m_ModelX->MeshTex[nCntMat]);
	}

	delete[] m_ModelX->MeshTex;
	m_ModelX->MeshTex = NULL;
	delete[] m_ModelX->MeshMat;
	m_ModelX->MeshMat = NULL;
	delete m_ModelX;
}

//CModelX::operator CModelX*() const
//{
//	return *this;
//}

CModelX::operator ModelX*() const
{
	//���g�����݂��Ȃ�������nullptr��Ԃ�
	if (this == nullptr) return nullptr;
	return m_ModelX;
}