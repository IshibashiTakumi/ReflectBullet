//=============================================================================
// 操作カメラ
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "playerCamera.h"
#include "input.h"
#include "inputMouse.h"
#include "object.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CAMERA_POSV_X ( 0.0f )		//カメラの位置
#define CAMERA_POSV_Y ( 200.0f )	//カメラの位置
#define CAMERA_POSV_Z ( -500.0f )	//カメラの位置
#define CAMERA_POSR_X ( 0.0f )		//カメラの位置
#define CAMERA_POSR_Y ( 0.0f )		//カメラの位置
#define CAMERA_POSR_Z ( 0.0f )		//カメラの位置
#define CAMERA_MOVE ( 40.0f )		//カメラの移動量
#define CAMERA_DISTANCE ( 200 )		//視点と注視点の距離
#define CAMERA_ATTENUATION ( 1.0f )	//カメラの減衰値

//=============================================================================
// クラスの生成
//=============================================================================
CPlayerCamera::CPlayerCamera(CCamera* Camera, CObject* Object) : CCameraController(Camera)
{
	m_Object = Object; 

	m_Distance = CAMERA_DISTANCE;
	m_MousePos = Vec2Init();
	m_OldMousePos = Vec2Init();
}

//=============================================================================
// クラスの破棄
//=============================================================================
CPlayerCamera::~CPlayerCamera()
{

}

//=============================================================================
// 更新
//=============================================================================
void CPlayerCamera::Update( void )
{
	CInputMouse *Input = CInput::GetInstance()->GetMouse();	//入力の取得

	D3DXVECTOR3 PosV = *m_PosV, PosR = *m_PosR, Rot = *m_Rot;

	//******カメラの移動******/

	m_MousePos = Input->GetPosA();

	//カメラのY角度の移動量の設定
	Rot.y += ((m_MousePos.x - m_OldMousePos.x) / (float)SCREEN_WIDTH) * (D3DX_PI * 2);
	//カメラの角度の移動量のオーバーフロー防止
	if (Rot.y < D3DX_PI)
	{
		Rot.y += D3DX_PI * 2;
	}
	else if (Rot.y > D3DX_PI)
	{
		Rot.y += -D3DX_PI * 2;
	}

	//カメラのY角度の移動量の設定
	Rot.x += ((m_MousePos.y - m_OldMousePos.y) / (float)SCREEN_HEIGHT) * (D3DX_PI * 2);
	//カメラの角度のオーバーフロー防止
	if (Rot.x < 0.0f)
	{
		Rot.x = 0.0f;
	}
	else if (Rot.x > D3DX_PI)
	{
		Rot.x = D3DX_PI;
	}

	//******位置の反映******/
	PosV = m_Object->m_Transform->Pos;
	PosR.x = m_Object->m_Transform->Pos.x + sinf(Rot.y + D3DX_PI) * CAMERA_ATTENUATION;
	PosR.y = m_Object->m_Transform->Pos.y + cosf(Rot.x) * CAMERA_ATTENUATION;
	PosR.z = m_Object->m_Transform->Pos.z + cosf(Rot.y + D3DX_PI) * CAMERA_ATTENUATION;

	*m_PosV = PosV, *m_PosR = PosR, *m_Rot = Rot;
	m_OldMousePos = m_MousePos;
}