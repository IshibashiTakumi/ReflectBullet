//=============================================================================
// �x���V�F�[�_
//=============================================================================
#pragma once

//=============================================================================
// �}�N����`
//=============================================================================
#define RENDERTARGET_MAX (4)	//�����_�[�^�[�Q�b�g�̍ő吔

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CDeferredShader
{
public:
	//�C���X�^���X��Ԃ�
	//=============================================================================
	static CDeferredShader* GetInstance() { return Instance == NULL ? Instance = new CDeferredShader() : Instance; }
	static void DestroyInstance() { Instance == NULL ? NULL : delete Instance; Instance = NULL; }

	//��{�I�Ȋ֐��̐錾
	//=============================================================================
	void Init(void);
	void Uninit(void);
	void Begin(void);
	void Draw(int pass = 0);
	void End(void);

	//�ݒ�E�擾�֐�
	//=============================================================================
	LPDIRECT3DTEXTURE9 GetTexture(int num = 0) { return m_Texture[num]; }

private:
	//�C���X�^���X
	//=============================================================================
	static CDeferredShader* Instance;

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CDeferredShader();
	~CDeferredShader();

	//�ϐ�
	//=============================================================================
	LPDIRECT3DTEXTURE9 m_Texture[RENDERTARGET_MAX];
	LPDIRECT3DSURFACE9 m_Surface[RENDERTARGET_MAX];
	LPDIRECT3DSURFACE9 m_Zbuffer;

	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //���_�o�b�t�@�ւ̃|�C���^
};