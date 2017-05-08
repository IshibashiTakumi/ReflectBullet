//=============================================================================
// �`��̏���
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "shaderManager.h"
#include "deferredShader.h"
#include "zTexRenderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
namespace renderer_define
{
	static const float START_FOG = 3000.0f;	//�t�H�O�̊J�n�n�_
	static const float END_FOG = 25000.0f;	//�t�H�O�̏I���n�_
}
using namespace renderer_define;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CRenderer::Instance = NULL;	//�C���X�^���X������

//=============================================================================
// �N���X�̐���
//=============================================================================
CRenderer::CRenderer()
{
	m_D3D = NULL;	 //DirectX3D�I�u�W�F�N�g�ւ̃|�C���^������
	m_D3DDevice = NULL;	//DirectX3D�f�o�C�X�ւ̃|�C���^������
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_D3D == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //��ʂ̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; //��ʂ̍���
	d3dpp.BackBufferFormat = d3ddm.Format; //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1; //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE; //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬����
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; //�f�v�X�o�b�t�@�Ƃ���16�r�b�g���g�p����
	d3dpp.Windowed = bWindow; //( �E�C���h�E���[�h / �t���X�N���[�� )
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̐���
	if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, //�`��
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, //���_����
		&d3dpp,
		&m_D3DDevice)))
	{
		if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_D3DDevice)))
		{
			if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_D3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�ݒ�
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //�J�����O���@
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); //�A���t�@�[�u�����h�̐ݒ�
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	////�t�H�O�̐ݒ�
	float StartFog = START_FOG;	//�J�n�ʒu
	float EndFog = END_FOG;		//�I���ʒu
	m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //�t�H�O�FON
	m_D3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(255, 255, 255, 255)); //���F�ŕs����
	m_D3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);      //���_���[�h
	m_D3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);     //�e�[�u�����[�h
	m_D3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&StartFog)); //�J�n�ʒu
	m_D3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&EndFog));     //�I���ʒu

	//�T���v���[�X�e�[�g�̐ݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); //�e�N�X�`���̏k�����̕�Ԑݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //�e�N�X�`���̊g�厞�̕�Ԑݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); //�e�N�X�`��(U�l)�J��Ԃ��ɐݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); //�e�N�X�`��(V�l)�J��Ԃ��ɐݒ�

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DVERTEXELEMENT9 mDecl[] = 
	{ { 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
	{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0 },
	{ 0,24,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0 },
	{ 0,36,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0 },
	{ 0,48,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 }, 
		D3DDECL_END() };

	m_D3DDevice->CreateVertexDeclaration(mDecl, &mVertexDeclaration);

	m_D3DDevice->GetRenderTarget(0, &m_BackBufferSurface);
	m_D3DDevice->GetDepthStencilSurface(&m_Zbuffer); 
	m_D3DDevice->GetViewport(&m_Viewport);

	CShaderManager::GetInstance()->Init();
	CDeferredShader::GetInstance()->Init();
	CZTexRenderer::GetInstance()->Init();

	return S_OK;
}

//=============================================================================
// �f�o�C�X�̉��
//=============================================================================
void CRenderer::Uninit(void)
{
	CShaderManager::GetInstance()->Uninit();
	CDeferredShader::GetInstance()->Uninit();
	CZTexRenderer::GetInstance()->Uninit();

	ResourceRelease(m_D3DDevice);
	ResourceRelease(m_D3D);

	ResourceRelease(m_BackBufferSurface); 
	ResourceRelease(m_Zbuffer);
}

//=============================================================================
// �`��J�n
//=============================================================================
void CRenderer::Begin(void)
{
	m_D3DDevice->SetViewport(&m_Viewport);
	m_D3DDevice->SetRenderTarget(0, m_BackBufferSurface);
	for (int count = 0; count < 3; count++)
	{
		m_D3DDevice->SetRenderTarget(count + 1, NULL);
	}
	m_D3DDevice->SetDepthStencilSurface(m_Zbuffer);

	//��ʂ̃N���A
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	SUCCEEDED(m_D3DDevice->BeginScene());	//�`��J�n
}

//=============================================================================
// �`��I��
//=============================================================================
void CRenderer::End(void)
{
	m_D3DDevice->EndScene(); //�`��I��

	m_D3DDevice->Present(NULL, NULL, NULL, NULL); //�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_D3DDevice;
}