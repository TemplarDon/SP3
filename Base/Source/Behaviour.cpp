#include "Behaviour.h"


Behaviour::Behaviour()
{
	enemyType = NIL;
	attack = new AttackBase();
	estimatedDistance = 0;
	behaviourRanged = new BehaviourRanged();
}
Behaviour::Behaviour(EnemyType enemyType,float estimatedDistance,AttackBase *attack)
{
	this->enemyType = enemyType;
	this->attack = attack;
	this->estimatedDistance = estimatedDistance;
	if (enemyType == RANGED)
	{
		behaviourRanged = new BehaviourRanged();
	}
	else
	{

	}

}
Behaviour::~Behaviour()
{

}
float Behaviour::calculateRelativeDistance(Vector3 playerPosition, Vector3 enemyPosition)
{
	float relativeDistance;
	relativeDistance = (playerPosition - enemyPosition).LengthSquared();
	return relativeDistance;
}
void Behaviour::Update(double dt, Vector3 playerPosition, Vector3 &enemyPosition,bool &moveLeft,bool &moveRight ,bool &jump)
{
	float relativeDistance=calculateRelativeDistance(playerPosition, enemyPosition);
	setDirection(playerPosition, enemyPosition);
	if (enemyType == MELEE)
	{

	}
	else if (enemyType == RANGED)
	{
		behaviourRanged->setBehaviour(BehaviourRanged::NEUTRAL);
		behaviourRanged->BehaviourRangedUpdate(relativeDistance,estimatedDistance,enemyPosition,dt,attack,moveLeft,moveRight,jump,Direction);
	}
}

void Behaviour::setEnemyType(EnemyType enemyType)
{
	this->enemyType = enemyType;
}
Behaviour::EnemyType Behaviour::getEnemyType()
{
	return enemyType;
}

void Behaviour::setEstimatedDistance(float estimatedDistance)
{
	this->estimatedDistance = estimatedDistance;
}
float Behaviour::getEstimatedDistance()
{
	return estimatedDistance;
}
void Behaviour::setAttack(AttackBase *attack)
{
	this->attack = attack;
}
AttackBase Behaviour::getAttack()
{
	return *attack;
}

void Behaviour::setDirection(Vector3 playerPosition,Vector3 enemyPosition)
{
	float XRelativePosition = 0;
	XRelativePosition = playerPosition.x-enemyPosition.x;
	if (XRelativePosition < 0)
	{
		this->Direction = false;
	}
	else 
	{
		this->Direction =true;
	}
}
bool Behaviour::getDirection()
{
	return Direction;
}
//void Behaviour::setBehaviour(BehaviourStates behaviour)
//{
//	this->behaviour = behaviour;
//}
//Behaviour::BehaviourStates Behaviour::getBehaviour()
//{
//	return behaviour;
//}
void Behaviour::setBehaviourRanged(BehaviourRanged* behaviourRanged)
{
	this->behaviourRanged = behaviourRanged;
}
BehaviourRanged* Behaviour::getBehaviourRanged()
{
	return behaviourRanged;
}
//void Behaviour::setEnemyPosition(Vector3 enemyPosition)
//{
//	this->enemyPosition = enemyPosition;
//}
//Vector3 Behaviour::setEnemyPosition()
//{
//	return enemyPosition;
//}