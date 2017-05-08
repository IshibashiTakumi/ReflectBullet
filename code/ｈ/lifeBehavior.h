//=============================================================================
// ���C�t
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "behavior.h"

//=============================================================================
// �O���錾
//=============================================================================
class CObject;
class CSceneAlphaMask;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CLifeBehavior : public CBehavior
{
public:

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CLifeBehavior();
	~CLifeBehavior();

	//�p���������ׂẴI�u�W�F�N�g�ɑ΂��čs���֐�
	//=============================================================================
	void Init(float Life, string& tagName);
	void Uninit(void);
	void Update(void);

	//�Փ�
	//=============================================================================
	void CollisionTrigger(CObject* Object);		//�Փˎ�
	void CollisionEnter(CObject* Object);		//�Փˌp����
	void CollisionRelease(CObject* Object);		//�ՓˏI����

	//�V�F�[�_�̌����A�擾
	template<class Class, class _Class>
	static Class* Find(list<_Class> List)
	{
		for each (auto list in List)
		{
			if (typeid((*list)) != typeid(Class)) continue;
			return (Class*)list;
		}
	}

private:
	//�ϐ�
	//=============================================================================
	CSceneAlphaMask* m_AlphaMask;
	float m_LifeMax, m_Life;
	string m_TagName;
	bool m_Use;
	bool m_use;
};