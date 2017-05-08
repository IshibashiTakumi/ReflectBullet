//=============================================================================
// ��ʑJ��
//=============================================================================
#pragma once

//=============================================================================
// �\����
//=============================================================================
//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,	//�������Ă��Ȃ�
	FADE_IN,		//�t�F�[�h�C��
	FADE_OUT,		//�t�F�[�h�A�E�g
	FADE_MAX
}FADE;

//=============================================================================
// �O���錾
//=============================================================================

class CFade
{
public:
	//�C���X�^���X��Ԃ�
	static CFade* GetInstance() { return Instance == NULL ? Instance = new CFade() : Instance; };

	//��{�֐�
	//=============================================================================
	void Init(D3DXCOLOR color, const string& TexName = "", const string& MaskName = "");
	void Uninit(void);
	void Update(void);
	void Draw(int pass = 0);

	//�ݒ�E�擾�֐�
	//=============================================================================
	void Start(CMode *NextMode);
	FADE GetFade(void);

private:
	static  CFade* Instance;	//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CFade();
	~CFade();

	//�ϐ�
	//=============================================================================
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_Texture;		//�e�N�X�`��
	LPDIRECT3DTEXTURE9 m_Mask;			//�}�X�N�摜
	D3DXCOLOR m_colorFade;				//�t�F�[�h�F
	FADE m_fade;						//�t�F�[�h�̏��
	CMode *m_NextMode;
};