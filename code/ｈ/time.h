//=============================================================================
// �^�C���`��
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

/*******************************************************************************
* �N���X�̒�`
*******************************************************************************/
class CTime : public CScene
{
public:

	CTime(CTransform* Transform);
	~CTime();

	void Init(int digit, int time, D3DXVECTOR2 size, string texName);
	void Uninit(void);
	void Update(void);
	void Draw(int pass = 0);
	float GetTime(void) { return m_LimitTime; }

private:

	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_Texture; //�e�N�X�`���ւ̃|�C���^

	int m_nCounterTimeAnim;								//�A�j���[�V�����J�E���^�[
	int m_nPatternTimeAnim;								//�A�j���[�V�����p�^�[��No
	float m_LimitTime;									//��������
	int m_Digit;										//�^�C���̌���
};