//=============================================================================
// 2D�`��
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CScene2D : public CScene
{
public:

	CScene2D(CTransform* Transform);
	~CScene2D();

	void Init(D3DXVECTOR2 Size, string& TexName, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), bool Noise = false);
	void Uninit(void);
	void Update(void);
	void Draw(int pass);

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_Texture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_Mask; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR2 m_Size;
	float m_Criteria;
	bool m_Noise;
};