//=============================================================================
// 多目的カメラ
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "multipurposeCamera.h"
#include "camera.h"
#include "object.h"
#include "input.h"
#include "joyStick.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CAMERA_ROT (0.03f)
#define CAMERA_MOVE (20.0f)

//=============================================================================
// クラスの生成
//=============================================================================
CMultipurposeCamera::CMultipurposeCamera(CCamera* Camera, CObject* Object) : CCameraController(Camera)
{
	m_Object = Object;
}

//=============================================================================
// クラスの破棄
//=============================================================================
CMultipurposeCamera::~CMultipurposeCamera()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CMultipurposeCamera::Init(D3DXVECTOR3 PosR, D3DXVECTOR3 PosV, float Distance)
{
	D3DXVECTOR3 Rot, _PosV;
	Rot = D3DXVECTOR3(atan2f(PosV.y - PosR.y, PosV.z - PosR.z),
		atan2f(PosV.x - PosR.x, PosV.z - PosR.z),
		atan2f(PosV.y - PosR.y, PosV.x - PosR.x));

	m_Distance = Distance;

	if (m_Object != NULL)
	{
		*m_PosR = m_Object->m_Transform->Pos;
		_PosV.x = m_Object->m_Transform->Pos.x + (Rot.y * m_Distance);
		_PosV.y = m_Object->m_Transform->Pos.y + (Rot.x * m_Distance);
		_PosV.z = m_Object->m_Transform->Pos.z + (Rot.y * m_Distance);
	}
	*m_Rot = Rot;
	*m_PosV = _PosV;
}

//=============================================================================
// 更新
//=============================================================================
void CMultipurposeCamera::Update(void)
{
	CInputKeyboard *Input = CInput::GetInstance()->GetKeyboard();	//入力の取得

	XINPUT_STATE state;								// 状態
	ZeroMemory(&state, sizeof(XINPUT_STATE));		//	0で初期化
	XInputGetState(CJoyStick::GetInstance()->GetUse(), &state);		// 状態を受け取る

																	//******カメラの移動******/
	D3DXVECTOR3 Rot = *m_Rot;

	//左前移動
	if ((Input->GetPress(DIK_UP) && Input->GetPress(DIK_LEFT)) || (state.Gamepad.sThumbRY > 20000 && state.Gamepad.sThumbRX < -20000))
	{
		Rot.x += CAMERA_ROT * sinf(D3DX_PI * 0.75);
		Rot.y += CAMERA_ROT * sinf(D3DX_PI * -0.75);
	}
	//右前移動
	else if (Input->GetPress(DIK_UP) && Input->GetPress(DIK_RIGHT) || (state.Gamepad.sThumbRY > 20000 && state.Gamepad.sThumbRX > 20000))
	{
		Rot.x += CAMERA_ROT * sinf(D3DX_PI * 0.75);
		Rot.y += CAMERA_ROT * sinf(D3DX_PI * 0.75);
	}
	//左後移動
	else if (Input->GetPress(DIK_DOWN) && Input->GetPress(DIK_LEFT) || (state.Gamepad.sThumbRY < -20000 && state.Gamepad.sThumbRX < -20000))
	{
		Rot.x += CAMERA_ROT * sinf(D3DX_PI * 1.75);
		Rot.y += CAMERA_ROT * sinf(D3DX_PI * 1.75);
	}
	//右後移動
	else if (Input->GetPress(DIK_DOWN) && Input->GetPress(DIK_RIGHT) || (state.Gamepad.sThumbRY < -20000 && state.Gamepad.sThumbRX > 20000))
	{
		Rot.x += CAMERA_ROT * sinf(D3DX_PI * 1.75);
		Rot.y += CAMERA_ROT * sinf(D3DX_PI * -1.75);
	}
	//前移動
	else if (Input->GetPress(DIK_UP) || state.Gamepad.sThumbRY > 20000)
	{
		Rot.x += CAMERA_ROT;
	}
	//後移動
	else if (Input->GetPress(DIK_DOWN) || state.Gamepad.sThumbRY < -20000)
	{
		Rot.x -= CAMERA_ROT;
	}
	//左移動
	else if (Input->GetPress(DIK_LEFT) || state.Gamepad.sThumbRX < -20000)
	{
		Rot.y -= CAMERA_ROT;
	}
	//右移動
	else if (Input->GetPress(DIK_RIGHT) || state.Gamepad.sThumbRX > 20000)
	{
		Rot.y += CAMERA_ROT;
	}

	Rot.y = RotCorrection(Rot.y);

	if (Rot.x > D3DX_PI * 0.49f)
	{
		Rot.x = D3DX_PI * 0.49f;
	}
	else if (Rot.x < D3DX_PI * -0.49f)
	{
		Rot.x = D3DX_PI * -0.49f;
	}
	Rot.x = RotCorrection(Rot.x);

	D3DXVECTOR3 Pos;
	Pos.x = m_Object->m_Transform->Pos.x + (sinf(Rot.y) * m_Distance);
	Pos.y = m_Object->m_Transform->Pos.y + (sinf(Rot.x) * m_Distance);
	Pos.z = m_Object->m_Transform->Pos.z + (cosf(Rot.y) * m_Distance);

	*m_PosV += ((Pos - *m_PosV) * 0.8f);
	*m_PosR += ((m_Object->m_Transform->Pos - *m_PosR) * 0.8f);

	*m_Rot = Rot;
}
