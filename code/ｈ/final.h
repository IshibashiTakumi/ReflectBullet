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
class CFinal : public CScene
{
	public:

		CFinal(CTransform* Transform);
		~CFinal();

		void Init (D3DXVECTOR2 Size, string& TexName, LPDIRECT3DTEXTURE9 Texture = NULL, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		void Uninit ( void );
		void Update ( void );
		void Draw (int num);

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_Texture; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR2 m_Size;

	D3DXCOLOR m_color[3];
};