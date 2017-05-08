//=============================================================================
// �V�F�[�_�Ǘ��N���X
//=============================================================================
#pragma once

//=============================================================================
// �O���錾
//=============================================================================
class CShader;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CShaderManager
{
public:
	//�C���X�^���X��Ԃ�
	static CShaderManager* GetInstance() { return Instance == NULL ? Instance = new CShaderManager() : Instance; }
	static void DestroyInstance() { Instance == NULL ? NULL : delete Instance; Instance = NULL; }

	//��{�I�Ȋ֐��̐錾
	//=============================================================================
	void Init(void);
	void Uninit(void);

	//�V�F�[�_�̌����A�擾
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

	//�`��J�n
	template<class Class, class ...Argument>
	void Begin(Argument& ...argument)
	{
		((Class*)m_Current)->Begin(argument...);	//�w�肳�ꂽ�V�F�[�_�ɕ���
	}

	void End(void);	//�`��I��

private:
	static CShaderManager* Instance;	//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CShaderManager() { m_List.clear(); m_Current = NULL; }
	~CShaderManager() {};

	//�ϐ�
	//=============================================================================
	list<CShader*> m_List;
	CShader* m_Current;	//���݂̃V�F�[�_
};