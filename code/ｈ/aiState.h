//=============================================================================
// AI�̏��
//=============================================================================
#pragma once

//=============================================================================
// �O���錾
//=============================================================================
class CObject;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CAiState
{
public:

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CAiState();
	~CAiState();

	//�p���������ׂẴI�u�W�F�N�g�ɑ΂��čs���֐�
	//=============================================================================
	virtual void Init(void);
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	void SetObject(CObject* Object) { m_Object = Object; }
	static void Change(CAiState* AiState, CAiState* _AiState);

	//�����֐�
	//=============================================================================
	template<class Class, class ...Argument>
	static CAiState* Create(CObject* Object, CObject* _Object, vector<vector<int>>* List, Argument ...argument)
	{
		Class* AiState = new Class();
		AiState->Init(Object, _Object, List, argument...);
		return AiState;
	}

protected:
	//�ϐ�
	//=============================================================================
	vector<vector<int>>* m_ThreatLevelMap;
	CObject* m_Object;
	CObject* m_Target;
	float m_Size;
};