//=============================================================================
// 3D�`��
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CScene3D : public CScene
{
public:
	CScene3D(CTransform* Transform);
	~CScene3D();

	void Init(D3DXVECTOR2 Size, string& Texture, string& NormalMap = (string)"NormalNone.jpg", D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2 tex = D3DXVECTOR2(1.0f, 1.0f));
	void Uninit(void);
	void Draw(int num);

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_Texture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_NormalMap;		//�@���}�b�v�ւ̃|�C���^
};