//=============================================================================
// ゲームパッド入力クラス
//=============================================================================
#pragma once

//=============================================================================
// インクルードファイル
//=============================================================================
#include "XInput.h"
#pragma comment(lib,"XInput.lib")

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_CONTROLLERS ( 4 )			//	コントローラーの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CJoyStick
{
public:
	//インスタンスを返す
	static CJoyStick* GetInstance() { return Instance == NULL ? Instance = new CJoyStick() : Instance; };

	void Init(void);
	void Uninit(void);
	void Update(void);

	//	JoyStickの入力を受け取る関数
	bool Press(WORD nKey);
	bool Trigger(WORD nKey);
	bool Release(WORD nKey);
	void Vibration(int LeftMotorSpeed, int RightMotorSpeed);
	WORD GetUse(void) { return UseController; }

private:
	static CJoyStick* Instance;	//インスタンス

	CJoyStick() {};
	~CJoyStick() {};

	XINPUT_STATE m_Press[MAX_CONTROLLERS];		//プレス情報
	XINPUT_STATE m_Trigger[MAX_CONTROLLERS];	//トリガー情報
	XINPUT_STATE m_Release[MAX_CONTROLLERS];	//リリース情報
	WORD UseController;							//使用しているコントローラー
};