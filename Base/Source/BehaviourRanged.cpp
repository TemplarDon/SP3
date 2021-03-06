#include "BehaviourRanged.h"

BehaviourRanged::BehaviourRanged()
{
	random = 0;
}
BehaviourRanged::~BehaviourRanged()
{

}
void BehaviourRanged::Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement,int ElementLevel ,AttackBase* attack, ENTITY_MOVE_STATE &m_currEntityMoveState, float detectionRange)
{	
	static bool randomInit = false;
	if (distancePlayerToEnemy < detectionRange)
	{
		
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
			else if (random > 99 && randomInit == true)
			{
				behaviour = EVADE;
			}
			else
			{
				behaviour = ATTACK;
			}

		}
		attack->UpdateAttack(dt, enemyPosition, Direction);
		if (behaviour == ATTACK)
		{
			//attack
			attack->SetisEnemy(true);
			attack->Attack_Basic(m_CurrElement, ElementLevel);
			randomInit = false;
		}
		else if (behaviour == EVADE)
		{
			if (m_currEntityMoveState != FALLING && m_currEntityMoveState==ON_GROUND &&m_currEntityMoveState!=JUMPING)
			{
				m_currEntityMoveState = JUMPING;
				randomInit = false;
			}
			else 
			{
				if (m_currEntityMoveState == ON_GROUND)
				{
 					behaviour = NEUTRAL;
					randomInit = false;
				}
			}
		}
		
	}
	else
	{
		moveLeft = false;
		moveRight = false;
		behaviour = NEUTRAL;
	}
}
