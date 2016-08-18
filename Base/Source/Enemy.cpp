#include "Enemy.h"


Enemy::Enemy()
{
	m_Position.Set(0, 0, 0);
}
void Enemy::EnemyInit(Vector3 playerPosition,EnemyType enemyType, float estimatedDistance, ELEMENT m_CurrElement,int Damage)
{
	this->enemyType = enemyType;
	if (enemyType == RANGED)
	{
		this->m_Behaviour = new BehaviourRanged();
	}
	else
	{
		this->m_Behaviour = new BehaviourMelee();
	}
	attack = new AttackBase();
	attack->Init(Damage, 5.0f);
	MovementSpeed = 0.1f;
	this->estimatedDistance = estimatedDistance;
	this->m_CurrElement = m_CurrElement;
}

Enemy::~Enemy()
{
}



void Enemy::Update(double dt,Vector3 playerPosition,GameObject_Map * map,Camera camera)
{
	static bool jumpInit = false;
	if (enemyType == RANGED)
	{
		//temp 
		this->setDistancePlayerToEnemy(playerPosition, m_Position);
		this->setDirectionBasedOnDistance(playerPosition, m_Position);
		//m_Behaviour = dynamic_cast<BehaviourRanged*>(m_Behaviour);
		m_Behaviour->Update(dt, distancePlayerToEnemy, estimatedDistance, m_Position, Move_Left, Move_Right, m_bJumping, DirectionLeftRight, m_CurrElement, attack,m_CurrEntityMoveState);
		if (Move_Left == true)
		{
			MoveLeft(0.1f);
			//std::cout << "RUN 1" << std::endl;
		}
		else if (Move_Right == true)
		{
			MoveRight(0.1f);
			//	std::cout << "RUN 2" << std::endl;
		}
		if (m_bJumping == true && jumpInit == false)
		{
			UpdateJump(dt);
			jumpInit = true;
		}
		else if (m_bJumping == true &&jumpInit==true)
		{
			EntityJumpUpdate(dt);
			
		}
		else if (m_bJumping == false)
		{
			jumpInit = false;
		}
		//std::cout << "ENEMY POS " << m_Position << std::endl;
		//UpdateTileMapCollision(map);
		ConstrainPlayer(5 + mapOffset_x + mapFineOffset_x, 150 + mapOffset_x + mapFineOffset_x, 25, 580, dt, camera);
	}
	else if (enemyType==MELEE)
	{
		this->setDistancePlayerToEnemy(playerPosition, m_Position);
		this->setDirectionBasedOnDistance(playerPosition, m_Position);
		//m_Behaviour = dynamic_cast<BehaviourRanged*>(m_Behaviour);
		m_Behaviour->Update(dt, distancePlayerToEnemy, estimatedDistance, m_Position, Move_Left, Move_Right, m_bJumping, DirectionLeftRight, m_CurrElement, attack, m_CurrEntityMoveState);
		if (Move_Left == true)
		{
			MoveLeft(0.1f);
			//std::cout << "RUN 1" << std::endl;
		}
		else if (Move_Right == true)
		{
			MoveRight(0.1f);
			//	std::cout << "RUN 2" << std::endl;
		}
		ConstrainPlayer(5 + mapOffset_x + mapFineOffset_x, 150 + mapOffset_x + mapFineOffset_x, 25, 580, dt, camera);
	}
	//std::cout << "Direction" << DirectionLeftRight << std::endl;
	//std::cout << "DistancePlayerToEnemy" << distancePlayerToEnemy << std::endl;
	//std::cout << "Estimated Distance" << estimatedDistance << std::endl;
}
void  Enemy::setBehaviour(Behaviour* behaviour)
{
	this->m_Behaviour = behaviour;
}
Behaviour*  Enemy::getBehaviour(Behaviour* behaviour)
{
	return m_Behaviour;
}
void  Enemy::setEnemyType(EnemyType enemyType)
{
	this->enemyType = enemyType;
}
Enemy::EnemyType Enemy::getEnemyType()
{
	return enemyType;
}
void  Enemy::setDistancePlayerToEnemy(Vector3 playerPosition, Vector3 enemyPosition)
{
	float temp = (playerPosition - enemyPosition).LengthSquared();
	this->distancePlayerToEnemy = temp;
}
float  Enemy::getDistancePlayerToEnemy()
{
	return distancePlayerToEnemy;
}

void  Enemy::setEstimatedDistance(float estimatedDistance)
{
	this->estimatedDistance = estimatedDistance;
}
float  Enemy::getEstimatedDistance()
{
	return estimatedDistance;
}

void  Enemy::setAttack(AttackBase* attack)
{
	this->attack = attack;
}
 AttackBase*  Enemy::getAttack()
{
	return attack;
}
void Enemy::setDirectionBasedOnDistance(Vector3 playerPosition, Vector3 enemyPosition)
{
	float temp = playerPosition.x - enemyPosition.x;
	if (temp < 0)
	{
		this->DirectionLeftRight = false;
	}
	else if ( temp>0)
	{
		this->DirectionLeftRight = true;
	}
	
}