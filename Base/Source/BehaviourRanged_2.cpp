#include "BehaviourRanged_2.h"

BehaviourRanged_2::BehaviourRanged_2()
	: m_DirectionSet(false)
	, m_RunOnce(false)
{}

BehaviourRanged_2::~BehaviourRanged_2()
{}

void BehaviourRanged_2::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map)
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
			Attack = false;
		}
	}
	else if(DistanceToPlayer > 25)
	{
		behaviour = NEUTRAL;
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
			else if ((int)CurrPos.x >(int)m_DestinationToReturn.x)
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
				m_DestinationToReturn = PlayerPos - Vector3(15, 0, 0);
			}
			else if (PlayerLeft)
			{
				m_DestinationToReturn = PlayerPos + Vector3(15, 0, 0);
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
	}
}

Vector3 BehaviourRanged_2::GetDestination()
{
	return m_DestinationToReturn;
}



