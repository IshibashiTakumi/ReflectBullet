//=============================================================================
// AI�̒�~
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "aiStateStop.h"
#include "renderer.h"
#include "object.h"
#include "aiStateMovement.h"
#include "aiBehavior.h"
#include "aiStateAttack.h"

//=============================================================================
// �N���X�̐���
//=============================================================================
CAiStateStop::CAiStateStop() : CAiState()
{
	
}

//=============================================================================
// �N���X�̔j��
//=============================================================================
CAiStateStop::~CAiStateStop()
{

}

//=============================================================================
// ������
//=============================================================================
void CAiStateStop::Init(CObject* Object, CObject* _Object, vector<vector<int>>* List, float Size)
{
	m_Object = Object;
	m_Target = _Object;
	m_Size = Size;
	m_ThreatLevelMap = List;
}

//=============================================================================
// ���
//=============================================================================
void CAiStateStop::Uninit(void)
{

}

//=============================================================================
// �X�V
//=============================================================================
void CAiStateStop::Update(void)
{
	int x, y;
	x = m_Object->m_Transform->Pos.x / m_Size;
	y = m_Object->m_Transform->Pos.z / m_Size;

	if ((*m_ThreatLevelMap)[y][x] < 4)
	{
		CAiState::Change(this, CAiState::Create<CAiStateAttack>(m_Object, m_Target, m_ThreatLevelMap, m_Size, 2.0f));
	}
	else if ((*m_ThreatLevelMap)[y][x] < 12)
	{
		CAiState::Change(this, CAiState::Create<CAiStateMovement>(m_Object, m_Target, m_ThreatLevelMap, m_Size));
	}
	
}