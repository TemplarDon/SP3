#include "BehaviourRanged.h"

BehaviourRanged::BehaviourRanged()
{
	random = 0;
}
BehaviourRanged::~BehaviourRanged()
{

}
void BehaviourRanged::Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack, ENTITY_MOVE_STATE &m_currEntityMoveState, float detectionRange)
{	
	if (distancePlayerToEnemy < detectionRange)
	{
		static bool randomInit = false;
		if (Direction == true)
		{
			if (distancePlayerToEnemy < estimatedDistance)
			{
				moveLeft = true;
				moveRight = false;
			}
			else
			{
				moveRight = true;
				moveLeft = false;
			}

		}
		else if (Direction == false)
		{
			if (distancePlayerToEnemy < estimatedDistance)
			{
				moveLeft = false;
				moveRight = true;
			}
			else
			{
				moveLeft = true;
				moveRight = false;
			}
		}


		if (distancePlayerToEnemy < estimatedDistance)
		{
			if (randomInit == false)
			{
				random = Math::RandIntMinMax(0, 100);
				randomInit = true;
			}
			if (random > 70 && randomInit == true)
			{
				behaviour = EVADE;
			}
			else
			{
				behaviour = ATTACK;
			}

		}
		attack->UpdateAttack(dt, m_CurrElement, enemyPosition, Direction);
		if (behaviour == ATTACK)
		{
			//attack
			attack->LaunchAttack();
			randomInit = false;
		}
		else if (behaviour == EVADE)
		{
			m_currEntityMoveState = JUMPING;
		}

		
		
	}
	else
	{
		moveLeft = false;
		moveRight = false;
		behaviour = NEUTRAL;
	}
}
