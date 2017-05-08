//=============================================================================
// ���C��
//=============================================================================
#pragma once

//=============================================================================
// scanf��woming�΍�
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4995)
#pragma warning( disable : 4996 ) // �x�����ꎞ�I�ɖ����ɂ��� 
#define DIRECTINPUT_VERSION ( 0x0800 ) //�x���Ώ��p
#define NOMINMAX	//windows.h��min,max��std::min,std::max�̏Փˉ��

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include < windows.h >
#include <time.h>
#include <stdio.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#include "dinput.h"		//���͏����ɕK�v
#include "xaudio2.h"	//�T�E���h�Đ��ɕK�v
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
#include <sstream> //�����X�g���[��
#include "utility.h"	//�֗��֐�(����)
#include "drawUtility.h"	//�`��p�֗��֐�(����)
#include "debugProc.h"
using namespace std;         //  ���O��Ԏw��

//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#pragma comment( lib, "d3d9.lib" )		//�`�揈���ɕK�v
#pragma comment( lib, "d3dx9.lib" )		//��L�̊g�����C�u����
#pragma comment( lib, "dxguid.lib" )	//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment( lib, "winmm.lib" )		//�V�X�e�������擾�ɕK�v
#pragma comment( lib, "dinput8.lib" )	//���͏����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================
namespace main_define
{
	static const string CLASS_NAME = "�T���v��";
	static const float SCREEN_WIDTH = 1280.0f;
	static const float SCREEN_HEIGHT = 720.0f;
	static const unsigned int ID_BUTTON000 = 101;	//�{�^����ID
	static const unsigned int ID_EDIT000 = 111;		//�G�f�B�b�g��ID
	static const unsigned int ID_TIMER = 121;		//�^�C�}�[��ID
	static const unsigned int VERTEX_NUM = 4;		//���_��
}
using namespace main_define;

#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//���_���W( 2D ), ���_�J���[, �e�N�X�`�����W
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) //���_���W( 2D ), ���_�J���[

//=============================================================================
// �֐��̃v���g�^�C�v�錾
//=============================================================================
POINT GetMousePos(void);