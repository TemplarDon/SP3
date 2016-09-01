#include "Player.h"
#include "Environment.h"
#include "GameObjectManager.h"

Player::Player(void)
	: jumpspeed(0)
	, m_HealthCharges(0)
	, m_Invulnerability(false)
	, m_InvulTimer(1)
{

    m_CurrElement = FIRE;
    isEnemyEntity = false;
    Attacks = new AttackBase;
	m_LastCheckpoint = NULL;
	m_FireBossClear = false;
	m_WaterBossClear = false;
	m_EarthBossClear = false;
}

Player::~Player(void)
{
	if (Attacks)
	{
		delete Attacks;
		Attacks = NULL;
	}
}

// Player Init
void Player::Init(void)
{
	SetEntityMaxHealth(10);
    CurrHealth = MaxHealth;
    Damage = 3;
	SetEntityMovementSpeed(1);
    Attacks->Init(GetEntityDamage(), 10.f);
	m_RespawnPos = m_Position;
	m_CurrLevel = TUTORIAL_LEVEL;
	m_InvulTimer = 1;
}

// Player Update
void Player::Update(double dt, GameObject_Map* Map, Camera camera)
{ 
	interDT = dt;
	GenerateCollisionBoundary(Map);
	CheckCollisionBoundary();
	mapFineOffset_x = mapOffset_x % Map->GetTileSize();

	ExecuteAbility(dt);
	DebuffCheckAndApply(dt);
	if (m_CurrLevel== WATER_BOSS_LEVEL1 || m_CurrLevel== WATER_LEVEL)
	{
		ConstrainPlayer(45  + mapOffset_x + mapFineOffset_x, 100 + mapOffset_x + mapFineOffset_x, 20+ mapOffset_y + mapFineOffset_y, 50+ mapOffset_y + mapFineOffset_y, 1.5);
	}
	else
	{
		ConstrainPlayer(20 + mapOffset_x + mapFineOffset_x, 100 + mapOffset_x + mapFineOffset_x, 15 + mapOffset_y + mapFineOffset_y, 80 + mapOffset_y + mapFineOffset_y, 1.5);

	}

	if (m_Invulnerability)
	{
		m_InvulTimer -= (float)dt;
		if (m_InvulTimer <= 0)
		{
			m_Invulnerability = false;
			m_InvulTimer = 1;
		}
	}
	if (!SheildRegen)
       {
           SheildRegenTimer += (float)dt;
           if (SheildRegenTimer >= 4)
           {
               SheildRegen = true;
               SheildRegenTimer = 0.f;
           }
       }
       if (SheildRegen)
       {
           CurrSheild += 5 * (float)dt;
           if (CurrSheild > MaxSheild)
           {
               CurrSheild = MaxSheild;
           }
       }
}
void Player::SetFireBossKill(bool input)
{
	m_FireBossClear = input;
}
void Player::SetWaterBossKill(bool input)
{
	m_WaterBossClear = input;
}
void Player::SetEarthBossKill(bool input)
{
	m_EarthBossClear = input;
}
bool Player::CheckIfSexy()
{
	if (m_FireBossClear && m_WaterBossClear && m_EarthBossClear)
		return true;
	else
		return false;
}
void Player::SetRespawnPos(Vector3 RespawnPos)
{
	m_RespawnPos = RespawnPos;
}

Vector3 Player::GetRespawnPos()
{
	return m_RespawnPos;
}
bool Player::CheckIsDead()
{
	if (CurrHealth <= 0)
	{
		music.playSE("Music//death.wav");
		return true;
	}

	else
		return false;
}

Checkpoint*  Player::GetCheckpoint()
{
	return m_LastCheckpoint;
}
void Player::Death()
{

	m_Position = m_LastCheckpoint->GetPosition();
	mapOffset_x = m_LastCheckpoint->GetMapOffset().x;
	mapOffset_y = m_LastCheckpoint->GetMapOffset().y;

	CurrHealth = MaxHealth;
	CurrSheild = MaxSheild;
	

	if (m_ElementsLevelMap[FIRE] > 0)
	{
		m_ElementsLevelMap[FIRE] -= 1;
		this->Attacks->SetAttackDamage(this->Attacks->GetAttackDamage() - 2);
	}
	if (m_ElementsLevelMap[WATER] > 0)
	{
		m_ElementsLevelMap[WATER] -= 1;
		this->MaxHealth -= 5;
	}
	if (m_ElementsLevelMap[EARTH] > 0)
	{
		m_ElementsLevelMap[EARTH] -= 1;
		this->MaxSheild -= 5;
	}
}

LEVEL Player::GetCurrentLevel()
{
	return m_CurrLevel;
}

void Player::SetCurrentLevel(LEVEL newLevel)
{
	m_CurrLevel = newLevel;
}

int Player::GetHealthCharges()
{
	return m_HealthCharges;
}

void Player::AddHealthCharges()
{
	++m_HealthCharges;
	m_HealthCharges = Math::Min(m_HealthCharges, 5);
}

