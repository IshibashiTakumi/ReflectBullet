//=============================================================================
// �_����
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "transform.h"

//=============================================================================
// �O���錾
//=============================================================================
class CPointLightManager;
class CObject;

//=============================================================================
// �N���X�̒�`
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
	void Transformation(void) {};	//�ʒu�C��

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

	//CObject�ŌĂяo�����߂̏���(friend)
	//=============================================================================
	friend static void SetObject(CPointLight* PointLight, CObject* Object) { PointLight->m_Object = Object; }
};