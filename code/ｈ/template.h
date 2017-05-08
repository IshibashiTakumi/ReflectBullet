//=============================================================================
//�@�����̃e���v���[�g���ׂ̈̃N���X
//=============================================================================
#pragma once

#include "main.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CTemplate
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
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