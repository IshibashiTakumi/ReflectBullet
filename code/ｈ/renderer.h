//=============================================================================
// �`��̏���
//=============================================================================
#pragma once

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��p�W��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@�����
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CRenderer
{
public:
	//�C���X�^���X��Ԃ�
	//=============================================================================
	static CRenderer* GetInstance() { return Instance == NULL ? Instance = new CRenderer() : Instance; };

	//��{�I�Ȋ֐��̐錾
	//=============================================================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Begin(void);
	void End(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	//�C���X�^���X
	//=============================================================================
	static  CRenderer* Instance;

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CRenderer();
	~CRenderer();

	LPDIRECT3D9 m_D3D; //DirectX3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_D3DDevice; //DirectX3D�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DVERTEXDECLARATION9 mVertexDeclaration;// ���_�錾

	LPDIRECT3DTEXTURE9 m_Texture;
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	LPDIRECT3DSURFACE9 m_Surface;
	LPDIRECT3DSURFACE9 m_BackBufferSurface;
	LPDIRECT3DSURFACE9 m_Zbuffer;

	D3DVIEWPORT9 m_Viewport;
};