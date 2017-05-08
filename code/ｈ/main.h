//=============================================================================
// メイン
//=============================================================================
#pragma once

//=============================================================================
// scanfのwoming対策
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4995)
#pragma warning( disable : 4996 ) // 警告を一時的に無効にする 
#define DIRECTINPUT_VERSION ( 0x0800 ) //警告対処用
#define NOMINMAX	//windows.hのmin,maxとstd::min,std::maxの衝突回避

//=============================================================================
// インクルードファイル
//=============================================================================
#include < windows.h >
#include <time.h>
#include <stdio.h>
#include "d3dx9.h"		//描画処理に必要
#include "dinput.h"		//入力処理に必要
#include "xaudio2.h"	//サウンド再生に必要
#include <crtdbg.h> 
#include <strsafe.h>
#include <dxerr.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <random>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream> //文字ストリーム
#include "utility.h"	//便利関数(自作)
#include "drawUtility.h"	//描画用便利関数(自作)
#include "debugProc.h"
using namespace std;         //  名前空間指定

//=============================================================================
// ライブラリのリンク
//=============================================================================
#pragma comment( lib, "d3d9.lib" )		//描画処理に必要
#pragma comment( lib, "d3dx9.lib" )		//上記の拡張ライブラリ
#pragma comment( lib, "dxguid.lib" )	//DirectXコンポーネント使用に必要
#pragma comment( lib, "winmm.lib" )		//システム時刻取得に必要
#pragma comment( lib, "dinput8.lib" )	//入力処理に必要

//=============================================================================
// マクロ定義
//=============================================================================
namespace main_define
{
	static const string CLASS_NAME = "サンプル";
	static const float SCREEN_WIDTH = 1280.0f;
	static const float SCREEN_HEIGHT = 720.0f;
	static const unsigned int ID_BUTTON000 = 101;	//ボタンのID
	static const unsigned int ID_EDIT000 = 111;		//エディットのID
	static const unsigned int ID_TIMER = 121;		//タイマーのID
	static const unsigned int VERTEX_NUM = 4;		//頂点数
}
using namespace main_define;

#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//頂点座標( 2D ), 頂点カラー, テクスチャ座標
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) //頂点座標( 2D ), 頂点カラー

//=============================================================================
// 関数のプロトタイプ宣言
//=============================================================================
POINT GetMousePos(void);