//=============================================================================
// 操作カメラ
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "CameraController.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CCameraOperation : public CCameraController
{
	public:
		CCameraOperation(CCamera* Camera);
		~CCameraOperation();

		void Update ( void );

private:
	D3DXVECTOR3 m_WorkPosV;		//視点の位置を一時的に格納
	D3DXVECTOR3 m_WorkPosR;		//注視点の位置を一時的に格納
	D3DXVECTOR3 m_CriteriaRot;	//基準の角度
	D3DXVECTOR3 m_MoveRot;		//回転量
	D3DXVECTOR3 m_MoveR;		//移動量
	D3DXVECTOR3 m_MoveV;		//移動量
	D3DXVECTOR3 m_MousePosR;	//マウスの相対座標
	D3DXVECTOR2 m_MousePosA;	//マウスの絶対座標
	D3DXVECTOR2 m_MousePosAC;	//マウスの絶対座標の基準点
	D3DXVECTOR3 m_WorkPos;		//注視点の位置を一時的に格納
	float m_Distance;
};