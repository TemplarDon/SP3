#include "EarthBossBehaviour.h"

EarthBehaviour::EarthBehaviour()
	: m_DirectionSet(false)
	, m_RunOnce(false)
	, m_LastStandStatus(false)
	, m_LastStandTimer(2)
	, m_AttackDistance(40)
	, m_EvadeDistance(10)
	, m_AttackCount(0)
{
}

EarthBehaviour::~EarthBehaviour()
{}

void EarthBehaviour::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &AttackStatus, GameObject_Map* Map)
{
	// Calculate DistanceToPlayer
	float DistanceToPlayer = 0;
	DistanceToPlayer = (PlayerPos - CurrPos).Length();

	// Find if player is left or right of curr enemy
	bool PlayerRight = false;
	bool PlayerLeft = false;
	if (PlayerPos.x > CurrPos.x)
	{
		PlayerRight = true;
	}
	else
	{
		PlayerLeft = true;
	}

	// Change BehaviourState and BossPhase, if needed
	if (DistanceToPlayer <= m_AttackDistance)
	{
		behaviour = ATTACK;
		
		if (m_AttackCount <= 200)
		{
			m_CurrPhase = NORMAL_ATTACK_PHASE;
			AttackStatus = true;
		}
		else
		{
			m_CurrPhase = ABILITY_ATTACK_PHASE;
			AttackStatus = true;
		}

		if (DistanceToPlayer <= m_EvadeDistance)
		{
			behaviour = EVADE;
			AttackStatus = false;
		}
		
	}
	else if (DistanceToPlayer > m_AttackDistance)
	{
		behaviour = NEUTRAL;
		AttackStatus = false;
	}

	// Check if tile is blocking enemy
	int EntityPos_X = (int)(CurrPos.x / Map->GetTileSize());
	int EntityPos_Y = (int)(CurrPos.y / Map->GetTileSize());

	bool BlockedLeft = false;
	bool BlockedRight = false;

	EntityPos_X = Math::Max(0, EntityPos_X - 2);

	GameObject* CheckGameObject_Right = Map->m_GameObjectMap[EntityPos_Y][EntityPos_X + 4];
	GameObject* CheckGameObject_Left = Map->m_GameObjectMap[EntityPos_Y][EntityPos_X];


	if ((CheckGameObject_Right->GetCollidable() && CheckGameObject_Right->GetActive()) && (CheckGameObject_Left->GetCollidable() && CheckGameObject_Left->GetActive()))
	{
		BlockedRight = true;
		BlockedLeft = true;
	}
	else if ((!CheckGameObject_Right->GetCollidable() && !CheckGameObject_Right->GetActive()) && (CheckGameObject_Left->GetCollidable() && CheckGameObject_Left->GetActive()))
	{
		BlockedLeft = true;
		BlockedRight = false;
	}
	else if ((CheckGameObject_Right->GetCollidable() && CheckGameObject_Right->GetActive()) && (!CheckGameObject_Left->GetCollidable() && !CheckGameObject_Left->GetActive()))
	{
		BlockedLeft = false;
		BlockedRight = true;
	}
	else if ((!CheckGameObject_Right->GetCollidable() && !CheckGameObject_Right->GetActive()) && (!CheckGameObject_Left->GetCollidable() && !CheckGameObject_Left->GetActive()))
	{
		BlockedLeft = false;
		BlockedRight = false;
	}
	
	// Check for 'Last Stand' behaviour
	if ((BlockedRight || BlockedLeft) && behaviour == EVADE && !m_LastStandStatus)
	{
		m_LastStandStatus = true;
	}

	// Update Last Stand
	if (m_LastStandStatus)
	{
		behaviour = LAST_STAND;
		if (m_LastStandTimer <= 0)
		{
			m_LastStandStatus = false;
			m_LastStandTimer = 2;
		}
	}

	// Generate Destination and set attack bool
	switch (this->behaviour)
	{
	case NEUTRAL:
	{
		// Random initial direction to walk in
		if (!m_RunOnce)
		{
			int rand = Math::RandIntMinMax(0, 1);
			if (rand == 1)
			{
				m_DestinationToReturn = CurrPos + Vector3(100, 0, 0);
				m_DirectionSet = true;
			}
			else if (rand == 0)
			{
				m_DestinationToReturn = CurrPos - Vector3(100, 0, 0);
				m_DirectionSet = true;
			}
			m_RunOnce = true;
		}

		if (!m_DirectionSet)
		{
			if (BlockedLeft)
			{
				m_DestinationToReturn = CurrPos + Vector3(5, 0, 0);
				m_DirectionSet = true;
			}
			else if (BlockedRight)
			{
				m_DestinationToReturn = CurrPos - Vector3(5, 0, 0);
				m_DirectionSet = true;
			}
			else if ((BlockedLeft) && (BlockedRight))
			{
				m_DestinationToReturn = CurrPos;
				m_DirectionSet = true;
			}
			else
			{
				m_DestinationToReturn = CurrPos + Vector3(100, 0, 0);
				m_DirectionSet = true;
			}

		}

		if ((int)CurrPos.x < (int)m_DestinationToReturn.x)
		{
			if (BlockedRight)
			{
				m_DirectionSet = false;
			}
		}
		else if ((int)CurrPos.x > (int)m_DestinationToReturn.x)
		{
			if (BlockedLeft)
			{
				m_DirectionSet = false;
			}
		}
		else
		{
			m_RunOnce = false;
		}
		break;
	}

	case ATTACK:
	{
		if (PlayerRight)
		{
			m_DestinationToReturn = PlayerPos - Vector3(30, 0, 0);
		}
		else if (PlayerLeft)
		{
			m_DestinationToReturn = PlayerPos + Vector3(30, 0, 0);
		}
		break;
	}

	case EVADE:
	{
		if (PlayerRight)
		{
			m_DestinationToReturn = CurrPos - Vector3(5, 0, 0);
		}
		else if (PlayerLeft)
		{
			m_DestinationToReturn = CurrPos + Vector3(5, 0, 0);
		}
		break;
	}

	case COLLIDE:
	{
		if (BlockedRight)
		{
			m_DestinationToReturn = CurrPos - Vector3(5, 0, 0);
		}
		else
		{
			m_DestinationToReturn = CurrPos + Vector3(5, 0, 0);
		}
		break;
	}

	case LAST_STAND:
	{
		m_DestinationToReturn = PlayerPos;
		break;
	}
	}
}

Vector3 EarthBehaviour::GetDestination()
{
	return m_DestinationToReturn;
}

EarthBehaviour::EARTH_PHASE EarthBehaviour::GetBossState()
{
	return m_CurrPhase;
}

void EarthBehaviour::SetLastStand(bool status)
{
	m_LastStandStatus = status;
}

bool EarthBehaviour::GetLastStand()
{
	return m_LastStandStatus;
}

void EarthBehaviour::SetLastStandTimer(float NewTime)
{
	m_LastStandTimer = NewTime;
}

float EarthBehaviour::GetLastStandTimer()
{
	return m_LastStandTimer;
}

void EarthBehaviour::SetAttackCount(float NewCount)
{
	m_AttackCount = NewCount;
}

float EarthBehaviour::GetAttackCount()
{
	return m_AttackCount;
}