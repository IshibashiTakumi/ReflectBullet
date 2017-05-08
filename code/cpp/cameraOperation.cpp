//=============================================================================
// 操作カメラ
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "cameraOperation.h"
#include "input.h"
#include "inputMouse.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define CAMERA_POSV_X ( 0.0f )		//カメラの位置
#define CAMERA_POSV_Y ( 200.0f )		//カメラの位置
#define CAMERA_POSV_Z ( -500.0f )		//カメラの位置
#define CAMERA_POSR_X ( 0.0f )		//カメラの位置
#define CAMERA_POSR_Y ( 0.0f )		//カメラの位置
#define CAMERA_POSR_Z ( 0.0f )		//カメラの位置
#define CAMERA_MOVE ( 40.0f )		//カメラの移動量
#define CAMERA_DISTANCE ( 200 )		//視点と注視点の距離
#define CAMERA_ATTENUATION ( 1.0f )		//カメラの減衰値

//=============================================================================
// クラスの生成
//=============================================================================
CCameraOperation::CCameraOperation(CCamera* Camera) : CCameraController(Camera)
{
	D3DXVECTOR3 PosV, PosR;
	PosV = D3DXVECTOR3(CAMERA_POSV_X, CAMERA_POSV_Y, CAMERA_POSV_Z);	//視点( X, Y, Z )
	PosR = D3DXVECTOR3(CAMERA_POSR_X, CAMERA_POSR_Y, CAMERA_POSR_Z);	//注視点( X, Y, Z )

																			//カメラの基準の角度を初期化
	m_CriteriaRot = D3DXVECTOR3(atan2f(PosV.y - PosR.y, PosV.z - PosR.z),
		atan2f(PosV.x - PosR.x, PosV.z - PosR.z),
		atan2f(PosV.y - PosR.y, PosV.x - PosR.x));

	*m_PosR = PosR, *m_PosV = PosV;

	//カメラの基準の角度のオーバーフロー防止
	if (m_CriteriaRot.x <= -D3DX_PI * 0.5f)
	{
		m_CriteriaRot.x -= (m_CriteriaRot.x + (D3DX_PI * 0.5f)) * 2;
	}
	else if (m_CriteriaRot.x >= D3DX_PI * 0.5f)
	{
		m_CriteriaRot.x -= (m_CriteriaRot.x - (D3DX_PI * 0.5f)) * 2;
	}

	*m_Rot = m_CriteriaRot;

	m_MoveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転( X, Y, Z )

	m_Distance = CAMERA_DISTANCE;
}

//=============================================================================
// クラスの破棄
//=============================================================================
CCameraOperation::~CCameraOperation()
{

}

