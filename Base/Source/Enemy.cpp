#include "Enemy.h"

Enemy::Enemy(int x, int y,Behaviour::EnemyType enemyType,float estimatedDistance,AttackBase *attack)
{
	enemyPosition.Set(x, y, 0);
	m_Behaviour = new Behaviour();
	m_Behaviour->setAttack(attack);
	m_Behaviour->setEstimatedDistance(estimatedDistance);
	m_Behaviour->setEnemyType(enemyType);
}

Enemy::~Enemy()
{
}

void Enemy::setEnemyPosition(Vector3 enemyPosition)
{
	this->enemyPosition = enemyPosition;
}
 
Vector3 Enemy::getEnemyPosition()
{
	return enemyPosition;
}
void Enemy::UpdateEnemy(double dt,Vector3 playerPosition)
{
	m_Behaviour->setDirection(playerPosition, enemyPosition);
	m_Behaviour->Update(dt, playerPosition, getEnemyPosition(), moveLeft, moveRight, jump, m_Behaviour->getDirection());
	if (moveLeft == true && moveRight==false)
	{
		MoveLeft(0.3f);
	}
	else if (moveLeft == false && moveRight == true)
	{
		MoveRight(0.3f);
	}
	if (jump == true)
	{
		UpdateJump(dt);
		EntityJumpUpdate(dt);
	}
}
void  Enemy::setBehaviour(Behaviour* behaviour)
{
	this->m_Behaviour = behaviour;
}
Behaviour*  Enemy::getBehaviour(Behaviour* behaviour)
{
	return m_Behaviour;
}

void  Enemy::setAttack(AttackBase* attack)
{
	this->attack = attack;
}
AttackBase*  Enemy::getAttack()
{
	return attack;
}
void Enemy::setMoveLeft(bool moveLeft)
{
	this->moveLeft = moveLeft;
}
bool Enemy::getMoveLeft()
{
	return moveLeft;
}
void Enemy::setMoveRight(bool moveRight)
{
	this->moveRight = moveRight;
}
bool Enemy::getMoveRight()
{
	return moveRight;
}
void Enemy::setJump(bool jump)
{
	this->jump = jump;
}
bool Enemy::getJump()
{
	return jump;
}