//=============================================================================
// ���s����
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "directionalLight.h"
#include "renderer.h"


//=============================================================================
// �N���X�̐���
//=============================================================================
CDirectionalLight::CDirectionalLight(D3DXCOLOR color, D3DXVECTOR3 Vec, int Number)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 
	D3DXVECTOR3 vecDir;

	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = D3DLIGHT_DIRECTIONAL; //���s����
	m_Light.Diffuse = color; //���̐F
	vecDir = Vec; //���̌���
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);
	pDevice->SetLight(Number, &m_Light); //���C�g�̐ݒ�
	pDevice->LightEnable(Number, TRUE); //���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE); //��d��
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CDirectionalLight::~CDirectionalLight()
{

}