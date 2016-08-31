#include "Collectibles.h"
#include "Player.h"

Collectibles::Collectibles()
	: m_Factor(0)
{}

Collectibles::~Collectibles()
{}

void Collectibles::InitCollectible(int factor)
{
	m_Factor = factor;
}

void Collectibles::SetFactor(int factor)
{
	m_Factor = factor;
}

int Collectibles::GetFactor()
{
	return m_Factor;
}

void Collectibles::CollisionResponse(GameObject* OtherGo)
{
	if (OtherGo->GetObjectType() == PLAYER)
	{
		if (OtherGo->GetType() == GO_DROP_HEALTH)
		{
			dynamic_cast<Player*>(OtherGo)->AddHealthCharges();
		}

		if (OtherGo->GetType() == GO_FIRE_HEART)
		{
			dynamic_cast<Player*>(OtherGo)->SetFireBossKill(true);
		}

		if (OtherGo->GetType() == GO_EARTH_HEART)
		{
			dynamic_cast<Player*>(OtherGo)->SetEarthBossKill(true);
		}

		if (OtherGo->GetType() == GO_WATER_HEART)
		{
			dynamic_cast<Player*>(OtherGo)->SetWaterBossKill(true);
		}
		this->m_Active = false;
	}
}