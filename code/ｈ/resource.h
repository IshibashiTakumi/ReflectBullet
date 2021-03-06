//=============================================================================
// Resource基底クラス
//=============================================================================
#pragma once

//=============================================================================
// マクロ定義
//=============================================================================
namespace directory
{
	static const string Texture_Directory = "./data/TEXTURE/";
	static const string Model_Directory = "./data/MODEL/";
}

//=============================================================================
// クラスの定義
//=============================================================================
class CResource
{
public:
	//基本関数
	//=============================================================================
	static void Load(void);
	static void Unload(void);

	//リソース取得
	//=============================================================================
	template <class Resource>
	static Resource* Get(const string &FileName);

private:
	//変数
	//=============================================================================
	static const string m_TexturePath[];
	static const string m_ModelPath[];

	//コンストラクタ・デストラクタ
	//=============================================================================
	CResource() {};
	~CResource() {};
};