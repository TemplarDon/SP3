#include "BehaviourRanged_2.h"

BehaviourRanged_2::BehaviourRanged_2()
{}

BehaviourRanged_2::~BehaviourRanged_2()
{}

void BehaviourRanged_2::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack)
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

	// Change BehaviourState, if needed
	if (DistanceToPlayer <= 25)
	{
		behaviour = ATTACK;
		Attack = true;
		if (DistanceToPlayer <= 10)
		{
			behaviour = EVADE;
		}
	}
	else if(DistanceToPlayer > 25)
	{
		behaviour = NEUTRAL;
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
				m_DestinationToReturn = PlayerPos - Vector3(5, 0, 0);
			}
			else if (PlayerLeft)
			{
				m_DestinationToReturn = PlayerPos + Vector3(5, 0, 0);
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

Vector3 BehaviourRanged_2::GetDestination()
{
	return m_DestinationToReturn;
}



