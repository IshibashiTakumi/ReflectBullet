//=============================================================================
// カメラの基底クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CCameraController;

//=============================================================================
// マクロ定義
//=============================================================================
namespace camera_define
{
	static const float NEAR_Z = 1.0f;		//NearZ値
	static const float FAR_Z = 20000.0f;	//FarZ値
}
using namespace camera_define;

//=============================================================================
// 構造体
//=============================================================================
typedef enum
{
	Perspective = 0,
	Orthographic,
}PROJECTION;

//=============================================================================
// クラスの定義
//=============================================================================

class CCamera
{
	friend CCameraController;
public:

	CCamera(float nearZ = NEAR_Z, float farZ = FAR_Z);
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	void ReleaseController(void);
	void SetController(CCameraController* Controller);
	void SetProjection(PROJECTION Projection) { m_Projection = Projection; }
	PROJECTION GetProjection(void) { return m_Projection; }

	D3DXVECTOR3 GetPosWorld(void) { return m_PosW; }

	D3DXVECTOR3 m_PosV;			//視点
	D3DXVECTOR3 m_PosR;			//注視点
	D3DXVECTOR3 m_VecU;			//上方向ベクトル
	D3DXVECTOR3 m_Rot;
	D3DXMATRIX m_MtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX m_MtxView;			//ビューマトリックス
	D3DXMATRIX m_MtxWorld;
	CCameraController* m_Controller;
	float near_z;
	float far_z;

private:
	D3DXVECTOR3 m_PosW;
	PROJECTION m_Projection;
	void transScreenToWorld(void);
};
