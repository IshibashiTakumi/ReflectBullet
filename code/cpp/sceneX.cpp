//=============================================================================
// X���f���`��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "sceneX.h"
#include "resource.h"
#include "model.h"
#include "modelX.h"
#include "renderer.h"
#include "camera.h"
#include "cameraManager.h"

#include "renderer.h"
#include "resource.h"
#include "texture.h"
#include "object.h"
#include "objectManager.h"

#include "shaderManager.h"
#include "shader.h"
#include "shaderX.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CSceneX::CSceneX(CTransform* Transform) : CScene(Transform, PRIORITY_3D)
{
	m_Transform = Transform;
	m_LocalTransform = new CTransform();
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CSceneX::~CSceneX()
{

}

//=============================================================================
// ������
//=============================================================================
void CSceneX::Init(const string& FileName)
{
	m_ModelX = **CResource::Get<CModel>(FileName);
}


//=============================================================================
// ���
//=============================================================================/
void CSceneX::Uninit(void)
{
	
}

//=============================================================================
// �`��
//=============================================================================/
void CSceneX::Draw(int num)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾 
	CCamera* pCamera = CCameraManager::GetInstance()->GetCamera();		//�J�����̎擾
	CShaderManager::GetInstance()->Find<CShaderX>();	//�V�F�[�_�̎擾

	//���[���h�}�g���b�N�X�̐ݒ�
	SetMatrix(m_Transform->mtxWorld, m_Transform->Scl, m_Transform->Rot, m_Transform->Pos);

	for (int nCntMat = 0; nCntMat < (int)m_ModelX->NumMat; nCntMat++)
	{
		CShaderManager::GetInstance()->Begin<CShaderX>(num, m_Transform->mtxWorld, pCamera->m_MtxView, pCamera->m_MtxProjection, m_ModelX->MeshMat[nCntMat], m_ModelX->MeshTex[nCntMat]);

		m_ModelX->Mesh->DrawSubset(nCntMat);				// ���b�V����`��

		CShaderManager::GetInstance()->End();
	}
}