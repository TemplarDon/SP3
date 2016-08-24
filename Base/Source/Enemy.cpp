#include "Enemy.h"

Enemy::Enemy()
{
	m_Position.Set(0, 0, 0);
	MaxHealth = 3;
    CurrHealth = MaxHealth;
    attack = new AttackBase;
	/*enemyPosition.Set(x, y, 0);
	m_Behaviour = new Behaviour();
	m_Behaviour->setAttack(attack);
	m_Behaviour->setEstimatedDistance(estimatedDistance);
	m_Behaviour->setEnemyType(enemyType);*/
    attack->SetisEnemy(true);
}
void Enemy::EnemyInit(float estimatedDistance, ELEMENT m_CurrElement, int Damage,float detectionRange)
{
	if (m_CurrElement != EARTH && m_CurrElement != EARTH_2)
	{
		this->m_Behaviour = new BehaviourRanged();
		this->enemyType = RANGED;
	}
	else
	{
		this->m_Behaviour = new BehaviourMelee();
		this->enemyType = MELEE;
	}
	
	attack = new AttackBase();
	attack->Init(Damage, 5.0f);
	MovementSpeed = 0.1f;
	this->estimatedDistance = estimatedDistance;
	this->m_CurrElement = m_CurrElement;
	this->detectionRange = detectionRange;
}

Enemy::~Enemy()
{
}

void  Enemy::setDetectionRange(float detectionRange)
{
	this->detectionRange = detectionRange;
}
float  Enemy::getDetectionRange()
{
	return detectionRange;
}

void Enemy::Update(double dt, Vector3 playerPosition, GameObject_Map * map, Camera camera)
{
	if (this->CurrHealth <= 0)
	{
		this->SetActive(false);
	}
	//std::cout << distancePlayerToEnemy << std::endl;
	if (m_CurrEntityMoveState == EDIBLE)
	{
		Vector3 Velocity(0, 0, 0);
		Velocity = (playerPosition - m_Position); 
		Velocity.Normalize();
		m_Position += Velocity*dt*10;
		//this->setDistancePlayerToEnemy(playerPosition, m_Position);
	}
	else
	{
		if (enemyType == RANGED)
		{
			//temp 
			this->setDistancePlayerToEnemy(playerPosition, m_Position);
			this->setDirectionBasedOnDistance(playerPosition, m_Position);
			m_Behaviour->Update(dt, distancePlayerToEnemy, estimatedDistance, m_Position, Move_Left, Move_Right, m_bJumping, DirectionLeftRight, m_CurrElement, attack, m_CurrEntityMoveState, detectionRange);
			if (Move_Left == true)
			{
				MoveLeft(0.1f);
			}
			else if (Move_Right == true)
			{
				MoveRight(0.1f);
			}
			if (m_CurrEntityMoveState == JUMPING)
			{
				UpdateJump(dt);
			}
			else if (m_CurrEntityMoveState != ON_GROUND)
			{
				EntityJumpUpdate(dt);
			}

			GenerateCollisionBoundary(map);
			CheckCollisionBoundary();
		}
		else if (enemyType == MELEE)
		{
			this->setDistancePlayerToEnemy(playerPosition, m_Position);
			this->setDirectionBasedOnDistance(playerPosition, m_Position);
			m_Behaviour->Update(dt, distancePlayerToEnemy, estimatedDistance, m_Position, Move_Left, Move_Right, m_bJumping, DirectionLeftRight, m_CurrElement, attack, m_CurrEntityMoveState, detectionRange);
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
			if (m_CurrEntityMoveState != ON_GROUND)
			{
				EntityJumpUpdate(dt);
			}
			GenerateCollisionBoundary(map);
			CheckCollisionBoundary();
		}
		ConstrainPlayer(15 + mapOffset_x + mapFineOffset_x, 90 + mapOffset_x + mapFineOffset_x, 25, 580, 1.5, camera);
		
		//std::cout << "Direction" << DirectionLeftRight << std::endl;
		//std::cout << "DistancePlayerToEnemy" << distancePlayerToEnemy << std::endl;
		//std::cout << "Estimated Distance" << estimatedDistance << std::endl;
	}
	DebuffCheckAndApply(dt);

	
}

void Enemy::CollisionResponse(GameObject* OtherGo)
{


	Projectile* tempProj;
	tempProj = dynamic_cast<Projectile*>(OtherGo);

	if (OtherGo->GetObjectType() == PROJECTILE)
	{
		if (this->m_ObjectType == ENEMY && tempProj->GetElement() == MISC && tempProj->getIsHostileProjectile() == false)
		{
			this->debuff_Edible = true;
		}
	}
		
		if (OtherGo->GetObjectType() == PROJECTILE&& tempProj->getIsHostileProjectile() == true)
		{

			if (tempProj->GetElement() == FIRE)
			{
				if (m_CurrElement == WATER)
					DamagMultiplier = 0.5;
				if (m_CurrElement == FIRE)
					DamagMultiplier = 1;
				if (m_CurrElement == EARTH)
					DamagMultiplier = 1.5;
			}
			if (tempProj->GetElement() == WATER)
			{
				if (m_CurrElement == WATER)
					DamagMultiplier = 1;
				if (m_CurrElement == FIRE)
					DamagMultiplier = 1.5;
				if (m_CurrElement == EARTH)
					DamagMultiplier = 0.5;
			}
			if (tempProj->GetElement() == EARTH)
			{
				if (m_CurrElement == WATER)
					DamagMultiplier = 1.5;
				if (m_CurrElement == FIRE)
					DamagMultiplier = 0.5;
				if (m_CurrElement == EARTH)
					DamagMultiplier == 1;
			}
			//debuffs
			//steam knockback
			if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == STEAM && !deBuff_KnockBack)
			{
				deBuff_KnockBack = true;
				if (dynamic_cast<Projectile*>(OtherGo)->getVelocity().x < 0)
				{
					KnockBackDestX = m_Position.x - 3;
					KnockBackLeftRight = false;
				}
				else if (dynamic_cast<Projectile*>(OtherGo)->getVelocity().x > 0)
				{
					KnockBackDestX = m_Position.x + 3;
					KnockBackLeftRight = true;
				}
			}
			//fire 2 burn
			if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == FIRE_2)
			{
				if (deBuff_burning = true)
				{
					deBuff_BurningTimer = 0.f;
				}
				else
				{
					deBuff_burning = true;
				}
			}
			//sand and fire 2 slow
			if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == SAND || dynamic_cast<Projectile*>(OtherGo)->GetElement() == FIRE_2)
			{
				if (deBuff_Slowed)
				{
					deBuff_SlowTimer = 0.f;
				}
				else
				{
					deBuff_Slowed = true;
				}
			}
			//earth 2 stun
			if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == EARTH_2)
			{
				if (deBuff_Stunned = true)
				{
					deBuff_StunTimer = 0.f;
				}
				else
				{
					deBuff_Stunned = true;
				}
			}
			TakeDamage(tempProj->getDamage());
			OtherGo->SetActive(false);
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
	else if (temp>0)
	{
		this->DirectionLeftRight = true;
	}

}

void Enemy::Death()
{
	this->m_Active = false;
}