#include "Enemy.h"
#include "GameObjectManager.h"

Enemy::Enemy()
{
	m_Position.Set(0, 0, 0);
	MaxHealth = 100;
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
	CurrHealth = MaxHealth;

	if (m_CurrElement == EARTH || m_CurrElement == FIRE || m_CurrElement == WATER)
	{
		//this->m_Behaviour = new BehaviourRanged();
		this->m_Behaviour = new BehaviourRanged_2();
		this->enemyType = RANGED;
	}
	else
	{
		//this->m_Behaviour = new BehaviourMelee();
		//this->enemyType = MELEE;
		if (m_CurrElement == EARTH_2)
		{
			this->m_Behaviour = new EarthBehaviour();
			this->enemyType = BOSS;
		}
	}
	
	Attacks->Init(Damage, 5.0f);
	//Attacks->SetAttackElement(m_CurrElement);
	MovementSpeed = 0.1f;
	SlowedSpeed = MovementSpeed * 0.5;
	this->estimatedDistance = estimatedDistance;
	this->m_CurrElement = m_CurrElement;
	this->detectionRange = detectionRange;

	m_ElementsPercentageMap[m_CurrElement] = 5.f;
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
	static float timer = 0;
	static bool timerBool = false;
	std::cout << "timer :" << timer << std::endl;
	//std::cout << "Curr health: " << CurrHealth << std::endl;
	if (this->CurrHealth <= 0)
	{
		Death();
	}
	if (CurrHealth <= (MaxHealth/2) && m_CurrEntityMoveState !=EDIBLE)
	{
		m_CurrEntityMoveState = WEAKENED;
	}
	if (timerBool == true)
	{
		timer += dt;
	}
	if (m_CurrEntityMoveState == EDIBLE)
	{
		Vector3 Velocity(0, 0, 0);
		Velocity = (playerPosition - m_Position); 
		Velocity.Normalize();
 		m_Position += Velocity*dt * 10;
		ConstrainPlayer(20, map->GetNumOfTiles_MapWidth() * map->GetTileSize(), 10, map->GetNumOfTiles_MapHeight() * map->GetTileSize(), 1.5, camera);
		GenerateCollisionBoundary(map);
		CheckCollisionBoundary();
		DebuffCheckAndApply(dt);
		if (m_CurrEntityMoveState == FALLING)
		{
			EntityJumpUpdate(dt);
		}
		m_CurrEntityMoveState = WEAKENED;
	}
	
	if (m_CurrEntityMoveState == WEAKENED)
	{
		if (timerBool == false)
		{
			timerBool = true;
		}
		
		ConstrainPlayer(20, map->GetNumOfTiles_MapWidth() * map->GetTileSize(), 10, map->GetNumOfTiles_MapHeight() * map->GetTileSize(), 1.5, camera);
		GenerateCollisionBoundary(map);
		CheckCollisionBoundary();
		DebuffCheckAndApply(dt);
		if (m_CurrEntityMoveState == FALLING)
		{
			EntityJumpUpdate(dt); 
		}
		if (m_CurrEntityMoveState != NO_STATE)
		{
			m_CurrEntityMoveState = WEAKENED;
		}
		if (timer >= 10.f)
		{
			CurrHealth = MaxHealth;
			timerBool = false;
			timer = 0;
			m_CurrEntityMoveState = NO_STATE;
		} 
	}

	if (m_CurrEntityMoveState != WEAKENED && m_CurrEntityMoveState != EDIBLE)
	{
		if (enemyType == RANGED)
		{
			bool Attack = false;
			this->setDirectionBasedOnDistance(playerPosition, m_Position);
			this->m_Behaviour->BehaviourUpdate(playerPosition, m_Position, Attack, map);
			this->m_Destination = this->m_Behaviour->GetDestination();

			if ((int)m_Destination.x > (int)m_Position.x)
			{
				MoveRight(0.1f);
				rotate = true;
			}
			else if ((int)m_Destination.x < (int)m_Position.x)
			{
				MoveLeft(0.1f);
				rotate = false;
			}
			else
			{
				if (playerPosition.x > m_Position.x)
				{
					rotate = true;
				}
				else
				{
					rotate = false;
				}
			}

			bool AttackDir = false;
			if (playerPosition.x > m_Position.x)
			{
				AttackDir = true;
			}
			else
			{
				AttackDir = false;
			}

			if (m_CurrEntityMoveState == FALLING)
			{
				EntityJumpUpdate(dt);
			}

			ConstrainPlayer(20, map->GetNumOfTiles_MapWidth() * map->GetTileSize(), 10, map->GetNumOfTiles_MapHeight() * map->GetTileSize(), 1.5, camera);
			GenerateCollisionBoundary(map);
			CheckCollisionBoundary();
			DebuffCheckAndApply(dt);

			if (Attack && DirectionLeftRight == AttackDir)
			{
				this->Attacks->SetisEnemy(true);
				this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
				this->Attacks->Attack_Basic(m_CurrElement, GetElementLevel(m_CurrElement));
			}
		}

		else if (enemyType == BOSS)
		{
			bool Attack = false;
			this->setDirectionBasedOnDistance(playerPosition, m_Position);
			this->m_Behaviour->BehaviourUpdate(playerPosition, m_Position, Attack, map);
			this->m_Destination = this->m_Behaviour->GetDestination();

			if ((int)m_Destination.x > (int)m_Position.x)
			{
				MoveRight(0.1f);
				rotate = true;
			}
			else if ((int)m_Destination.x < (int)m_Position.x)
			{
				MoveLeft(0.1f);
				rotate = false;
			}
			else
			{
				if (playerPosition.x > m_Position.x)
				{
					rotate = true;
				}
				else
				{
					rotate = false;
				}
			}

			bool AttackDir = false;
			if (playerPosition.x > m_Position.x)
			{
				AttackDir = true;
			}
			else
			{
				AttackDir = false;
			}

			if (m_CurrEntityMoveState == FALLING)
			{
				EntityJumpUpdate(dt);
			}

			ConstrainPlayer(20, map->GetNumOfTiles_MapWidth() * map->GetTileSize(), 10, map->GetNumOfTiles_MapHeight() * map->GetTileSize(), 1.5, camera);
			GenerateCollisionBoundary(map);
			CheckCollisionBoundary();
			DebuffCheckAndApply(dt);

			if (Attack && DirectionLeftRight == AttackDir)
			{
				ELEMENT temp;
				if (m_CurrElement == FIRE_2)
				{
					temp = FIRE;
				}
				if (m_CurrElement == EARTH_2)
				{
					temp = EARTH;
				}
				if (m_CurrElement == WATER_2)
				{
					temp = WATER;
				}
				if (dynamic_cast<EarthBehaviour*>(m_Behaviour)->GetBossState() == EarthBehaviour::NORMAL_ATTACK_PHASE)
				{
					this->Attacks->SetisEnemy(true);
					this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
					this->Attacks->Attack_Basic(temp, GetElementLevel(temp));
				}
				else if (dynamic_cast<EarthBehaviour*>(m_Behaviour)->GetBossState() == EarthBehaviour::ABILITY_ATTACK_PHASE)
				{
					this->Attacks->SetisEnemy(true);
					this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
					this->Attacks->Attack_Ability(temp, GetElementLevel(temp));
				}

			}
		}
	}
	//else if (enemyType == MELEE)
	//{
	//	this->setDistancePlayerToEnemy(playerPosition, m_Position);
	//	this->setDirectionBasedOnDistance(playerPosition, m_Position);
	//	m_Behaviour->Update(dt, distancePlayerToEnemy, estimatedDistance, m_Position, Move_Left, Move_Right, m_bJumping, DirectionLeftRight, m_CurrElement, Attacks, m_CurrEntityMoveState, detectionRange);
	//	if (Move_Left == true)
	//	{
	//		MoveLeft(0.1f);
	//		//std::cout << "RUN 1" << std::endl;
	//	}
	//	else if (Move_Right == true)
	//	{
	//		MoveRight(0.1f);
	//		//	std::cout << "RUN 2" << std::endl;
	//	}
	//	if (m_CurrEntityMoveState != ON_GROUND)
	//	{
	//		EntityJumpUpdate(dt);
	//	}
	//}


}



	


