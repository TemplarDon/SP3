#include "BehaviourWaterBoss.h"
BehaviourWaterBoss::BehaviourWaterBoss()
	: m_DirectionSet(false)
	, m_RunOnce(false)
	, bossState(PHASE1)
	
{
	playmusic = true;
	music.playSE("Music//water_boss.wav");
}

BehaviourWaterBoss::~BehaviourWaterBoss()
{}
BehaviourWaterBoss::WaterBossState BehaviourWaterBoss::getBossState()
{
	return bossState;
}
void BehaviourWaterBoss::setBossState(WaterBossState bossState)
{
	this->bossState = bossState;
}
void BehaviourWaterBoss::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack,  GameObject_Map* Map)
{
	// Calculate DistanceToPlayer
	if (bossState == PHASE1 ||bossState==PHASE2)
	{
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
		if (DistanceToPlayer <= 10000)
		{
			behaviour = ATTACK;
			Attack = true;
		}

		// Generate Destination and set attack bool
		switch (this->behaviour)
		{
		case ATTACK:
		{
			if (PlayerRight)
			{
				m_DestinationToReturn = PlayerPos;// - Vector3(35, 0, 0);
			}
			else if (PlayerLeft)
			{
				m_DestinationToReturn = PlayerPos;// + Vector3(35, 0, 0);
			}
			break;
		}

		}

	}
}

Vector3 BehaviourWaterBoss::GetDestination()
{
	return m_DestinationToReturn;
}



