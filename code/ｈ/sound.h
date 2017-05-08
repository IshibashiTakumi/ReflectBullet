//=============================================================================
//	サウンド
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDPARAM;

//=============================================================================
// サウンドファイル
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM000
	SOUND_LABEL_BGM001,			// BGM001
	SOUND_LABEL_BGM002,			// BGM002
	SOUND_LABEL_SE_000,		// 選択
	SOUND_LABEL_SE_001,		// 発射
	SOUND_LABEL_SE_002,		// 反射
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
class CSound
{
	public:
		//インスタンスを返す
		static CSound* GetInstance() { return Instance == NULL ? Instance = new CSound() : Instance; };

		HRESULT Init(HWND hWnd);
		void Uninit(void);
		HRESULT PlaySound(SOUND_LABEL label);
		void StopSound(SOUND_LABEL label);
		void StopSound(void);

private:
	static  CSound* Instance;	//インスタンス

	CSound();
	~CSound();

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

};
