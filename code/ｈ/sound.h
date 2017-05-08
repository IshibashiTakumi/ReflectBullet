//=============================================================================
//	�T�E���h
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;

//=============================================================================
// �T�E���h�t�@�C��
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM000
	SOUND_LABEL_BGM001,			// BGM001
	SOUND_LABEL_BGM002,			// BGM002
	SOUND_LABEL_SE_000,		// �I��
	SOUND_LABEL_SE_001,		// ����
	SOUND_LABEL_SE_002,		// ����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CSound
{
	public:
		//�C���X�^���X��Ԃ�
		static CSound* GetInstance() { return Instance == NULL ? Instance = new CSound() : Instance; };

		HRESULT Init(HWND hWnd);
		void Uninit(void);
		HRESULT PlaySound(SOUND_LABEL label);
		void StopSound(SOUND_LABEL label);
		void StopSound(void);

private:
	static  CSound* Instance;	//�C���X�^���X

	CSound();
	~CSound();

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

};
