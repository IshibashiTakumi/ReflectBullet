//=============================================================================
// Scene���N���X
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "sceneManager.h"
#include "transform.h"

//=============================================================================
// �O���錾
//=============================================================================
class CObject;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CScene
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CScene(CTransform* Transform, PRIORITY Priority);
	~CScene();

	//��{�֐�
	//=============================================================================
	virtual void Init(void) { }			//������
	virtual void Uninit(void) = 0;		//���
	virtual void Update(void) {};		//�X�V
	virtual void Draw(int num) = 0;		//�`��
	virtual void Transformation(void);	//�ʒu�C��
	void Begin(void);					//�`��J�n
	void End(void);						//�`��I��

	//�ݒ�E�擾�֐�
	//=============================================================================
	CObject* GetObj(void) { return m_Object; };	//�I�u�W�F�N�g
	void SetCull(D3DCULL Cull) { m_Cull = Cull; };	//�J�����O�ݒ�
	void SetLight(bool Light) { m_Light = Light; };	//�J�����O�ݒ�

	//�ϐ�
	//=============================================================================
	CTransform* m_Transform;
	CTransform* m_LocalTransform;

	//�����֐�
	//=============================================================================
	template<class Class, class ...Argument>
	static CScene* Create(CTransform* transform, Argument ...argument)
	{
		Class* Scene = new Class(transform);
		Scene->Init(argument...);
		return Scene;
	}

protected:
	//�ϐ�
	//=============================================================================
	CObject* m_Object;		//�I�u�W�F�N�g�^�C�v
	D3DCULL m_Cull;			//�J�����O
	bool m_Light;			//���C�e�B���O

private:
	//CSceneManager�ŌĂяo�����߂̏���(friend)
	//=============================================================================
	PRIORITY m_Priority;
	friend static PRIORITY GetPriority(CScene* Scene) { return Scene->m_Priority; }

	//CObject�ŌĂяo�����߂̏���(friend)
	//=============================================================================
	friend static void SetObject(CScene* Scene, CObject* Object) { Scene->m_Object = Object; }
};