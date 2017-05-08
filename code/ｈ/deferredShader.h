//=============================================================================
// 遅延シェーダ
//=============================================================================
#pragma once

//=============================================================================
// マクロ定義
//=============================================================================
#define RENDERTARGET_MAX (4)	//レンダーターゲットの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CDeferredShader
{
public:
	//インスタンスを返す
	//=============================================================================
	static CDeferredShader* GetInstance() { return Instance == NULL ? Instance = new CDeferredShader() : Instance; }
	static void DestroyInstance() { Instance == NULL ? NULL : delete Instance; Instance = NULL; }

	//基本的な関数の宣言
	//=============================================================================
	void Init(void);
	void Uninit(void);
	void Begin(void);
	void Draw(int pass = 0);
	void End(void);

	//設定・取得関数
	//=============================================================================
	LPDIRECT3DTEXTURE9 GetTexture(int num = 0) { return m_Texture[num]; }

private:
	//インスタンス
	//=============================================================================
	static CDeferredShader* Instance;

	//コンストラクタ・デストラクタ
	//=============================================================================
	CDeferredShader();
	~CDeferredShader();

	//変数
	//=============================================================================
	LPDIRECT3DTEXTURE9 m_Texture[RENDERTARGET_MAX];
	LPDIRECT3DSURFACE9 m_Surface[RENDERTARGET_MAX];
	LPDIRECT3DSURFACE9 m_Zbuffer;

	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff; //頂点バッファへのポインタ
};