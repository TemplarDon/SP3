#include "Environment.h"
#include "GameObjectManager.h"

Environment::Environment()
	: m_Destructible(false)
	, m_CanFall(false)
	, m_FallSpeed(1)
	, m_HasLifeTime(false)
{}

Environment::~Environment()
{}

void Environment::Init(bool Destructible, bool CanFall)
{
	m_Destructible = Destructible;
	m_CanFall = CanFall;
}

void Environment::Update(double dt, GameObject_Map* Map)
{
	if (m_CanFall)
	{
		int EnvironmentPos_X = (int)((/*mapOffset_x + */m_Position.x)) / Map->GetTileSize();
		int EnvironmentPos_Y = (int)(m_Position.y / Map->GetTileSize());

		float MinYPos;

		// Y-Axis Boundary (Bottom)
		for (int i = EnvironmentPos_Y; i >= 0; --i)
		{
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[i][EnvironmentPos_X];
			if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive() && i != EnvironmentPos_Y && this != CheckGameObject_2)
			{
				MinYPos = (CheckGameObject_2->GetPosition().y) + (Map->GetTileSize());
				break;
			}
			MinYPos = (0.5 * Map->GetTileSize());
		}

		m_Position.y -= 10 * (float)dt;

		if (m_Position.y < MinYPos)
		{
			m_Position.y = MinYPos;
		}
	}

	if (m_HasLifeTime)
	{
		m_LifeTime -= dt;
		if (m_LifeTime <= 0)
		{
			this->m_Active = false;
		}
	}
}

void Environment::Update_Sheild(Vector3 playerpos)
{
    Vector3 dir = playerpos - m_Position;
    if (dir.x < 0)
        m_Position = playerpos + Vector3(-5, 0, 0);
    if (dir.x > 0)
        m_Position = playerpos + Vector3(5, 0, 0);
}

void Environment::CollisionResponse(GameObject* OtherGo, GameObject_Map* Map)
{	
	if (OtherGo->GetObjectType() == PROJECTILE && this->m_Destructible)
	{
		Projectile* temp = dynamic_cast<Projectile*>(OtherGo);

		switch (this->m_CurrElement)
		{
		case WATER:
		{
			if (temp->GetElement() == EARTH_2)
			{
				this->m_Active = false;
				this->m_Collidable = false;
			}
			else
			{
				OtherGo->SetActive(false);
			}
			break;
		}

		case EARTH:
		{
			if (temp->GetElement() == FIRE_2)
			{
				this->m_Active = false;
				this->m_Collidable = false;
			}
			else
			{
				OtherGo->SetActive(false);
			}
			break;
		}

		case FIRE:
		{
			if (temp->GetElement() == WATER_2)
			{
				this->m_Active = false;
				this->m_Collidable = false;
			}
			else
			{
				OtherGo->SetActive(false);
			}
			break;
		}

		case NO_ELEMENT:
		{
			if (temp->GetElement() != FIRE_2)
				OtherGo->SetActive(false);

			if (temp->GetElement() == EARTH_2)
			{
				float TempLifeTime = temp->GetElementLevel() * 2 + 90;
				float radius = 15;

				Mesh* Quad = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1));

				for (int offset = 0; offset < 15; offset += 5)
				{
					Vector3 SpawnLocation_Right = Vector3((int)temp->GetPosition().x + radius, (int)temp->GetPosition().y + offset, (int)temp->GetPosition().z);
					Vector3 SpawnLocation_Left = Vector3((int)temp->GetPosition().x - radius, (int)temp->GetPosition().y + offset, (int)temp->GetPosition().z);

					int LeftSpawnTile_X = (int)(SpawnLocation_Left.x / Map->GetTileSize());
					int LeftSpawnTile_Y = (int)(SpawnLocation_Left.y / Map->GetTileSize());

					int RightSpawnTile_X = (int)(SpawnLocation_Right.x / Map->GetTileSize());
					int RightSpawnTile_Y = (int)(SpawnLocation_Right.y / Map->GetTileSize());

					if (Map->m_GameObjectMap[RightSpawnTile_Y + 1][RightSpawnTile_X]->GetType() == GO_NONE)
					{
						Environment* temp1 = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_EARTH_WALL, SpawnLocation_Right, Vector3(5, 5, 5), true, true, Quad, "Image//Tiles//wood.tga"));
						temp1->SetLifeTimeBool(true);
						temp1->SetLifeTime(TempLifeTime);
						Map->AddIntoMap(temp1);
					}

					if (Map->m_GameObjectMap[LeftSpawnTile_Y + 1][LeftSpawnTile_X]->GetType() == GO_NONE)
					{
						Environment* temp2 = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_EARTH_WALL, SpawnLocation_Left, Vector3(5, 5, 5), true, true, Quad, "Image//Tiles//wood.tga"));
						temp2->SetLifeTimeBool(true);
						temp2->SetLifeTime(TempLifeTime);
						Map->AddIntoMap(temp2);
					}
				}
			}
			break;
		}
		}
	}
}

bool Environment::GetFallStatus()
{
	return m_CanFall;
}

void Environment::SetLifeTimeBool(bool status)
{
	m_HasLifeTime = status;
}

void Environment::SetLifeTime(float time)
{
	m_LifeTime = time;
}
