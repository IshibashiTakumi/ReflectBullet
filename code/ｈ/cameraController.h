//=============================================================================
// カメラ制御の基底クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CCamera;
class CObject;

//=============================================================================
// クラスの定義
//=============================================================================
class CCameraController
{
public:

	CCameraController(CCamera* camera);
	~CCameraController();

	virtual void Init(void) {};
	virtual void Update(void) = 0;

	template <class Class, class... Argument>
	static Class* Create(CCamera* Camera, CObject* Object, const Argument&... argument)
	{
		Class* _Class = new Class(Camera, Object);
		_Class->Init(argument...);
		return _Class;
	}

protected:
	D3DXVECTOR3* m_PosV;
	D3DXVECTOR3* m_PosR;
	D3DXVECTOR3* m_Rot;
private:
};
