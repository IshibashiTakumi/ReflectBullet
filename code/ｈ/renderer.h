//=============================================================================
// 描画の準備
//=============================================================================
#pragma once

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換用係数
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線情報
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_3D;

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
class CRenderer
{
public:
	//インスタンスを返す
	//=============================================================================
	static CRenderer* GetInstance() { return Instance == NULL ? Instance = new CRenderer() : Instance; };

	//基本的な関数の宣言
	//=============================================================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Begin(void);
	void End(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	//インスタンス
	//=============================================================================
	static  CRenderer* Instance;

	//コンストラクタ・デストラクタ
	//=============================================================================
	CRenderer();
	~CRenderer();

	LPDIRECT3D9 m_D3D; //DirectX3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_D3DDevice; //DirectX3Dデバイスへのポインタ
	LPDIRECT3DVERTEXDECLARATION9 mVertexDeclaration;// 頂点宣言

	LPDIRECT3DTEXTURE9 m_Texture;
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	LPDIRECT3DSURFACE9 m_Surface;
	LPDIRECT3DSURFACE9 m_BackBufferSurface;
	LPDIRECT3DSURFACE9 m_Zbuffer;

	D3DVIEWPORT9 m_Viewport;
};