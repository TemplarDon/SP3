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
void Player::PlayerUpdate(double dt)
{ 
	if (m_Invulnerability)
	{
		m_InvulTimer -= (float)dt;
		if (m_InvulTimer <= 0)
		{
			m_Invulnerability = false;
			m_InvulTimer = 1;
		}
	}
}

void Player::SetRespawnPos(Vector3 RespawnPos)
{
	m_RespawnPos = RespawnPos;
}

Vector3 Player::GetRespawnPos()
{
	return m_RespawnPos;
}

void Player::Death()
{
	m_Position = m_RespawnPos;
	CurrHealth = 10;
	CurrSheild = 10;
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
		--m_HealthCharges;
		CurrHealth += 5;

		CurrHealth = Math::Min(CurrHealth, MaxHealth);
	}
}

void Player::CollisionResponse(GameObject* OtherGo, GameObject_Map* Map)
{
	if (OtherGo->GetObjectType() == PROJECTILE)
	{
		Projectile* tempProj;
		tempProj = dynamic_cast<Projectile*>(OtherGo);
		if (OtherGo->GetObjectType() == ENVIRONMENT)
		{
			if (OtherGo->GetType() == GO_CHECKPOINT)
			{
				this->SetRespawnPos(this->m_Position);
				OtherGo->SetActive(false);
			}

			if (OtherGo->GetType() == GO_DROP_HEALTH)
			{
				this->AddHealthCharges();
			}
		}

		if (OtherGo->GetObjectType() == PROJECTILE && tempProj->getIsHostileProjectile() == true)
		{

			if (tempProj->GetElement() == FIRE)
			{
				if (m_CurrElement == WATER)
					DamagMultiplier = 0.5f;
				if (m_CurrElement == FIRE)
					DamagMultiplier = 1.f;
				if (m_CurrElement == EARTH)
					DamagMultiplier = 1.5f;
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

