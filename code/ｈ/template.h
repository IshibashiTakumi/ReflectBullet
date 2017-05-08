//=============================================================================
//　生成のテンプレート化の為のクラス
//=============================================================================
#pragma once

#include "main.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CTemplate
{
public:
	//コンストラクタ・デストラクタ
	//=============================================================================
	CTemplate();
	~CTemplate();

	/*template<class Class>
	static Class* Create()
	{
		Class* _Class = new Class();
		return _Class;
	}
	*/

	template<class Class, class ...Argument>
	static Class* Create(const Argument& ...argument)
	{
		Class* _Class = new Class(argument...);
		return _Class;
	}
};