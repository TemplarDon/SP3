#include "BehaviourRanged.h"

BehaviourRanged::BehaviourRanged()
{
	random = 0;
}
BehaviourRanged::~BehaviourRanged()
{

}
//
//void BehaviourRanged::Update(double dt, Vector3 playerPosition, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump)
//{
//	//static bool randomInit = false;
//	//if (Direction == false && distancePlayerToEnemy>estimatedDistance)
//	//{
//	//	moveLeft = true;
//	//	moveRight = false;
//	//}
//	//else if (Direction == true && distancePlayerToEnemy>estimatedDistance)
//	//{
//	//	//move right
//	//	moveRight = true;
//	//	moveLeft = false;
//	//}
//
//	//if (distancePlayerToEnemy < estimatedDistance)
//	//{
//	//	if (randomInit == false)
//	//	{
//	//		random = Math::RandIntMinMax(0, 100);
//	//		randomInit = true;
//	//	}
//	//	if (random > 70 && randomInit == true)
//	//	{
//	//		behaviour = EVADE;
//	//	}
//	//	else if (random <= 69 && randomInit == true)
//	//	{
//	//		behaviour = ATTACK;
//	//	}
//	//	else
//	//	{
//	//		behaviour = NEUTRAL;
//	//	}
//	//}
//	///*else
//	//{
//	//behaviour = NEUTRAL;
//	//}
//	//*/
//	//if (behaviour == ATTACK)
//	//{
//	//	//attack
//	//	randomInit = false;
//	//}
//	//else if (behaviour == EVADE)
//	//{
//	//	jump = true;
//	//	randomInit = false;
//	//}
//	///*else if (behaviour == NEUTRAL)
//	//{
//
//	//}
//
//	//*/
//
//}

void BehaviourRanged::BehaviourRangedUpdate(float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, double dt, AttackBase *attack, bool &moveLeft, bool &moveRight,bool &jump,bool Direction)
{	
	static bool randomInit = false;
	if (Direction == false && distancePlayerToEnemy>estimatedDistance)
	{
		moveLeft = true;
		moveRight = false;
	}
	else if (Direction == true && distancePlayerToEnemy>estimatedDistance)
	{
		//move right
		moveRight = true;
		moveLeft = false;
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
			behaviour= EVADE;
		}
		else if (random <=69 &&randomInit==true)
		{
			behaviour = ATTACK;
		}
		else
		{
			behaviour = NEUTRAL;
		}
	}
	/*else
	{
		behaviour = NEUTRAL;
	}
*/
	if (behaviour == ATTACK)
	{
		//attack
		attack->LaunchAttack();
		randomInit = false;
	}
	else if (behaviour == EVADE)
	{
		jump = true;
		randomInit = false;
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