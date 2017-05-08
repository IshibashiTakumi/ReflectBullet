//=============================================================================
// AIの状態
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CObject;

//=============================================================================
// クラスの定義
//=============================================================================
class CAiState
{
public:

	//コンストラクタ・デストラクタ
	//=============================================================================
	CAiState();
	~CAiState();

	//継承したすべてのオブジェクトに対して行う関数
	//=============================================================================
	virtual void Init(void);
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	void SetObject(CObject* Object) { m_Object = Object; }
	static void Change(CAiState* AiState, CAiState* _AiState);

	//生成関数
	//=============================================================================
	template<class Class, class ...Argument>
	static CAiState* Create(CObject* Object, CObject* _Object, vector<vector<int>>* List, Argument ...argument)
	{
		Class* AiState = new Class();
		AiState->Init(Object, _Object, List, argument...);
		return AiState;
	}

protected:
	//変数
	//=============================================================================
	vector<vector<int>>* m_ThreatLevelMap;
	CObject* m_Object;
	CObject* m_Target;
	float m_Size;
};