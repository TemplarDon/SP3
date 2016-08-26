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
		dynamic_cast<Player*>(OtherGo)->AddHealthCharges();
		this->m_Active = false;
	}
}