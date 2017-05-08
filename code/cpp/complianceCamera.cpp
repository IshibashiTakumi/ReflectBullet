//=============================================================================
// 操作カメラ
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "complianceCamera.h"
#include "input.h"
#include "inputMouse.h"
#include "object.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// クラスの生成
//=============================================================================
CComplianceCamera::CComplianceCamera(CCamera* Camera, CObject* Object) : CCameraController(Camera)
{
	m_Object = Object; 
}

//=============================================================================
// クラスの破棄
//=============================================================================
CComplianceCamera::~CComplianceCamera()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CComplianceCamera::Init(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;

	*m_PosR = m_Object->m_Transform->Pos;
	*m_PosV = *m_PosR + m_Pos;

	D3DXVECTOR3 PosV = *m_PosV, PosR = *m_PosR;

	*m_Rot = D3DXVECTOR3(atan2f(PosV.y - PosR.y, PosV.z - PosR.z),
		atan2f(PosV.x - PosR.x, PosV.z - PosR.z),
		atan2f(PosV.y - PosR.y, PosV.x - PosR.x));
}

//=============================================================================
// 更新
//=============================================================================
void CComplianceCamera::Update( void )
{
	CInputMouse *Input = CInput::GetInstance()->GetMouse();	//入力の取得

	D3DXVECTOR3 PosV = *m_PosV, PosR = *m_PosR, Rot = *m_Rot;

	//******カメラの移動******/

	//m_MousePos = Input->GetPosA();

	////カメラのY角度の移動量の設定
	//Rot.y += ((m_MousePos.x - m_OldMousePos.x) / (float)SCREEN_WIDTH) * (D3DX_PI * 2);
	////カメラの角度の移動量のオーバーフロー防止
	//if (Rot.y < D3DX_PI)
	//{
	//	Rot.y += D3DX_PI * 2;
	//}
	//else if (Rot.y > D3DX_PI)
	//{
	//	Rot.y += -D3DX_PI * 2;
	//}

	////カメラのY角度の移動量の設定
	//Rot.x += ((m_MousePos.y - m_OldMousePos.y) / (float)SCREEN_HEIGHT) * (D3DX_PI * 2);
	////カメラの角度のオーバーフロー防止
	//if (Rot.x < 0.0f)
	//{
	//	Rot.x = 0.0f;
	//}
	//else if (Rot.x > D3DX_PI)
	//{
	//	Rot.x = D3DX_PI;
	//}

	//******位置の反映******/
	PosR = m_Object->m_Transform->Pos;
	PosV = PosR + m_Pos;

	*m_PosV = PosV, *m_PosR = PosR, *m_Rot = Rot;
}