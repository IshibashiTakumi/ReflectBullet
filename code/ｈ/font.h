//=============================================================================
// �����`��
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CFont : public CScene
{
public:

	CFont(CTransform* Transform);
	~CFont();

	void Init(D3DXVECTOR2 Size, string word, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void Uninit(void);
	void Update(void);
	void Draw(int pass = 0);
	void SetColor(D3DXCOLOR color);
private:
	static string m_Font;
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_Texture; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR2 m_Size;
	unsigned int m_WordMax;

	//�����֐�
	bool SetScan(char font, D3DXVECTOR2& tex);
};