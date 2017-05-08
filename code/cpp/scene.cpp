//=============================================================================
// Scene���N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "sceneManager.h"
#include "object.h"
#include "renderer.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CScene::CScene(CTransform* Transform, PRIORITY Priority)
{
	m_Priority = Priority;
	m_Light = true;
	m_Cull = D3DCULL_CCW;

	m_LocalTransform = Transform;
	m_Transform = new CTransform();

	CSceneManager::GetInstance()->SetObject(Priority, this);	//�o�^
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CScene::~CScene()
{
	delete m_Transform;
	delete m_LocalTransform;
}

//=============================================================================
// �ʒu�C��
//=============================================================================
void CScene::Transformation(void)
{
	m_Transform->Pos = (m_Object->m_Transform->Pos + m_LocalTransform->Pos);
	m_Transform->Rot = (m_Object->m_Transform->Rot + m_LocalTransform->Rot);
	m_Transform->Scl = D3DXVECTOR3(m_Object->m_Transform->Scl.x * m_LocalTransform->Scl.x,
											   	m_Object->m_Transform->Scl.y * m_LocalTransform->Scl.y,
												m_Object->m_Transform->Scl.z * m_LocalTransform->Scl.z);
}

//=============================================================================
// �`��J�n
//=============================================================================
void CScene::Begin(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	pDevice->SetRenderState(D3DRS_CULLMODE, m_Cull); //�J�����O���@
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); // ���C�e�B���O�𖳌�������
}

//=============================================================================
// �`��I��
//=============================================================================
void CScene::End(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�J�����O���@
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE); // ���C�e�B���O�𖳌�������
}
