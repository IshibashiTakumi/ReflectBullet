//=============================================================================
// 点光源
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "transform.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPointLightManager;
class CObject;

//=============================================================================
// クラスの定義
//=============================================================================
class CPointLight
{
	friend CPointLightManager;
public:
	CPointLight();
	~CPointLight();

	void Init(float radius, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Transformation(void) {};	//位置修正

	static CPointLight* Create(float radius = 100.0f, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
	{
		CPointLight* PointLight = new CPointLight();
		PointLight->Init(radius, color);
		return PointLight;
	}

private:
	CObject* m_Object;
	D3DXVECTOR3 m_Pos;
	D3DXCOLOR m_Color;
	float m_Radius;

	//CObjectで呼び出すための処理(friend)
	//=============================================================================
	friend static void SetObject(CPointLight* PointLight, CObject* Object) { PointLight->m_Object = Object; }
};