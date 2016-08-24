#include "BehaviourMelee.h"

BehaviourMelee::BehaviourMelee()
{
	behaviour = NEUTRAL;
}

BehaviourMelee::~BehaviourMelee()
{
	
}
void BehaviourMelee::Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack, ENTITY_MOVE_STATE &m_currEntityMoveState, float detectionRange)
{
//	std::cout << "random INit: " << randomInit << std::endl;
	//std::cout << "move state: " << m_currEntityMoveState << std::endl;
	//std::cout << "behaviour: " << behaviour << std::endl;
	if (distancePlayerToEnemy <=detectionRange)
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
			behaviour = ATTACK;
		}
		else
		{
			behaviour = NEUTRAL;
			
		}
		attack->UpdateAttack(dt, m_CurrElement, enemyPosition, Direction);
		if (behaviour == ATTACK)
		{
			attack->SetisEnemy(true);
			attack->LaunchAttack();
		}
	}
	else
	{
		moveLeft = false;
		moveRight = false;
		behaviour = NEUTRAL;
	}



}




