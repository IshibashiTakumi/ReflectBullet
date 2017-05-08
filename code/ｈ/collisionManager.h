//=============================================================================
// �����蔻��Ǘ��N���X
//=============================================================================
#pragma once

//=============================================================================
// �O���錾
//=============================================================================
class CCollision;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CCollisionManager
{
public:
	//�C���X�^���X��Ԃ�
	static CCollisionManager* GetInstance() { return Instance == NULL ? Instance = new CCollisionManager() : Instance; };

	//��{�֐�
	//=============================================================================
	void UninitAll(void);
	void UpdateAll(void);
	void DrawAll(void);
	void SetCollision(CCollision* Collision) { m_List.push_back(Collision); }
	void Release(CCollision* Collision);

	//�ݒ�E�擾�֐�
	//=============================================================================
	list<CCollision*> GetList(void) { return m_List; }	//�w�肵�����X�g�̎擾

private:
	static  CCollisionManager* Instance;	//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CCollisionManager();
	~CCollisionManager();

	//����p���X�g
	//=============================================================================
	void ReleaseList(void);		//collision

	//�ϐ�
	//=============================================================================
	list<CCollision*> m_List;				//���X�g�\��
	list<CCollision*> m_ReleaseList;		//����p���X�g
};
