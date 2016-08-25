#include "EarthBossBehaviour.h"

EarthBehaviour::EarthBehaviour()
{}

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

	// Generate Destination and set attack bool
	switch (this->behaviour)
	{
	case NEUTRAL:
	{
		//int rand = Math::RandIntMinMax(0, 1);

		//if (rand == 1)
		//	m_DestinationToReturn = CurrPos + Vector3(5, 0, 0);
		//else
		//	m_DestinationToReturn = CurrPos - Vector3(5, 0, 0);
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