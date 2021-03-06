//=============================================================================
// Texture管理クラス
//=============================================================================
#pragma once

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;

//=============================================================================
// クラスの定義
//=============================================================================
class CTextureManager
{
public:
	//インスタンスを返す
	static CTextureManager* GetInstance() { return Instance == NULL ? Instance = new CTextureManager() : Instance; };

	//テクスチャ関数
	//=============================================================================
	CTexture* Find(const string& FileName);		//取得
	void Create(const string& FileName);		//生成
	void ReleaseAll(void);						//解放

private:
	static  CTextureManager* Instance;	//インスタンス

	//変数
	//=============================================================================
	vector<CTexture*> m_Scan;							//走査用
	unordered_map<string, CTexture*> m_Search;			//検索用

	//コンストラクタ・デストラクタ
	//=============================================================================
	CTextureManager() {};
	~CTextureManager() {};
};