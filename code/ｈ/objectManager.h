//=============================================================================
// �I�u�W�F�N�g�Ǘ��N���X
//=============================================================================
#pragma once

//=============================================================================
// �O���錾
//=============================================================================
class CObject;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObjectManager
{
public:
	//�C���X�^���X��Ԃ�
	static CObjectManager* GetInstance() { return Instance == NULL ? Instance = new CObjectManager() : Instance; };

	//��{�I�Ȋ֐��̐錾
	//=============================================================================
	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);
	void SetObject(CObject* Object) { m_List.push_back(Object); }
	void Release(CObject* Object);
	CObject* FindName(const string& Name);
	list<CObject*> FindTag(const string& Tag);

	//�ݒ�E�擾�֐�
	//=============================================================================
	list<CObject*> GetList(void) { return m_List; }	//�w�肵�����X�g�̎擾

private:
	static  CObjectManager* Instance;	//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CObjectManager() {}
	~CObjectManager() {}

	//����p���X�g
	//=============================================================================
	void ReleaseList(void);		//object

	//�ϐ�
	//=============================================================================
	list<CObject*> m_List;			//���X�g�\��
	list<CObject*> m_ReleaseList;	//����p���X�g
};