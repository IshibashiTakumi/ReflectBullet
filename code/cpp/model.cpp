//=============================================================================
// Model検索クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "model.h"
#include "modelX.h"

using namespace extension;

//=============================================================================
// 関数名: CSceneModel *CSceneModel::Create(char name)
//		  (関数の概要)
// 引数:   char name...ファイルの名前
// 戻り値: CScene3D
// 説明:   モデルの生成
//=============================================================================
CModel *CModel::Create(const string& FileName)
{
	string str = Search(FileName);

	if (str == Model_X)
	{
		CModelX* modelX = new CModelX(FileName);
		return modelX;
	}

	return NULL;
}

string CModel::Search(const string& FileName)
{
	string str, extension;

	for (auto _str = FileName.end() - 1; (*_str) != '.'; _str--)
	{
		str.push_back((*_str));
	}
	for each (auto _str in str)
	{
		extension.push_back(_str);
	}

	return extension;
}

CModel::operator CModelX*() const
{
	return (this == nullptr) ? nullptr : (CModelX*)this;
}
