#include "Environment.h"
#include "GameObjectManager.h"

Environment::Environment()
	: m_Destructible(false)
	, m_CanFall(false)
	, m_FallSpeed(5)
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
	//if (m_CanFall)
	//{
	//	int EnvironmentPos_X = (int)((mapOffset_x + m_Position.x)) / Map->GetTileSize();
	//	int EnvironmentPos_Y = (int)(m_Position.y / Map->GetTileSize());

	//	GameObject* CheckGameObject_1 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];
	//	if ((CheckGameObject_1->GetCollidable() && CheckGameObject_1->GetActive()) || ((CheckGameObject_2->GetCollidable()) && CheckGameObject_2->GetActive()))
	//	{
	//		m_Position = m_PrevPos;
	//		m_bJumping = false;
	//		m_CurrEntityMoveState = ON_GROUND;
	//		JumpVel = 0;
	//	}
	//}
}

void Environment::CollisionResponse(GameObject* OtherGo)
{	
	if (OtherGo->GetObjectType() == PROJECTILE)
	{
		Projectile* temp = dynamic_cast<Projectile*>(OtherGo);

		switch (this->m_CurrElement)
		{
		case WATER:
		{
			if (temp->GetElement() == EARTH)
			{
				this->m_Active = false;
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
			}
			else
			{
				OtherGo->SetActive(false);
			}
			break;
		}
		}


	}
}