//=============================================================================
// Model�����N���X
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"
#include "modelX.h"

using namespace extension;

//=============================================================================
// �֐���: CSceneModel *CSceneModel::Create(char name)
//		  (�֐��̊T�v)
// ����:   char name...�t�@�C���̖��O
// �߂�l: CScene3D
// ����:   ���f���̐���
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
