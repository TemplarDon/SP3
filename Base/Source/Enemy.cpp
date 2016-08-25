#include "Enemy.h"

Enemy::Enemy()
{
	m_Position.Set(0, 0, 0);
	MaxHealth = 3;
    CurrHealth = MaxHealth;
	/*enemyPosition.Set(x, y, 0);
	m_Behaviour = new Behaviour();
	m_Behaviour->setAttack(attack);
	m_Behaviour->setEstimatedDistance(estimatedDistance);
	m_Behaviour->setEnemyType(enemyType);*/
	Attacks->SetisEnemy(true);
}
void Enemy::EnemyInit(float estimatedDistance, ELEMENT m_CurrElement, int Damage,float detectionRange)
{
	if (m_CurrElement != EARTH && m_CurrElement != EARTH_2)
	{
		//this->m_Behaviour = new BehaviourRanged();
		this->m_Behaviour = new BehaviourRanged_2();
		this->enemyType = RANGED;
	}
	else
	{
		//this->m_Behaviour = new BehaviourMelee();
		//this->enemyType = MELEE;
		this->m_Behaviour = new EarthBehaviour();
		this->enemyType = BOSS;
	}
	
	Attacks->Init(Damage, 5.0f);
	//Attacks->SetAttackElement(m_CurrElement);
	MovementSpeed = 0.1f;
	this->estimatedDistance = estimatedDistance;
	this->m_CurrElement = m_CurrElement;
	this->detectionRange = detectionRange;
}

Enemy::~Enemy()
{
	if (m_Behaviour)
	{
		delete m_Behaviour;
		m_Behaviour = NULL;
	}
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
			////temp 
			//this->setDistancePlayerToEnemy(playerPosition, m_Position);
			//this->setDirectionBasedOnDistance(playerPosition, m_Position);
			//m_Behaviour->Update(dt, distancePlayerToEnemy, estimatedDistance, m_Position, Move_Left, Move_Right, m_bJumping, DirectionLeftRight, m_CurrElement, attack, m_CurrEntityMoveState, detectionRange);
			//if (Move_Left == true)
			//{
			//	MoveLeft(0.1f);
			//}
			//else if (Move_Right == true)
			//{
			//	MoveRight(0.1f);
			//}
			//if (m_CurrEntityMoveState == JUMPING)
			//{
			//	UpdateJump(dt);
			//}
			//else if (m_CurrEntityMoveState != ON_GROUND)
			//{
			//	EntityJumpUpdate(dt);
			//}

			//GenerateCollisionBoundary(map);
			//CheckCollisionBoundary();

			bool Attack = false;
			this->setDirectionBasedOnDistance(playerPosition, m_Position);
			this->m_Behaviour->BehaviourUpdate(playerPosition, m_Position, Attack);
			this->m_Destination = this->m_Behaviour->GetDestination();

			if (m_Destination.x > m_Position.x)
			{
				MoveRight(0.1f);
				rotate = true;
			}
			else if (m_Destination.x < m_Position.x)
			{
				MoveLeft(0.1f);
				rotate = false;
			}
			else
			{
				rotate = true;
			}

			if (m_CurrEntityMoveState == FALLING)
			{
				EntityJumpUpdate(dt);
			}

			ConstrainPlayer(15 + mapOffset_x + mapFineOffset_x, 90 + mapOffset_x + mapFineOffset_x, 25, 580, 1.5, camera);
			GenerateCollisionBoundary(map);
			CheckCollisionBoundary();
			DebuffCheckAndApply(dt);

			if (Attack)
			{
				this->Attacks->SetisEnemy(true);
				this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
				this->Attacks->Attack_Ranged(m_CurrElement, GetElementLevel(m_CurrElement));
			}
		}
		else if (enemyType == MELEE)
		{
			this->setDistancePlayerToEnemy(playerPosition, m_Position);
			this->setDirectionBasedOnDistance(playerPosition, m_Position);
			m_Behaviour->Update(dt, distancePlayerToEnemy, estimatedDistance, m_Position, Move_Left, Move_Right, m_bJumping, DirectionLeftRight, m_CurrElement, Attacks, m_CurrEntityMoveState, detectionRange);
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
			//GenerateCollisionBoundary(map);
			//CheckCollisionBoundary();
		}
		else if (enemyType == BOSS)
		{
			bool Attack = false;
			this->setDirectionBasedOnDistance(playerPosition, m_Position);
			this->m_Behaviour->BehaviourUpdate(playerPosition, m_Position, Attack, map);
			this->m_Destination = this->m_Behaviour->GetDestination();

			if (m_Destination.x > m_Position.x)
			{
				MoveRight(0.1f);
				rotate = true;
			}
			else if (m_Destination.x < m_Position.x)
			{
				MoveLeft(0.1f);
				rotate = false;
			}
			else
			{
				rotate = true;
			}

			if (m_CurrEntityMoveState == FALLING)
			{
				EntityJumpUpdate(dt);
			}

			ConstrainPlayer(0, map->GetNumOfTiles_MapWidth() * map->GetTileSize(), 0, map->GetNumOfTiles_MapHeight() * map->GetTileSize(), 1.5, camera);
			GenerateCollisionBoundary(map);
			CheckCollisionBoundary();
			DebuffCheckAndApply(dt);

			if (Attack)
			{
				if (dynamic_cast<EarthBehaviour*>(m_Behaviour)->GetBossState() == EarthBehaviour::NORMAL_ATTACK_PHASE)
				{
					this->Attacks->SetisEnemy(true);
					this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
					this->Attacks->Attack_Ranged(m_CurrElement, GetElementLevel(m_CurrElement));
				}
				else if (dynamic_cast<EarthBehaviour*>(m_Behaviour)->GetBossState() == EarthBehaviour::ABILITY_ATTACK_PHASE)
				{
					this->Attacks->SetisEnemy(true);
					this->Attacks->UpdateAttack(dt,  this->m_Position, DirectionLeftRight);
					this->Attacks->Attack_Ability(m_CurrElement, GetElementLevel(m_CurrElement));
				}

			}
		}

	
	}



	
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

            DamagMultiplier += 0.5;
        }
        //debuffs

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
        if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == WATER || dynamic_cast<Projectile*>(OtherGo)->GetElement() == WATER_2)
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

void Enemy::setDistancePlayerToEnemy(Vector3 playerPosition, Vector3 enemyPosition)
{
	float temp = (playerPosition - enemyPosition).LengthSquared();
	this->distancePlayerToEnemy = temp;
}

float Enemy::getDistancePlayerToEnemy()
{
	return distancePlayerToEnemy;
}

void Enemy::setEstimatedDistance(float estimatedDistance)
{
	this->estimatedDistance = estimatedDistance;
}
float Enemy::getEstimatedDistance()
{
	return estimatedDistance;
}

void Enemy::setAttack(AttackBase* attack)
{
	this->Attacks = attack;
}
AttackBase* Enemy::getAttack()
{
	return Attacks;
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