void Enemy::CollisionResponse(GameObject* OtherGo)
{


    Projectile* tempProj;
    tempProj = dynamic_cast<Projectile*>(OtherGo);

    if (OtherGo->GetObjectType() == PROJECTILE)
    {
        if (this->m_ObjectType == ENEMY && this->m_CurrEntityMoveState==WEAKENED && tempProj->GetElement() == MISC && tempProj->getIsHostileProjectile() == false)
        {
          //  this->debuff_Edible = true;
			this->m_CurrEntityMoveState = EDIBLE;
			std::cout << "HIT " << std::endl;
        }
    }

    if (OtherGo->GetObjectType() == PROJECTILE&& tempProj->getIsHostileProjectile() == false)
    {

        if (tempProj->GetElement() == FIRE || tempProj->GetElement() == FIRE_2)
        {
            if (m_CurrElement == WATER)
                DamagMultiplier = 0.5;
            if (m_CurrElement == FIRE)
                DamagMultiplier = 1;
            if (m_CurrElement == EARTH)
                DamagMultiplier = 1.5;

            DamagMultiplier = DamagMultiplier * 0.4;
        }
		if (tempProj->GetElement() == WATER || tempProj->GetElement() == WATER_2)
        {
            if (m_CurrElement == WATER)
                DamagMultiplier = 1;
            if (m_CurrElement == FIRE)
                DamagMultiplier = 1.5;
            if (m_CurrElement == EARTH)
                DamagMultiplier = 0.5;
        }
		if (tempProj->GetElement() == EARTH || tempProj->GetElement() == EARTH_2)
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

	Collectibles* temp = dynamic_cast<Collectibles*>(GameObjectManager::SpawnGameObject(COLLECTIBLE, GO_DROP_HEALTH, m_Position, Vector3(3, 3, 3), false, true, MeshBuilder::GenerateQuad("healthdrop", Color(1, 1, 1)), "Image//UI//heart_icon.tga"));
	temp->InitCollectible(5);
}