void Player::UseHealthCharge()
{
	if (m_HealthCharges > 0)
	{
		music.playSE("Music//heal.wav");
		--m_HealthCharges;
		CurrHealth += 5;

		CurrHealth = Math::Min(CurrHealth, MaxHealth);
	}
}

void Player::CollisionResponse(GameObject* OtherGo, GameObject_Map* Map)
{
	if (OtherGo->GetObjectType() == ENVIRONMENT)
	{
		if (OtherGo->GetType() == GO_DROP_HEALTH)
		{
			this->AddHealthCharges();
		}
	}

	if (OtherGo->GetType() == GO_CHECKPOINT)
	{
		Vector3 mapoffset;
		mapoffset.x = mapOffset_x;
		mapoffset.y = mapOffset_y;

		this->m_LastCheckpoint = dynamic_cast<Checkpoint*>(OtherGo);
		this->m_LastCheckpoint->SetCheckpoint(m_CurrLevel, mapoffset);
	}

	if (OtherGo->GetObjectType() == PROJECTILE)
	{
		Projectile* tempProj;
		tempProj = dynamic_cast<Projectile*>(OtherGo);
		if (tempProj->getIsHostileProjectile())
		{

			if (tempProj->GetElement() == FIRE)
			{
				if (m_CurrElement == WATER)
					DamagMultiplier = 0.5f;
				if (m_CurrElement == FIRE)
					DamagMultiplier = 1.f;

				if (m_CurrElement == EARTH)
					DamagMultiplier = 1.5f;
				DamagMultiplier = DamagMultiplier * 0.3f;
			}
			if (tempProj->GetElement() == WATER)
			{
				if (m_CurrElement == WATER)
					DamagMultiplier = 1.f;
				if (m_CurrElement == FIRE)
					DamagMultiplier = 1.5f;
				if (m_CurrElement == EARTH)
					DamagMultiplier = 0.5f;
			}
			if (tempProj->GetElement() == EARTH)
			{
				if (m_CurrElement == WATER)
					DamagMultiplier = 1.5f;
				if (m_CurrElement == FIRE)
					DamagMultiplier = 0.5f;
				if (m_CurrElement == EARTH)
					DamagMultiplier = 1.f;
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
			//Water and Water2 slow
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


		if (tempProj->GetElement() == EARTH_2 && tempProj->getIsHostileProjectile())
		{
			// Find if bullet is left or right of player
			bool PlayerRight = false;
			bool PlayerLeft = false;
			if (tempProj->GetPosition().x > this->m_Position.x)
			{
				PlayerLeft = true;
				PlayerRight = false;
			}
			else
			{
				PlayerLeft = false;
				PlayerRight = true;
			}

			float TempLifeTime = tempProj->GetElementLevel() * 2 + 5;
			float radius = 10;

			Mesh* Quad = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1));

			// Spawn base blocks
			for (int offset = 0; offset < 10; offset += 5)
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

			// Spawn more blocks, based on direction
			for (int offset = 10; offset < 45; offset += 5)
			{
				Vector3 SpawnLocation;
				if (PlayerRight)
				{
					// Spawn on player's right
					SpawnLocation = Vector3((int)this->GetPosition().x + radius, (int)this->GetPosition().y + offset, (int)this->GetPosition().z);
				}
				else if (PlayerLeft)
				{
					// Spawn on player's left
					SpawnLocation = Vector3((int)this->GetPosition().x - radius, (int)this->GetPosition().y + offset, (int)this->GetPosition().z);
				}

				int SpawnTile_X = (int)(SpawnLocation.x / Map->GetTileSize());
				int SpawnTile_Y = (int)(SpawnLocation.y / Map->GetTileSize());

				if (Map->m_GameObjectMap[SpawnTile_Y][SpawnTile_X]->GetType() == GO_NONE)
				{
					Environment* temp1 = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_EARTH_WALL, Vector3(SpawnTile_X * Map->GetTileSize(), SpawnTile_Y * Map->GetTileSize(), 0), Vector3(5, 5, 5), true, true, Quad, "Image//Tiles//wood.tga"));
					temp1->Init(true, false);
					temp1->SetElement(EARTH);
					temp1->SetLifeTimeBool(true);
					temp1->SetLifeTime(TempLifeTime);
					Map->AddIntoMap(temp1);
				}
			}
		}

		if (tempProj->GetElement() == MISC && tempProj->getIsHostileProjectile())
		{
			if (this->m_Position.x > tempProj->GetPosition().x)
			{
				// Player on the right, knock player right
				m_Position.x += m_Position.Normalized().x;
			}
			else
			{
				// Player on the left, knock player left
				m_Position.x -= m_Position.Normalized().x;
			}
		}
	}
}

void Player::SetInvulnerability(bool status)
{
	m_Invulnerability = status;
}

bool Player::GetInvulnerability()
{
	return m_Invulnerability;
}

