//=============================================================================
// 3D�`��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "camera.h"
#include "cameraManager.h"
#include "object.h"
#include "objectManager.h"
#include "shaderManager.h"
#include "shader.h"
#include "shader3D.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CScene3D::CScene3D(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_VtxBuff = NULL;	//���_�o�b�t�@�|�C���^�̏�����
	m_Texture = NULL;	//�e�N�X�`���|�C���^�̏�����
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
//  ������
//=============================================================================
void CScene3D::Init(D3DXVECTOR2 Size, string& Texture, string& NormalMap, D3DXCOLOR color, D3DXVECTOR2 tex)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance() -> GetDevice( ); //�f�o�C�X�̎擾 

	//�e�N�X�`���̓ǂݍ���
	m_Texture = *CResource::Get<CTexture>(Texture);
	m_NormalMap = *CResource::Get<CTexture>(NormalMap);

	//���_�u�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_NUM,
		D3DUSAGE_WRITEONLY, //�m�ۂ���o�b�t�@�T�C�Y
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED, //�g�p���钸�_�t�H�[�}�b�g
		&m_VtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	m_VtxBuff -> Lock( 0, 0, ( void** )&pVtx, 0 ); //���_���ւ̃|�C���^���擾

	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2(tex.x, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, tex.y);
	pVtx[ 3 ].tex = D3DXVECTOR2(tex.x, tex.y);

	float Width = Size.x * 0.5f, Depth = Size.y * 0.5f;
	pVtx[ 0 ].pos = D3DXVECTOR3( -Width, 0, Depth);
	pVtx[ 1 ].pos = D3DXVECTOR3(Width, 0, Depth);
	pVtx[ 2 ].pos = D3DXVECTOR3( -Width, 0, -Depth);
	pVtx[ 3 ].pos = D3DXVECTOR3(Width, 0, -Depth);

	for (int Count = 0; Count < VERTEX_NUM; Count++)
	{
		pVtx[Count].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[Count].col = color;
	}

	m_VtxBuff -> Unlock( );
}

//=============================================================================
// ���
//=============================================================================
void CScene3D::Uninit( void )
{
	ResourceRelease(m_VtxBuff);	//���_�o�b�t�@�̉�� 
}

//=============================================================================
// �`��
//=============================================================================
void CScene3D::Draw(int num)
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

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); 

	CShaderManager::GetInstance()->End();
}