//=============================================================================
// 更新
//=============================================================================
void CCameraOperation::Update( void )
{
	CInputMouse *Input = CInput::GetInstance()->GetMouse();	//入力の取得

	D3DXVECTOR3 PosV = *m_PosV, PosR = *m_PosR, Rot = *m_Rot;

	//******カメラの移動******/

	m_MousePosR = Input->GetPosR();
	m_MousePosA = Input->GetPosA();

	if (Input->GetTrigger(MOUSE_BUTTON1))
	{
		m_MousePosAC = Input->GetPosA();
	}
	else if (Input->GetRelease(MOUSE_BUTTON1))
	{
		//カメラの基準の角度の設定
		m_CriteriaRot = m_CriteriaRot + m_MoveRot;

		//カメラの基準の角度のオーバーフロー防止
		if (m_CriteriaRot.x < -D3DX_PI * 0.5f)
		{
			m_CriteriaRot.x = -D3DX_PI * 0.5f;
		}
		else if (m_CriteriaRot.x > D3DX_PI * 0.5f)
		{
			m_CriteriaRot.x = D3DX_PI * 0.5f;
		}

		//カメラの角度の移動量の初期化
		m_MoveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (Input->GetPress(MOUSE_BUTTON1))
	{
		float DistanseWidth = m_MousePosA.x - m_MousePosAC.x;
		float DistanseHight = m_MousePosA.y - m_MousePosAC.y;

		if (m_MousePosR.x > 0.0f || m_MousePosR.x < 0.0f)
		{
			//カメラのY角度の移動量の設定
			m_MoveRot.y = (DistanseWidth / (float)SCREEN_HEIGHT) * D3DX_PI;
			//カメラの角度の移動量のオーバーフロー防止
			if (m_MoveRot.y < D3DX_PI)
			{
				m_MoveRot.y += D3DX_PI * 2;
			}
			else if (m_MoveRot.y > D3DX_PI)
			{
				m_MoveRot.y += -D3DX_PI * 2;
			}
		}
		if (m_MousePosR.y > 0.0f || m_MousePosR.y < 0.0f)
		{
			//カメラのX角度の移動量の設定
			m_MoveRot.x = (DistanseHight / (float)SCREEN_HEIGHT) * D3DX_PI;
		}
	}

	//更新した角度をカメラの角度に反映
	Rot = m_CriteriaRot + m_MoveRot;

	//カメラの角度のオーバーフロー防止
	if (Rot.x < -D3DX_PI * 0.5f)
	{
		Rot.x = -D3DX_PI * 0.5f;
	}
	else if (Rot.x > D3DX_PI * 0.5f)
	{
		Rot.x = D3DX_PI * 0.5f;
	}

	//******カメラの視点の移動******/

	//カメラの視点の上下左右移動
	if (Input->GetTrigger(MOUSE_BUTTON2))
	{
		//MOUSE_BUTTON2が押されたときにカメラの位置とマウスの位置を取得
		m_MousePosAC = Input->GetPosA();
		m_WorkPosV = PosV;
		m_WorkPosR = PosR;
	}
	if (Input->GetPress(MOUSE_BUTTON2))
	{
		//MOUSE_BUTTON2が押されている間カメラの視点を求めた位置に移動
		PosV.x = m_WorkPosV.x + sinf(Rot.y + D3DX_PI * 0.5f) * ((m_MousePosAC.x - m_MousePosA.x) * CAMERA_ATTENUATION);
		PosV.z = m_WorkPosV.z + cosf(Rot.y + D3DX_PI * 0.5f) * ((m_MousePosAC.x - m_MousePosA.x) * CAMERA_ATTENUATION);
		PosR.x = m_WorkPosR.x + sinf(Rot.y + D3DX_PI * 0.5f) * ((m_MousePosAC.x - m_MousePosA.x) * CAMERA_ATTENUATION);
		PosR.z = m_WorkPosR.z + cosf(Rot.y + D3DX_PI * 0.5f) * ((m_MousePosAC.x - m_MousePosA.x) * CAMERA_ATTENUATION);
		PosV.y = m_WorkPosV.y + ((m_MousePosAC.y - m_MousePosA.y) * CAMERA_ATTENUATION);
		PosR.y = m_WorkPosR.y + ((m_MousePosAC.y - m_MousePosA.y) * CAMERA_ATTENUATION);
	}

	//カメラの視点の前後移動
	if (m_MousePosR.z > 0.0f)
	{
		PosV.x -= sinf(Rot.y) * CAMERA_MOVE;
		PosV.y -= sinf(Rot.x) * CAMERA_MOVE;
		PosV.z -= cosf(Rot.y) * CAMERA_MOVE;
		PosR.x -= sinf(Rot.y) * CAMERA_MOVE;
		PosR.y -= sinf(Rot.x) * CAMERA_MOVE;
		PosR.z -= cosf(Rot.y) * CAMERA_MOVE;
	}
	else if (m_MousePosR.z < 0.0f)
	{
		PosV.x += sinf(Rot.y) * CAMERA_MOVE;
		PosV.y += sinf(Rot.x) * CAMERA_MOVE;
		PosV.z += cosf(Rot.y) * CAMERA_MOVE;
		PosR.x += sinf(Rot.y) * CAMERA_MOVE;
		PosR.y += sinf(Rot.x) * CAMERA_MOVE;
		PosR.z += cosf(Rot.y) * CAMERA_MOVE;
	}

	//******更新の反映******/

	//注視点移動の更新
	PosR.x = PosV.x - (sinf(Rot.y) * m_Distance);
	PosR.y = PosV.y - (sinf(Rot.x) * m_Distance);
	PosR.z = PosV.z - (cosf(Rot.y) * m_Distance);

	*m_PosV = PosV, *m_PosR = PosR, *m_Rot = Rot;
}