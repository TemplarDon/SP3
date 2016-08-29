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
	timer = 0;
}
void Enemy::EnemyInit(float estimatedDistance, ELEMENT m_CurrElement, int Damage,float detectionRange)
{
	CurrHealth = MaxHealth;

	if (m_CurrElement == EARTH || m_CurrElement == FIRE || m_CurrElement == WATER)
	{
		//this->m_Behaviour = new BehaviourRanged();
		this->m_Behaviour = new BehaviourRanged_2(m_CurrElement);
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
		if (m_CurrElement == WATER_2)
		{
			this->m_Behaviour = new BehaviourWaterBoss();
			this->enemyType = WATERBOSS;
		}
	}
	
	Attacks->Init(Damage, 5.0f);
	//Attacks->SetAttackElement(m_CurrElement);
	MovementSpeed = 0.1f;

	SlowedSpeed = MovementSpeed * 0.5f;

	this->estimatedDistance = estimatedDistance;
	this->m_CurrElement = m_CurrElement;
	this->detectionRange = detectionRange;

	timer = 0;
	m_ElementsPercentageMap[m_CurrElement] = 3.f;

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

	static bool timerBool = false;

	std::cout << "timer: " << timer << std::endl;
	//std::cout << "Curr health: " << CurrHealth << std::endl;

	if (this->CurrHealth <= 0)
	{
		Death();
	}
	if (CurrHealth <= (MaxHealth/2) && m_CurrEntityMoveState !=EDIBLE && this->enemyType!=WATERBOSS && this->enemyType !=BOSS)
	{	
			m_CurrEntityMoveState = WEAKENED;
	}

	if (timerBool == true)
	{
		timer += (float)dt;
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



			if (m_Behaviour->GetLastStand())
			{
				m_Behaviour->SetLastStandTimer(m_Behaviour->GetLastStandTimer() - dt);
			}

			if (m_Behaviour->GetCollide())
			{
				m_Behaviour->SetCollideTimer(m_Behaviour->GetCollideTimer() - dt);
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
		else if (enemyType == WATERBOSS)
		{
			 if (CurrHealth <= 0)
			 {
				if (enemyType == WATERBOSS && dynamic_cast<BehaviourWaterBoss*>(m_Behaviour)->getBossState() == BehaviourWaterBoss::PHASE1)
				{
				dynamic_cast<BehaviourWaterBoss*>(m_Behaviour)->setBossState(BehaviourWaterBoss::PHASE2);

				}
				else if (enemyType == WATERBOSS && dynamic_cast<BehaviourWaterBoss*>(m_Behaviour)->getBossState() == BehaviourWaterBoss::PHASE2)
				{
				dynamic_cast<BehaviourWaterBoss*>(m_Behaviour)->setBossState(BehaviourWaterBoss::PHASE3);
				}
			}
			std::cout << (m_Destination - m_Position).LengthSquared() << std::endl;
			bool Attack = false;
			this->m_Behaviour->BehaviourUpdate(playerPosition, m_Position, Attack);
			this->m_Destination = this->m_Behaviour->GetDestination();
			if ((int)m_Destination.x > (int)m_Position.x)
			{
				if ((m_Destination - m_Position).LengthSquared() > 4500)
				{
					std::cout << "YES" << std::endl;
					this->MovementSpeed = 0.2f;
				} 
				else if ((m_Destination - m_Position).LengthSquared() < 500)
				{
					this->MovementSpeed = 0.01f;
				}
				else
				{
					this->MovementSpeed = 0.1f;
				}
				MoveRight(0.1f);
				rotate = true;
			}
			else if ((int)m_Destination.x < (int)m_Position.x)
			{
				if ((m_Destination - m_Position).LengthSquared() > 4500)
				{
					this->MovementSpeed = 0.2f;
				}
				else if ((m_Destination - m_Position).LengthSquared() < 500)
				{
					this->MovementSpeed = 0.01f;
				}
				else
				{
					this->MovementSpeed = 0.1f;
				}
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
			

			ConstrainPlayer(20, map->GetNumOfTiles_MapWidth() * map->GetTileSize(), 10, map->GetNumOfTiles_MapHeight() * map->GetTileSize(), 1.5, camera);
		//	GenerateCollisionBoundary(map);
			//CheckCollisionBoundary();
			DebuffCheckAndApply(dt);

			bool AttackDir = false;
			if (playerPosition.x > m_Position.x)
			{
				AttackDir = true;
			}
			else
			{
				AttackDir = false;
			}

			static float waterAttackDuration = 1;
			static float waterAttackTimer = 0;
			if (Attack && DirectionLeftRight == AttackDir)
			{
				if (waterAttackDuration <= 3 && waterAttackDuration >= 0)
				{
				this->Attacks->SetisEnemy(true);
				this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
				this->Attacks->Attack_Ability(WATER, 0);
				
					this->Attacks->SetisEnemy(true);
					this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
					this->Attacks->Attack_Basic(WATER, 0);
					waterAttackDuration -= dt;	
				}
				else
				{
					waterAttackTimer += dt;
					if (waterAttackTimer >= 3)
					{
						waterAttackTimer = 0;
						waterAttackDuration = 1;
					}
				}
			}
			//waterAttackTimer += dt;

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
			
			if (m_Behaviour->GetLastStand())
			{
				m_Behaviour->SetLastStandTimer(m_Behaviour->GetLastStandTimer() - dt);
			}

			if (m_Behaviour->GetCollide())
			{
				m_Behaviour->SetCollideTimer(m_Behaviour->GetCollideTimer() - dt);
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
					dynamic_cast<EarthBehaviour*>(m_Behaviour)->SetAttackCount(dynamic_cast<EarthBehaviour*>(m_Behaviour)->GetAttackCount() + 1);
				}
				else if (dynamic_cast<EarthBehaviour*>(m_Behaviour)->GetBossState() == EarthBehaviour::ABILITY_ATTACK_PHASE)
				{
					this->Attacks->SetisEnemy(true);
					this->Attacks->UpdateAttack(dt, this->m_Position, DirectionLeftRight);
					this->Attacks->Attack_Ability(temp, GetElementLevel(temp));
					dynamic_cast<EarthBehaviour*>(m_Behaviour)->SetAttackCount(0);
				}

			}
		}
	}


}

void Enemy::CollisionResponse(GameObject* OtherGo, GameObject_Map* Map)
{

    if (OtherGo->GetObjectType() == PROJECTILE)
    {
		Projectile* tempProj;
		tempProj = dynamic_cast<Projectile*>(OtherGo);

		if (!tempProj->getIsHostileProjectile() && tempProj->GetElement() != EARTH_2)
		{
			if (this->m_CurrEntityMoveState == WEAKENED && tempProj->GetElement() == MISC)
			{
				this->m_CurrEntityMoveState = EDIBLE;
			}
			else
			{
				if (tempProj->GetElement() == FIRE || tempProj->GetElement() == FIRE_2)
				{
					if (m_CurrElement == WATER || m_CurrElement == WATER_2)
						DamagMultiplier = 0.5;
					if (m_CurrElement == FIRE || m_CurrElement == FIRE_2)
						DamagMultiplier = 1;
					if (m_CurrElement == EARTH || m_CurrElement == EARTH_2)
						DamagMultiplier = 1.5;

					DamagMultiplier = DamagMultiplier * 0.4f;
				}
				if (tempProj->GetElement() == WATER || tempProj->GetElement() == WATER_2)
				{
					if (m_CurrElement == WATER || m_CurrElement == WATER_2)
						DamagMultiplier = 1;
					if (m_CurrElement == FIRE || m_CurrElement == FIRE_2)
						DamagMultiplier = 1.5;
					if (m_CurrElement == EARTH || m_CurrElement == EARTH_2)
						DamagMultiplier = 0.5;
				}
				if (tempProj->GetElement() == EARTH || tempProj->GetElement() == EARTH_2)
				{
					if (m_CurrElement == WATER || m_CurrElement == WATER_2)
						DamagMultiplier = 1.5;
					if (m_CurrElement == FIRE || m_CurrElement == FIRE_2)
						DamagMultiplier = 0.5;
					if (m_CurrElement == EARTH || m_CurrElement == EARTH_2)
						DamagMultiplier = 1;

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
		else if (!tempProj->getIsHostileProjectile() && tempProj->GetElement() == EARTH_2)
		{
			float TempLifeTime = tempProj->GetElementLevel() * 2 + 5;
			float radius = 10;

			Mesh* Quad = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1));

			for (int offset = 0; offset < 15; offset += 5)
			{
				Vector3 SpawnLocation_Right = Vector3((int)this->GetPosition().x + radius, (int)this->GetPosition().y + offset, (int)this->GetPosition().z);
				Vector3 SpawnLocation_Left = Vector3((int)this->GetPosition().x - radius, (int)this->GetPosition().y + offset, (int)this->GetPosition().z);

				int LeftSpawnTile_X = (int)(SpawnLocation_Left.x / Map->GetTileSize());
				int LeftSpawnTile_Y = (int)(SpawnLocation_Left.y / Map->GetTileSize());

				int RightSpawnTile_X = (int)(SpawnLocation_Right.x / Map->GetTileSize());
				int RightSpawnTile_Y = (int)(SpawnLocation_Right.y / Map->GetTileSize());

				if (Map->m_GameObjectMap[RightSpawnTile_Y][RightSpawnTile_X]->GetType() == GO_NONE)
				{
					Environment* temp1 = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_EARTH_WALL, Vector3(RightSpawnTile_X * Map->GetTileSize(), RightSpawnTile_Y * Map->GetTileSize(), 0), Vector3(5, 5, 5), true, true, Quad, "Image//Tiles//wood.tga"));
					temp1->Init(true, false);
					temp1->SetElement(EARTH);
					temp1->SetLifeTimeBool(true);
					temp1->SetLifeTime(TempLifeTime);
					Map->AddIntoMap(temp1);
				}

				if (Map->m_GameObjectMap[LeftSpawnTile_Y][LeftSpawnTile_X]->GetType() == GO_NONE)
				{
					Environment* temp2 = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_EARTH_WALL, Vector3(LeftSpawnTile_X * Map->GetTileSize(), LeftSpawnTile_Y * Map->GetTileSize(), 0), Vector3(5, 5, 5), true, true, Quad, "Image//Tiles//wood.tga"));
					temp2->Init(true, false);
					temp2->SetElement(EARTH);
					temp2->SetLifeTimeBool(true);
					temp2->SetLifeTime(TempLifeTime);
					Map->AddIntoMap(temp2);
				}
			}

			tempProj->SetActive(false);
		}

        if (this->m_ObjectType == ENEMY && this->m_CurrEntityMoveState==WEAKENED && tempProj->GetElement() == MISC && tempProj->getIsHostileProjectile() == false && this->getEnemyType()!=WATERBOSS)
        {
			this->m_CurrEntityMoveState = EDIBLE;
        }
    }

	if (OtherGo->GetObjectType() == ENEMY)
	{
		this->m_Behaviour->SetCollide(true);
		dynamic_cast<Enemy*>(OtherGo)->m_Behaviour->SetCollide(true);
	}
}

void  Enemy::setBehaviour(Behaviour* behaviour)
{
	this->m_Behaviour = behaviour;
}

Behaviour*  Enemy::getBehaviour()
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