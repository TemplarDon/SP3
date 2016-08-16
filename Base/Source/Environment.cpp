#include "Environment.h"
#include "GameObjectManager.h"

Environment::Environment()
{}

Environment::~Environment()
{}

void Environment::CollisionResponse(GameObject* OtherGo)
{	
	if (OtherGo->GetObjectType() == PROJECTILE)
	{
		Projectile* temp = dynamic_cast<Projectile*>(OtherGo);

		switch (this->m_CurrElement)
		{
		case WATER:
		{
			if (temp->GetElement() == EARTH_2)
			{
				this->m_Active = false;
			}
			break;
		}

		case EARTH:
		{
			if (temp->GetElement() == FIRE_2)
			{
				this->m_Active = false;
			}
			break;
		}

		case FIRE:
		{
			if (temp->GetElement() == WATER_2)
			{
				this->m_Active = false;
			}
			break;
		}
		}


	}
}