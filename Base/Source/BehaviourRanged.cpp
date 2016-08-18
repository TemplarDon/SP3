#include "BehaviourRanged.h"

BehaviourRanged::BehaviourRanged()
{
	random = 0;
}
BehaviourRanged::~BehaviourRanged()
{

}
void BehaviourRanged::Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack, ENTITY_MOVE_STATE m_currEntityMoveState)
{	
	static bool randomInit = false;
	if (Direction == true)
	{
		if (distancePlayerToEnemy<estimatedDistance)
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
		if (distancePlayerToEnemy<estimatedDistance)
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
			std::cout << "Before Bool: " << randomInit << std::endl;
			random = Math::RandIntMinMax(0, 100);
			randomInit = true;
		}
		if (random >70 && randomInit == true)
		{
			behaviour= EVADE;
			std::cout << "after Bool: " << randomInit << std::endl;
			std::cout << "random int: " << random << std::endl;
		}
		else 
		{
			behaviour = ATTACK;
		}
		/*else
		{
			behaviour = NEUTRAL;
		}*/
	}
	/*else
	{
		behaviour = NEUTRAL;
	}
*/
	attack->UpdateAttack(dt, m_CurrElement, enemyPosition, Direction);
	if (behaviour == ATTACK)
	{
		//attack
		attack->LaunchAttack();
		randomInit = false;
	}
	else if (behaviour == EVADE)
	{
		if (jump == true && m_currEntityMoveState == ON_GROUND)
		{
		jump = false;
		randomInit = false;
		}
		else
		jump = true;
		
	}
	
	/*else if (behaviour == NEUTRAL)
	{
		
	}

*/

}
void BehaviourRanged::setBehaviour(BehaviourStates behaviour)
{
	this->behaviour = behaviour;
}
BehaviourRanged::BehaviourStates BehaviourRanged::getBehaviour()
{
	return behaviour;
}