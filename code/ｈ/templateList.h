//=============================================================================
//　リストのテンプレート化の為のクラス
//=============================================================================
#pragma once

//=============================================================================
// クラスの定義
//=============================================================================
class CTemplateList
{
public:
	template<class Class, class List>
	static void Uninit(List list)
	{
		for each (auto _list in list) Class::GetInstance()->Release(_list);
		list.clear();
	}

	template<class Class, class List, class T>
	static void Release(List list)
	{
		for (auto itr = list.begin(); itr != list.end(); itr++)
		{
			if ((*itr) != T) continue;
			itr = list.erase(itr);
			break;
		}
	}
};