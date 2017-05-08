//=============================================================================
// �`��Ǘ��N���X
//=============================================================================
#pragma once

//=============================================================================
// �\����
//=============================================================================
typedef enum
{
	PRIORITY_3D = 0,
	PRIORITY_2D,
	PRIORITY_MAX,
}PRIORITY;

//=============================================================================
// �O���錾
//=============================================================================
class CScene;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CSceneManager
{
public:
	//�C���X�^���X��Ԃ�
	static CSceneManager* GetInstance() { return Instance == NULL ? Instance = new CSceneManager() : Instance; };

	//��{�I�Ȋ֐��̐錾
	//=============================================================================
	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);
	void PriorityDraw(PRIORITY Priority, int pass = 0);
	void SetObject(PRIORITY Priority, CScene* Scene) { m_List[Priority].push_back(Scene); }
	void Release(CScene* Scene);

	//�ݒ�E�擾�֐�
	//=============================================================================
	list<CScene*> GetList(PRIORITY Priority) { return m_List[Priority]; }	//�w�肵�����X�g�̎擾

private:
	static  CSceneManager* Instance;	//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CSceneManager();
	~CSceneManager();

	//����p���X�g
	//=============================================================================
	void ReleaseList(void);		//scene
	friend static PRIORITY GetPriority(CScene* Scene);

	//�ϐ�
	//=============================================================================
	list<CScene*> m_List[PRIORITY_MAX];	//���X�g�\��
	list<CScene*> m_ReleaseList;	//����p���X�g
};