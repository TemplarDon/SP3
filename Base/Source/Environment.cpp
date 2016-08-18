#include "Environment.h"
#include "GameObjectManager.h"

Environment::Environment()
	: m_Destructible(false)
	, m_CanFall(false)
	, m_FallSpeed(1)
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

		m_Position.y -= 10 * dt;

		if (m_Position.y < MinYPos)
		{
			m_Position.y = MinYPos;
		}


	}
}

void Environment::CollisionResponse(GameObject* OtherGo)
{	
	if (OtherGo->GetObjectType() == PROJECTILE && this->m_Destructible)
	{
		Projectile* temp = dynamic_cast<Projectile*>(OtherGo);

		switch (this->m_CurrElement)
		{
		case WATER:
		{
			if (temp->GetElement() == EARTH)
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
			if (temp->GetElement() == FIRE)
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
			if (temp->GetElement() == WATER)
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
		}
	}

	if (OtherGo->GetObjectType() == PLAYER && this->GetType() == GO_CHECKPOINT)
	{
		dynamic_cast<Player*>(OtherGo)->SetRespawnPos(this->m_Position);
		this->m_Active = false;
	}
}

bool Environment::GetFallStatus()
{
	return m_CanFall;
}