#include "Behaviour.h"


Behaviour::Behaviour()
{
	enemyType = NIL;
	attack = new AttackBase();
	estimatedDistance = 0;
}
Behaviour::Behaviour(EnemyType enemyType,float estimatedDistance,AttackBase *attack)
{
	this->enemyType = enemyType;
	this->attack = attack;
	this->estimatedDistance = estimatedDistance;
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
void Behaviour::Update(double dt,Vector3 playerPosition,Vector3 enemyPosition)
{
	float relativeDistance=calculateRelativeDistance(playerPosition, enemyPosition);
	setDirection(playerPosition, enemyPosition);
	if (enemyType == MELEE)
	{

	}
	else if (enemyType == RANGED)
	{

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
	XRelativePosition = (playerPosition.x - enemyPosition.x);
	if (XRelativePosition < 0)
	{
		this->Direction = true;
	}
	else 
	{
		this->Direction = false;
	}
}
bool Behaviour::getDirection()
{
	return Direction;
}