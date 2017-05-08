//=============================================================================
// �v���C���[�̍s��
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "moveBehavior.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "camera.h"
#include "cameraManager.h"
#include "object.h"
#include "mode.h"
#include "fade.h"
#include "destroyBehavior.h"
#include "pointLight.h"
#include "bulletBehavior.h"
#include "collisionCircle.h"
#include "sceneX.h"
#include "fade.h"
#include "sound.h"
#include "manager.h"
#include "debugProc.h"
#include "sound.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
#define PLAYER_MOVE ( 2.0f )	//�v���C���[�̈ړ���
#define PLAYER_RESISTANCE ( 0.2f )	//�v���C���[�̈ړ��ʒ�R

//=============================================================================
// �N���X�̐���
//=============================================================================
CMoveBehavior::CMoveBehavior() : CBehavior()
{
	m_Move = Vec3Init();
	m_OldPos = Vec3Init();
	m_MoveRot = Vec3Init();
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CMoveBehavior::~CMoveBehavior()
{

}

//=============================================================================
// ������
//=============================================================================
void CMoveBehavior::Init(string& FileName, float Size)
{
	m_Size = Size;
	m_MovementMap.clear();
	m_ThreatLevelMap.clear();

	m_Width = m_Height = 0;
	ifstream file(FileName);
	if (file)
	{
		vector<int> list;
		int num;
		string str;
		while (getline(file, str))
		{
			m_Width = 0;
			string token;
			istringstream stream(str);
			m_MovementMap.push_back(list);
			while (getline(stream, token, ','))
			{
				num = stoi(token);
				m_MovementMap[m_Height].push_back(num);
				m_Width++;
			}
			m_Height++;
		}

		file.close();
	}
}

//=============================================================================
// ���
//=============================================================================
void CMoveBehavior::Uninit(void)
{

}

//=============================================================================
// �X�V
//=============================================================================
void CMoveBehavior::Update(void)
{
	CInputKeyboard* Input = CInput::GetInstance()->GetKeyboard();

	CCamera* camera = CManager::GetInstance()->camera[0];

	D3DXVECTOR3 Pos, Rot;
	Pos = m_Object->m_Transform->Pos;
	Rot = m_Object->m_Transform->Rot;

	m_MoveRot.y = atan2f(SCREEN_HEIGHT * 0.5f - GetMousePos().y, SCREEN_WIDTH * 0.5f - GetMousePos().x);

	/******�v���C���[�̈ړ�******/
	//���O�ړ�
	if ((Input->GetPress(DIK_W) && Input->GetPress(DIK_A)))
	{
		m_Move.x += (-sinf(camera->m_Rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE);
		m_Move.z += (-cosf(camera->m_Rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y + D3DX_PI * 0.75f;
	}
	//�E�O�ړ�
	else if (Input->GetPress(DIK_W) && Input->GetPress(DIK_D))
	{
		m_Move.x -= (-sinf(camera->m_Rot.y - D3DX_PI * 0.75f) * PLAYER_MOVE);
		m_Move.z -= (-cosf(camera->m_Rot.y - D3DX_PI * 0.75f) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y - D3DX_PI * 0.75f;
	}
	//����ړ�
	else if (Input->GetPress(DIK_S) && Input->GetPress(DIK_A))
	{
		m_Move.x -= (-cosf(camera->m_Rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE);
		m_Move.z -= (sinf(camera->m_Rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y + D3DX_PI * 0.25f;
	}
	//�E��ړ�
	else if (Input->GetPress(DIK_S) && Input->GetPress(DIK_D))
	{
		m_Move.x += (-cosf(camera->m_Rot.y + D3DX_PI * 0.25f) * PLAYER_MOVE);
		m_Move.z += (sinf(camera->m_Rot.y + D3DX_PI * 0.25f) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y - D3DX_PI * 0.25f;
	}
	//�O�ړ�
	else if (Input->GetPress(DIK_W))
	{
		m_Move.x += (-sinf(camera->m_Rot.y) * PLAYER_MOVE);
		m_Move.z += (-cosf(camera->m_Rot.y) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y + D3DX_PI;
	}
	//��ړ�
	else if (Input->GetPress(DIK_S))
	{
		m_Move.x -= (-sinf(camera->m_Rot.y) * PLAYER_MOVE);
		m_Move.z -= (-cosf(camera->m_Rot.y) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y;
	}
	//���ړ�
	else if (Input->GetPress(DIK_A))
	{
		m_Move.x -= (-cosf(camera->m_Rot.y) * PLAYER_MOVE);
		m_Move.z -= (sinf(camera->m_Rot.y) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y + D3DX_PI * 0.5f;
	}
	//�E�ړ�
	else if (Input->GetPress(DIK_D))
	{
		m_Move.x += (-cosf(camera->m_Rot.y) * PLAYER_MOVE);
		m_Move.z += (sinf(camera->m_Rot.y) * PLAYER_MOVE);
		//m_MoveRot.y = camera->m_Rot.y - D3DX_PI * 0.5f;
	}

	//��ړ�
	if (Input->GetPress(DIK_U))
	{
		m_Move.y += PLAYER_MOVE;
	}
	//���ړ�
	else if (Input->GetPress(DIK_M))
	{
		m_Move.y -= PLAYER_MOVE;
	}

	m_Move += (Vec3Init() - m_Move) * PLAYER_RESISTANCE;		/* ��R�������� */

	Pos += m_Move;

	if (Rot.y - m_MoveRot.y > D3DX_PI)
	{
		Rot.y -= D3DX_PI * 2;
	}
	else if (Rot.y - m_MoveRot.y < -D3DX_PI)
	{
		Rot.y += D3DX_PI * 2;
	}

	//��]�ʂ̌���
	Rot.y += (m_MoveRot.y - Rot.y) * 0.10f;

	m_Object->m_Transform->Pos = Pos;
	m_Object->m_Transform->Rot = Rot;

	SetMatrix(m_Object->m_Transform->mtxWorld, m_Object->m_Transform->Scl, m_Object->m_Transform->Rot, m_Object->m_Transform->Pos);

	if (CInput::GetInstance()->GetMouse()->GetTrigger(MOUSE_BUTTON0))
	{
		CSound::GetInstance()->PlaySound(SOUND_LABEL_SE_001);
		CObject::Create("bullet", "playerBullet", new CTransform(m_Object->m_Transform->Pos + D3DXVECTOR3(sinf(Rot.y) * 80.0f, 0.0f, cosf(Rot.y) * 80.0f)),
			CScene::Create<CSceneX>(new CTransform(), (string)"bullet.x"),
			CCollision::Create<CCollisionCircle>(new CTransform(), true, 10.0f),
			CBehavior::Create<CBulletBehavior>(Rot.y, 10.0f),
			CBehavior::Create<CDestroyBehavior>(6.0f),
			CPointLight::Create(200.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f)));
	}

	ThreatLevelMap();

	/*FILE* file;
	if (Input->GetTrigger(DIK_F2))
	{
		file = fopen("./data/test.txt", "w");

		for each (auto list in m_ThreatLevelMap)
		{
			for each (auto _list in list)
			{
				fprintf(file, "%d,	", _list);
			}
			fprintf(file, "\n");
		}
	}*/
}

//=============================================================================
// ���������u��
//=============================================================================
void CMoveBehavior::CollisionTrigger(CObject * Object)
{
	
}

//=============================================================================
// ������Â��Ă���
//=============================================================================
void CMoveBehavior::CollisionEnter(CObject * Object)
{

}

//=============================================================================
// ���ꂽ�u��
//=============================================================================
void CMoveBehavior::CollisionRelease(CObject * Object)
{

}

//=============================================================================
// ���Гx�}�b�v�̍쐬
//=============================================================================
void CMoveBehavior::ThreatLevelMap(void)
{
	m_ThreatLevelMap = m_MovementMap;

	int x, y, _x, _y, width = 0, height = 0;
	x = _x = m_Object->m_Transform->Pos.x / m_Size;
	y = _y = m_Object->m_Transform->Pos.z / m_Size;

	list<int> Array;
	if (Decision(x, y, x, y + 1)) m_ThreatLevelMap[y + 1][x] = m_ThreatLevelMap[y][x] + 1;
	if (Decision(x, y, x, y - 1)) m_ThreatLevelMap[y - 1][x] = m_ThreatLevelMap[y][x] + 1;
	if (Decision(x, y, x + 1, y)) m_ThreatLevelMap[y][x + 1] = m_ThreatLevelMap[y][x] + 1;
	if (Decision(x, y, x - 1, y)) m_ThreatLevelMap[y][x - 1] = m_ThreatLevelMap[y][x] + 1;

	Array.clear();
	for each (auto list in m_ThreatLevelMap)
	{
		width = 0;
		for each (auto _list in list)
		{
			if (m_ThreatLevelMap[height][width] == m_ThreatLevelMap[y][x] + 1)
			{
				Array.push_back(height);
				Array.push_back(width);
			}
			width++;
		}
		height++;
	}

	int num = m_ThreatLevelMap[y][x] + 1;
	while (true)
	{
		for (auto list = Array.begin(); list != Array.end(); list++)
		{
			y = *list;
			list++;
			x = *list;

			if (Decision(x, y, x, y + 1)) m_ThreatLevelMap[y + 1][x] = m_ThreatLevelMap[y][x] + 1;
			if (Decision(x, y, x, y - 1)) m_ThreatLevelMap[y - 1][x] = m_ThreatLevelMap[y][x] + 1;
			if (Decision(x, y, x + 1, y)) m_ThreatLevelMap[y][x + 1] = m_ThreatLevelMap[y][x] + 1;
			if (Decision(x, y, x - 1, y)) m_ThreatLevelMap[y][x - 1] = m_ThreatLevelMap[y][x] + 1;
		}

		if (num == m_ThreatLevelMap[y][x] + 1)
		{
			break;
		}

		Array.clear();
		height = 0;
		for each (auto list in m_ThreatLevelMap)
		{
			width = 0;
			for each (auto _list in list)
			{
				if (m_ThreatLevelMap[height][width] == m_ThreatLevelMap[y][x] + 1)
				{
					Array.push_back(height);
					Array.push_back(width);
				}
				width++;
			}
			height++;
		}

		num = m_ThreatLevelMap[y][x] + 1;
	}

	m_ThreatLevelMap[_y][_x] = 0;
}

//=============================================================================
// �i�[����
//=============================================================================
bool CMoveBehavior::Decision(int x, int y, int _x, int _y)
{
	if ((_x >= 0 && _x < m_Width) && (_y >= 0 && _y < m_Height))
	{
		if (m_ThreatLevelMap[_y][_x] != -1 && (m_ThreatLevelMap[_y][_x] == 0 || m_ThreatLevelMap[y][x] < m_ThreatLevelMap[_y][_x] + 1))
		{
			return true;
		}
	}
	return false;
}