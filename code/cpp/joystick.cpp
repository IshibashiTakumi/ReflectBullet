//=============================================================================
// ゲームパッド入力クラス
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "joyStick.h"

//=============================================================================
// グローバル変数
//=============================================================================
CJoyStick* CJoyStick::Instance = NULL;	//インスタンス

//=============================================================================
// 初期化
//=============================================================================
void CJoyStick::Init(void)
{
	//	作業用変数
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	UseController = 0;
	for (DWORD count = 0; count < MAX_CONTROLLERS; count++)
	{
		dwResult = XInputGetState(count, &state);

		//	デヴァイスがあるかどうか
		if (dwResult == ERROR_SUCCESS)
		{
			UseController = count;
			break;
		}
	}

	for (DWORD count = 0; count < MAX_CONTROLLERS; count++)
	{
		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(count, &state);

		//	デヴァイスがあるかどうか
		if (dwResult == ERROR_SUCCESS)
		{// Controller is connected

			//	Press情報の初期化
			m_Press[count].Gamepad.bLeftTrigger = NULL;
			m_Press[count].Gamepad.bRightTrigger = NULL;
			m_Press[count].Gamepad.sThumbLX = NULL;
			m_Press[count].Gamepad.sThumbLY = NULL;
			m_Press[count].Gamepad.sThumbRX = NULL;
			m_Press[count].Gamepad.sThumbRY = NULL;
			m_Press[count].Gamepad.wButtons = NULL;

			// Trigger情報の初期化
			m_Trigger[count].Gamepad.bLeftTrigger = NULL;
			m_Trigger[count].Gamepad.bRightTrigger = NULL;
			m_Trigger[count].Gamepad.sThumbLX = NULL;
			m_Trigger[count].Gamepad.sThumbLY = NULL;
			m_Trigger[count].Gamepad.sThumbRX = NULL;
			m_Trigger[count].Gamepad.sThumbRY = NULL;
			m_Trigger[count].Gamepad.wButtons = NULL;

			//	Release情報の初期化
			m_Release[count].Gamepad.bLeftTrigger = NULL;
			m_Release[count].Gamepad.bRightTrigger = NULL;
			m_Release[count].Gamepad.sThumbLX = NULL;
			m_Release[count].Gamepad.sThumbLY = NULL;
			m_Release[count].Gamepad.sThumbRX = NULL;
			m_Release[count].Gamepad.sThumbRY = NULL;
			m_Release[count].Gamepad.wButtons = NULL;
		}
	}
}

//=============================================================================
// 更新
//=============================================================================
void CJoyStick::Uninit(void)
{
	
}

//=============================================================================
// 描画
//=============================================================================
void CJoyStick::Update(void)
{
	//	作業用変数
	DWORD dwResult;
	XINPUT_STATE state;

	for (DWORD count = 0; count < MAX_CONTROLLERS; count++)
	{
		//0で初期化
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		//デヴァイス情報取得
		dwResult = XInputGetState(count, &state);

		//デヴァイスがあったら
		if (dwResult == ERROR_SUCCESS)
		{
			//Trigger
			m_Trigger[count].Gamepad.wButtons = (m_Press[count].Gamepad.wButtons | state.Gamepad.wButtons) ^ m_Press[count].Gamepad.wButtons;

			//Release
			m_Release[count].Gamepad.wButtons = (m_Press[count].Gamepad.wButtons | state.Gamepad.wButtons) ^ state.Gamepad.wButtons;

			//Pless処理
			if (state.Gamepad.sThumbLY <= 0)
			{
				m_Press[count] = state;
			}
			m_Press[count] = state;
		}
	}
}

//=============================================================================
// プレスキーの取得
//=============================================================================
bool CJoyStick::Press(WORD nKey)
{
	return (m_Press[UseController].Gamepad.wButtons & nKey) ? true : false;
}


//=============================================================================
// トリガーの取得
//=============================================================================
bool CJoyStick::Trigger(WORD nKey)
{
	return (m_Trigger[UseController].Gamepad.wButtons & nKey) ? true : false;
}


//=============================================================================
// リリースの取得
//=============================================================================
bool CJoyStick::Release(WORD nKey)
{
	return (m_Release[UseController].Gamepad.wButtons & nKey) ? true : false;
}

//=============================================================================
// 
//=============================================================================
void CJoyStick::Vibration( int LeftMotorSpeed , int RightMotorSpeed )
{
	XINPUT_VIBRATION pVibration;
	pVibration.wLeftMotorSpeed = LeftMotorSpeed;
	pVibration.wRightMotorSpeed = RightMotorSpeed;
	XInputSetState( 0 , &pVibration );
}