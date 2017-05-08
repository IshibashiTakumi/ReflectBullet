//=============================================================================
// �}�E�X�̓���
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "inputMouse.h"
#include "renderer.h"
#include "camera.h"
#include "cameraManager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DIDEVICE_BUFFERSIZE	100						// �f�o�C�X�ɐݒ肷��o�b�t�@�E�T�C�Y

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �N���X�̐���
//=============================================================================
CInputMouse::CInputMouse()
{
	m_DevMouse = NULL;		//���̓f�o�C�X(�}�E�X)�ւ̃|�C���^�̏�����

	//�}�E�X�̓��͏��̏�����
	for (int count = 0; count < MAUSE_BUTTON_MAX; count++)
	{
		m_State[count] = 0;
		m_Trigger[count] = 0;
		m_Release[count] = 0;
	}
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CInputMouse::~CInputMouse()
{

}

//=============================================================================
// �}�E�X�̏�����
//=============================================================================
HRESULT CInputMouse::Init(LPDIRECTINPUT8* Input, HWND hWnd )
{
	if (FAILED((*Input)->CreateDevice(GUID_SysMouse, &m_DevMouse, NULL))) //�}�E�X�̃f�o�C�X�I�u�W�F�N�g�̂��쐬
	{
		return E_FAIL;
	}
	if (FAILED(m_DevMouse->SetDataFormat(&c_dfDIMouse2))) //�f�[�^�`����ݒ�
	{
		return E_FAIL;
	}
	if (FAILED(FAILED(m_DevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))	//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	{
		return E_FAIL;
	}

	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//	diprop.dwData		= DIPROPAXISMODE_ABS;	// ��Βl���[�h�̏ꍇ
	if (FAILED(m_DevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
	diprop.dwData = DIDEVICE_BUFFERSIZE;
	if (FAILED(m_DevMouse->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph)))
	{
		return E_FAIL;
	}

	m_DevMouse->Acquire(); //�A�N�Z�X�����擾

	return S_OK;
}

//=============================================================================
// �}�E�X�̉��
//=============================================================================
void CInputMouse::Uninit( void )
{
	ResourceRelease(m_DevMouse);
}

//=============================================================================
// �}�E�X�̍X�V
//=============================================================================
void CInputMouse::Update( void )
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾

	// �f�o�C�X�̒��ڃf�[�^���擾����
	DIMOUSESTATE2 dims;
	if (SUCCEEDED(m_DevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &dims)))
	{
		m_PosR = D3DXVECTOR3(dims.lX, dims.lY, dims.lZ);	//���΍��W�̎擾
		m_PosA = D3DXVECTOR2(GetMousePos().x, GetMousePos().y);	//��΍��W�̎擾

		CCamera *Camera = CCameraManager::GetInstance()->GetCamera();
		m_PosW = Camera->GetPosWorld();

		for (int count = 0; count < MAUSE_BUTTON_MAX; count++)
		{
			//�g���K�[�L�[�̏���
			m_Trigger[count] = (m_State[count] | dims.rgbButtons[count]) ^ m_State[count];

			//�����[�X�L�[�̏���
			m_Release[count] = (m_State[count] | dims.rgbButtons[count]) ^ dims.rgbButtons[count];

			//�v���X�L�[�̏���
			m_State[count] = dims.rgbButtons[count];
		}
	}
	else
	{
		m_DevMouse->Acquire();
	}
}

//=============================================================================
// ���΍��W�̎擾
//=============================================================================
D3DXVECTOR3 CInputMouse::GetPosR( void )
{
	return m_PosR;
}

//=============================================================================
// ��΍��W�̎擾
//=============================================================================
D3DXVECTOR2 CInputMouse::GetPosA(void)
{
	return m_PosA;
}

//=============================================================================
// ���[���h���W�̎擾
//=============================================================================
D3DXVECTOR3 CInputMouse::GetPosW(void)
{
	return m_PosW;
}

//=============================================================================
// �v���X�̎擾
//=============================================================================
bool CInputMouse::GetPress( int nBottun )
{
	return ( m_State[ nBottun ] & 0x80 )? true : false;
}

//=============================================================================
// �g���K�[�̎擾
//=============================================================================
bool CInputMouse::GetTrigger( int nBottun )
{
	return ( m_Trigger[ nBottun ] & 0x80 )? true : false;
}

//=============================================================================
// �����[�X�L�[�̎擾
//=============================================================================
bool CInputMouse::GetRelease( int nBottun )
{
	return ( m_Release[ nBottun ] & 0x80 )? true : false;
}