//=============================================================================
// �_����
//=============================================================================
#pragma once

//=============================================================================
// �}�N����`
//=============================================================================
#define POINTLIGHT_MAX (50)

//=============================================================================
// �O���錾
//=============================================================================
class CPointLight;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CPointLightManager
{
public:
	//�C���X�^���X��Ԃ�
	static CPointLightManager* GetInstance() { return Instance == NULL ? Instance = new CPointLightManager() : Instance; };

	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);

	void SetPointLight(CPointLight* PointLight) { m_List.push_back(PointLight); }
	void Release(CPointLight* PointLight);

	//�ݒ�E�擾�֐�
	//=============================================================================
	list<CPointLight*> GetList(void) { return m_List; }	//�w�肵�����X�g�̎擾

private:
	static  CPointLightManager* Instance;	//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CPointLightManager() {};
	~CPointLightManager() {};

	//����p���X�g
	//=============================================================================
	void ReleaseList(void);	

	//�ϐ�
	//=============================================================================
	list<CPointLight*> m_List;
	list<CPointLight*> m_ReleaseList;	//����p���X�g
	D3DXVECTOR3 m_Pos[POINTLIGHT_MAX];
	D3DXCOLOR m_Color[POINTLIGHT_MAX];
	float m_Radius[POINTLIGHT_MAX];
};