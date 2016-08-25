#include "EarthBossBehaviour.h"

EarthBehaviour::EarthBehaviour()
	: m_DirectionSet(true)
	, m_RunOnce(false)
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
	if (DistanceToPlayer <= 30)
	{
		behaviour = ATTACK;
		m_CurrPhase = NORMAL_ATTACK_PHASE;
		AttackStatus = true;

		if (DistanceToPlayer <= 20)
		{
			m_CurrPhase = ABILITY_ATTACK_PHASE;
			if (DistanceToPlayer <= 10)
			{
				behaviour = EVADE;
				AttackStatus = false;
			}
		}
	}
	else if (DistanceToPlayer > 30)
	{
		behaviour = NEUTRAL;
		AttackStatus = false;
	}

	// Check if tile is blocking enemy
	int EntityPos_X = (int)(CurrPos.x / Map->GetTileSize());
	int EntityPos_Y = (int)(CurrPos.y / Map->GetTileSize());

	bool BlockedLeft = false;
	bool BlockedRight = false;

	GameObject* CheckGameObject_Right = Map->m_GameObjectMap[EntityPos_Y + 1][EntityPos_X + 2];
	GameObject* CheckGameObject_Left = Map->m_GameObjectMap[EntityPos_Y + 1][EntityPos_X - 2];


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

		if (m_DirectionSet)
		{
			if (BlockedLeft)
			{
				m_DestinationToReturn = CurrPos + Vector3(5, 0, 0);
			}
			else if (BlockedRight)
			{
				m_DestinationToReturn = CurrPos - Vector3(5, 0, 0);
			}
			else if ((BlockedLeft) && (BlockedRight))
			{
				m_DestinationToReturn = CurrPos;
			}
			else
			{
				m_DestinationToReturn = CurrPos + Vector3(100, 0, 0);
			}

		}

		if (CurrPos.x < m_DestinationToReturn.x)
		{
			if (BlockedRight)
			{
				m_DirectionSet = true;
				m_DestinationToReturn = CurrPos - Vector3(100, 0, 0);
			}
		}
		else
		{
			if (BlockedLeft)
			{
				m_DirectionSet = true;
				m_DestinationToReturn = CurrPos + Vector3(100, 0, 0);
			}
		}

		break;
	}

	case ATTACK:
	{
		if (PlayerRight)
		{
			m_DestinationToReturn = PlayerPos - Vector3(25, 0, 0);
		}
		else if (PlayerLeft)
		{
			m_DestinationToReturn = PlayerPos + Vector3(25, 0, 0);
		}
		break;
	}

	case EVADE:
	{
		if (PlayerRight)
		{
			m_DestinationToReturn = CurrPos - Vector3(10, 0, 0);
		}
		else if (PlayerLeft)
		{
			m_DestinationToReturn = CurrPos + Vector3(10, 0, 0);
		}
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