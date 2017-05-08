//=============================================================================
// 3D�`��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "sceneWave.h"
#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "camera.h"
#include "cameraManager.h"
#include "object.h"
#include "objectManager.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CSceneWave::CSceneWave(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_VtxBuff = NULL;	//���_�o�b�t�@�|�C���^�̏�����
	m_Texture = NULL;	//�e�N�X�`���|�C���^�̏�����
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CSceneWave::~CSceneWave()
{

}

//=============================================================================
//  ������
//=============================================================================
void CSceneWave::Init(D3DXVECTOR2 Size, string& TexName, D3DXCOLOR color, D3DXVECTOR2 tex)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance() -> GetDevice( ); //�f�o�C�X�̎擾 

	//�e�N�X�`���̓ǂݍ���
	m_Texture = *CResource::Get<CTexture>(TexName);

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
void CSceneWave::Uninit( void )
{
	ResourceRelease(m_VtxBuff);	//���_�o�b�t�@�̉�� 
}

//=============================================================================
// �`��
//=============================================================================
void CSceneWave::Draw(int num)
{
	
	//LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance() -> GetDevice( ); //�f�o�C�X�̎擾 

	////���[���h�}�g���b�N�X�̐ݒ�
	//SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);
	//
	////���[���h�}�g�b���N�X�̐ݒ�
	//pDevice -> SetTransform( D3DTS_WORLD, &m_Transform->mtxWorld );

	////���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	//pDevice -> SetStreamSource( 0,
	//							m_VtxBuff,
	//							0,
	//							sizeof( VERTEX_3D ) ); //�f�[�^�Ԋu

	////���_�t�H�[�}�b�g�̐ݒ�
	//pDevice -> SetFVF( FVF_VERTEX_3D );

	////�e�N�X�`���̐ݒ�
	//pDevice -> SetTexture( 0, m_Texture );

	//pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
	//							0, //�ŏ��̒��_�̃C���f�b�N�X
	//							2 ); //�`�悷��v���~�e�B�u��








	//LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 
	//ID3DXEffect* pEffect = CRenderer::GetInstance()->GetEffect();
	//CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();

	//D3DXMATRIX mtxScl, mtxRot, mtxTrans;

	////���[���h�}�g���b�N�X�̐ݒ�
	//SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);

	////���[���h�}�g�b���N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &m_Transform->mtxWorld);

	////���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	//pDevice->SetStreamSource(0,
	//	m_VtxBuff,
	//	0,
	//	sizeof(VERTEX_3D)); //�f�[�^�Ԋu

	//						//���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_3D);

	//// �G�t�F�N�g�ݒ�
	//pEffect->SetMatrix("g_world", &m_Transform->mtxWorld);
	//pEffect->SetMatrix("g_view", &pCamera->m_MtxView);
	//pEffect->SetMatrix("g_proj", &pCamera->m_MtxProjection);

	//pEffect->SetTexture("g_texture", m_Texture);

	//for each (auto list in CScreenTexManager::GetInstance()->GetList())
	//{
	//	pEffect->SetTexture("g_shadowMap", list->GetTexture());
	//}

	//LPDIRECT3DTEXTURE9 Texture = *CResource::Get<CTexture>("NormalMap.jpg");
	//pEffect->SetTexture("g_NormalTex", Texture);
	//pEffect->SetTexture("g_SpecularTex", *CResource::Get<CTexture>("Specular.jpg"));

	//D3DXVECTOR3 Vec[3] = { D3DXVECTOR3(1.0f, -1.0f, -0.5f) , D3DXVECTOR3(-1.0f, 1.0f, 0.65f) , D3DXVECTOR3(0.0f, 0.0f, -0.5f) };
	//m_color[0] = m_color[1] = m_color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//D3DXCOLOR(0.05f, 0.05f, 0.05f, 1.0f)

	//static float texmove = 0.0f;
	//texmove += 0.005;
	//pEffect->SetFloatArray("g_texmove", &texmove, 1);

	//pEffect->SetFloatArray("g_lightVec", (float*)Vec, 9);
	//pEffect->SetFloatArray("g_color", (float*)m_color, 12);
	//pEffect->SetFloatArray("g_CameraPos", (float*)pCamera->m_PosV, 3);

	//D3DXVECTOR2 fog;
	//fog.x = pCamera->far_z / (pCamera->far_z - pCamera->near_z);
	//fog.y = -1.0f / (pCamera->far_z - pCamera->near_z);
	//pEffect->SetFloatArray("g_Fog", (float*)fog, 2);

	//pEffect->Begin(NULL, 0);	// �e�N�j�b�N�J�n 
	//pEffect->BeginPass(num);		//�p�X�̎w��

	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
	//	0, //�ŏ��̒��_�̃C���f�b�N�X
	//	2); //�`�悷��v���~�e�B�u��

	//pEffect->EndPass();
	//pEffect->End();
}
