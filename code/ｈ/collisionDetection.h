//=============================================================================
// �����蔻����s�N���X
//=============================================================================
#pragma once

//=============================================================================
// �O���錾
//=============================================================================
class CCollision;
class CCollisionCircle;
class CCollision2DMap;
class CCollisionSquare;

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CCollisionDetection
{
public:
	//�C���X�^���X��Ԃ�
	static CCollisionDetection* GetInstance() { return Instance == NULL ? Instance = new CCollisionDetection() : Instance; };

	void CollisionDetection(void);	//�����蔻��Ǘ�
	void CollisionState(CCollision* Collision);
	bool CollisionOverlap(CCollision* list, std::list<CCollision*> _list);		//�Փˏd������
	bool Overlap(CCollision* Collision, CCollision* _Collision);				//�d�����f

	void CircleToCircle(CCollisionCircle* Circle, CCollisionCircle* _Circle);	//�~���m�̂����蔻��
	void CircleToSquare(CCollisionCircle* Circle, CCollisionSquare* Square);	//�~�Ǝl�p�̂����蔻��
	void SquareToSquare(CCollisionSquare* Square, CCollisionSquare* _Square);	//�l�p���m�̂����蔻��
	//void SphereToAabb(CCollisionSphere* Sphere, CCollisionAabb* Aabb);		//Sphere��Aabb�̂����蔻��
	//void AabbToAabb(CCollisionAabb* Aabb, CCollisionAabb* _Aabb);		//Sphere��Aabb�̂����蔻��

private:
	static  CCollisionDetection* Instance;	//�C���X�^���X

	CCollisionDetection();
	~CCollisionDetection();

	void Rejection(CCollision* Collision);

	void HitCollision(CCollision* Collision, CCollision* _Collision);	//�R���W�����ƃR���W�����������������̏���
};
