//=============================================================================
// シェーダ管理クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CShader;

//=============================================================================
// クラスの定義
//=============================================================================
class CShaderManager
{
public:
	//インスタンスを返す
	static CShaderManager* GetInstance() { return Instance == NULL ? Instance = new CShaderManager() : Instance; }
	static void DestroyInstance() { Instance == NULL ? NULL : delete Instance; Instance = NULL; }

	//基本的な関数の宣言
	//=============================================================================
	void Init(void);
	void Uninit(void);

	//シェーダの検索、取得
	template<class Class>
	Class* Find(void)
	{
		for each (auto list in m_List)
		{
			if (typeid((*list)) != typeid(Class)) continue;
			list->Begin();
			m_Current = list;
			return (Class*)list;
		}
	}

	//描画開始
	template<class Class, class ...Argument>
	void Begin(Argument& ...argument)
	{
		((Class*)m_Current)->Begin(argument...);	//指定されたシェーダに分岐
	}

	void End(void);	//描画終了

private:
	static CShaderManager* Instance;	//インスタンス

	//コンストラクタ・デストラクタ
	//=============================================================================
	CShaderManager() { m_List.clear(); m_Current = NULL; }
	~CShaderManager() {};

	//変数
	//=============================================================================
	list<CShader*> m_List;
	CShader* m_Current;	//現在のシェーダ
};