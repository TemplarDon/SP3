#include "Player.h"

Player::Player(void)
	: jumpspeed(0)
	, m_HealthCharges(0)
{

    m_CurrElement = EARTH;
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
	SetEntityMaxHealth(50);
    CurrHealth = MaxHealth;
    Damage = 5;
	SetEntityMovementSpeed(1);
    Attacks->Init(GetEntityDamage(), 10.f);
	m_RespawnPos = m_Position;
	m_CurrLevel = TEST;

}

// Player Update
void Player::PlayerUpdate(GameObject_Map* Map)
{ 

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
}

void Player::UpdateHealthCharges()
{
	if (m_HealthCharges >= 5)
	{
		this->MaxHealth += 2;
		m_HealthCharges = 0;
	}
}

void Player::CollisionResponse(GameObject* OtherGo)
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
        if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == FIRE_2 )
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

}



