//=============================================================================
// 点光源
//=============================================================================
#pragma once

//=============================================================================
// マクロ定義
//=============================================================================
#define POINTLIGHT_MAX (50)

//=============================================================================
// 前方宣言
//=============================================================================
class CPointLight;

//=============================================================================
// クラスの定義
//=============================================================================
class CPointLightManager
{
public:
	//インスタンスを返す
	static CPointLightManager* GetInstance() { return Instance == NULL ? Instance = new CPointLightManager() : Instance; };

	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);

	void SetPointLight(CPointLight* PointLight) { m_List.push_back(PointLight); }
	void Release(CPointLight* PointLight);

	//設定・取得関数
	//=============================================================================
	list<CPointLight*> GetList(void) { return m_List; }	//指定したリストの取得

private:
	static  CPointLightManager* Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	//=============================================================================
	CPointLightManager() {};
	~CPointLightManager() {};

	//解放用リスト
	//=============================================================================
	void ReleaseList(void);	

	//変数
	//=============================================================================
	list<CPointLight*> m_List;
	list<CPointLight*> m_ReleaseList;	//解放用リスト
	D3DXVECTOR3 m_Pos[POINTLIGHT_MAX];
	D3DXCOLOR m_Color[POINTLIGHT_MAX];
	float m_Radius[POINTLIGHT_MAX];
};