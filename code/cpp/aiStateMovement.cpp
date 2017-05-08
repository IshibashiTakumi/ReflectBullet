//=============================================================================
// AIの行動
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "aiStateMovement.h"
#include "renderer.h"
#include "object.h"
#include "aiStateStop.h"
#include "aiStateAttack.h"

//=============================================================================
// クラスの生成
//=============================================================================
CAiStateMovement::CAiStateMovement() : CAiState()
{
	
}

//=============================================================================
// クラスの破棄
//=============================================================================
CAiStateMovement::~CAiStateMovement()
{

}

//=============================================================================
// 初期化
//=============================================================================
void CAiStateMovement::Init(CObject* Object, CObject* _Object, vector<vector<int>>* List, float Size)
{
	m_Object = Object;
	m_Target = _Object;
	m_Size = Size;
	m_ThreatLevelMap = List;

	Array_X = m_Object->m_Transform->Pos.x / m_Size;
	Array_Y = m_Object->m_Transform->Pos.z / m_Size;

	use = false;
}

//=============================================================================
// 解放
//=============================================================================
void CAiStateMovement::Uninit(void)
{

}

//=============================================================================
// 更新
//=============================================================================
void CAiStateMovement::Update(void)
{
	int x, y;
	x = Array_X;
	y = Array_Y;

	if (!use)
	{
		if (Decision(x, y, x, y + 1))
		{
			Array_X = Array_X;
			Array_Y++;
			use = true;
		}
		else if (Decision(x, y, x, y - 1))
		{
			Array_X = Array_X;
			Array_Y--;
			use = true;
		}
		else if (Decision(x, y, x + 1, y))
		{
			Array_X++;
			Array_Y = Array_Y;
			use = true;
		}
		else if (Decision(x, y, x - 1, y))
		{
			Array_X--;
			Array_Y = Array_Y;
			use = true;
		}			
	}

	D3DXVECTOR2 Pos = D3DXVECTOR2(m_Object->m_Transform->Pos.x, m_Object->m_Transform->Pos.z);

	Pos += (D3DXVECTOR2(100.0f * Array_X, 100.0f * Array_Y) - Pos) * 0.1;		/* 抵抗を加える */

	if ((Pos.x > (100.0f * Array_X) - 10 && Pos.x < (100.0f * Array_X) + 10) && (Pos.y > (100.0f * Array_Y) - 10 && Pos.y < (100.0f * Array_Y) + 10)) use = false;

	m_Object->m_Transform->Pos.x = Pos.x;
	m_Object->m_Transform->Pos.z = Pos.y;

	x = Pos.x / m_Size;
	y = Pos.y / m_Size;

	if ((*m_ThreatLevelMap)[y][x] < 4)
	{
		CAiState::Change(this, CAiState::Create<CAiStateAttack>(m_Object, m_Target, m_ThreatLevelMap, m_Size, 2.0f));
	}
	else if((*m_ThreatLevelMap)[y][x] >= 12)
	{
		CAiState::Change(this, CAiState::Create<CAiStateStop>(m_Object, m_Target, m_ThreatLevelMap, m_Size));
	}
	
}

//=============================================================================
// 格納判定
//=============================================================================
bool CAiStateMovement::Decision(int x, int y, int _x, int _y)
{
	if ((*m_ThreatLevelMap)[y][x] - 1 == (*m_ThreatLevelMap)[_y][_x])
	{
		return true;
	}
	return false;
}
