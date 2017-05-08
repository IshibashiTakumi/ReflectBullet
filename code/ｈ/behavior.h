//=============================================================================
// Behavior���N���X
//=============================================================================
#pragma once

//=============================================================================
// �O���錾
//=============================================================================
class CObject;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CBehavior
{
public:

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CBehavior();
	~CBehavior();

	//��{�֐�
	//=============================================================================
	virtual void Init(void) { };		//������
	virtual void Uninit(void) = 0;		//���
	virtual void Update(void) = 0;		//�X�V
	virtual void Transformation(void) {};	//�ʒu�C��

	//�j��
	//=============================================================================
	virtual void Release(void);			//�P��

	//�ݒ�E�擾�֐�
	//=============================================================================
	CObject* GetObj(void) { return m_Object; };	//�I�u�W�F�N�g

	//�Փ�
	//=============================================================================
	virtual void CollisionEnter(CObject* Object) {};	//�Փˎ�
	virtual void CollisionTrigger(CObject* Object) {};	//�Փˌp����
	virtual void CollisionRelease(CObject* Object) {};	//�ՓˏI����

	//�����֐�
	//=============================================================================
	template<class Class, class ...Argument>
	static CBehavior* Create(Argument ...argument)
	{
		Class* Behavior = new Class();
		Behavior->Init(argument...);
		return Behavior;
	}
	CObject* m_Object;	//�I�u�W�F�N�g
protected:
	//�ϐ�
	//=============================================================================
	//CObject* m_Object;	//�I�u�W�F�N�g

private:
	//CObject�ŌĂяo�����߂̏���(friend)
	//=============================================================================
	friend static void SetObject(CBehavior* Behavior, CObject* Object) { Behavior->m_Object = Object; }
};