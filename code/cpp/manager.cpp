//=============================================================================
// �A�v���P�[�V�����̃Q�[�������̊Ǘ�
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "fpsManager.h"
#include "cameraManager.h"
#include "lightManager.h"
#include "input.h"
#include "modeManager.h"
#include "game.h"
#include "title.h"
#include "fade.h"
#include "template.h"
#include "resource.h"
#include "camera.h"
#include "cameraOperation.h"
#include "CameraController.h"
#include "joyStick.h"
#include "sound.h"
#include "sceneManager.h"
#include "deferredShader.h"
#include "zTexRenderer.h"
#include "fixedCamera.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CManager* CManager::Instance = NULL;	//�C���X�^���X������

//=============================================================================
// �N���X�̐���
//=============================================================================
CManager::CManager()
{
	m_WireFrame = false; //���C���[�t���[��OFF
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	srand((unsigned)time(NULL));

	CRenderer::GetInstance()->Init( hInstance, hWnd, bWindow);

	CDebugProc::GetInstance()->Init();

	CCamera* Camera = CTemplate::Create<CCamera>(); 
	Camera->SetController(CTemplate::Create<CCameraOperation>(Camera));
	camera[0] = Camera;

	Camera = CTemplate::Create<CCamera>(500.0f, 10000.0f);
	Camera->SetController(CCameraController::Create<CFixedCamera>(Camera, NULL, D3DXVECTOR3(3200.0f, 1000.0f, 1000.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f)));
	camera[1] = Camera;

	CInput::GetInstance()->Init(hInstance, hWnd);
	CJoyStick::GetInstance()->Init();

	CLightManager::GetInstance()->CreateAll();

	CResource::Load();

	CSound::GetInstance()->Init(hWnd);

	CFade::GetInstance()->Init(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), (string)"", (string)"mask.jpg");
	CFade::GetInstance()->Start(new CTitle);

	return S_OK;
}

//=============================================================================
// ���
//=============================================================================
void CManager::Uninit( void )
{
	CDebugProc::GetInstance()->Uninit();
	CCameraManager::GetInstance()->UninitAll();
	CLightManager::GetInstance()->UninitAll();
	CRenderer::GetInstance()->Uninit();
	CInput::GetInstance()->Uninit();
	CJoyStick::GetInstance()->Uninit();
	CFade::GetInstance()->Uninit();
	CModeManager::GetInstance()->Uninit();
	CSound::GetInstance()->Uninit();
	CResource::Unload();
}

//=============================================================================
// �X�V
//=============================================================================
void CManager::Update( void )
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice(); //�f�o�C�X�̎擾 

	CInput *Input = CInput::GetInstance();	//���͂̎擾
	if (Input->GetKeyboard()->GetTrigger(DIK_F8)) m_WireFrame = !m_WireFrame;

	m_WireFrame ? pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) : pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	CCameraManager::GetInstance()->UpdateAll();

	CLightManager::GetInstance()->UpdateAll();	//���C�g�̍X�V

	CInput::GetInstance()->Update();	//���͂̍X�V
	CJoyStick::GetInstance()->Update();

	CFade::GetInstance()->Update();

	CModeManager::GetInstance()->Update( );	//���[�h�̍X�V
}

//=============================================================================
// �`��
//=============================================================================
void CManager::Draw( void )
{
	CCameraManager::GetInstance()->SelectCamera(camera[1]);
	CCameraManager::GetInstance()->SetCamera();	//�J�����̃Z�b�g

	CZTexRenderer::GetInstance()->Begin();

	CSceneManager::GetInstance()->PriorityDraw(PRIORITY_3D, 2);

	CZTexRenderer::GetInstance()->End();

	CCameraManager::GetInstance()->SelectCamera(camera[0]);
	CCameraManager::GetInstance()->SetCamera();	//�J�����̃Z�b�g

	CDeferredShader::GetInstance()->Begin();

	CSceneManager::GetInstance()->PriorityDraw(PRIORITY_3D);

	CDeferredShader::GetInstance()->End();

	CCameraManager::GetInstance()->SelectCamera(camera[1]);
	CCameraManager::GetInstance()->SetCamera();	//�J�����̃Z�b�g

	CRenderer::GetInstance()->Begin( );

	CModeManager::GetInstance()->Draw();	//���[�h�̕`��

	CFade::GetInstance()->Draw(1);

	CDebugProc::GetInstance()->Draw();

	CRenderer::GetInstance()->End();

	CDebugProc::GetInstance()->PrintDebugProc("FPS %d\n", CFpsManager::GetInstance()->GetFps());
}

