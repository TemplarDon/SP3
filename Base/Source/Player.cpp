#include "Player.h"

Player::Player(void)
	: jumpspeed(0)
	, m_HealthCharges(0)
{

    m_CurrElement = FIRE;
    isEnemyEntity = false;
    Attacks = new AttackBase;


	m_ElementArray[0] = FIRE;
	m_ElementArray[1] = WATER;
	m_ElementArray[2] = FIRE;
	m_ElementArray[3] = WATER;
	m_ElementArray[4] = FIRE;
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

void Player::AddElementCharge(ELEMENT ToBeAdded)
{
	for (int i = 0; i < 5; ++i)
	{
		if (m_ElementArray[i] == NO_ELEMENT)
		{
			m_ElementArray[i] = ToBeAdded;
			break;
		}
	}
}

void Player::RemoveElementCharge()
{
	m_ElementArray[0] = NO_ELEMENT;
	ReorderElements();
}

void Player::ReorderElements()
{
	ELEMENT temp = m_ElementArray[0];

	m_ElementArray[0] = m_ElementArray[1];
	m_ElementArray[1] = m_ElementArray[2];
	m_ElementArray[2] = m_ElementArray[3];
	m_ElementArray[3] = m_ElementArray[4];
	m_ElementArray[4] = temp;

	for (int i = 0; i < 5; ++i)
	{
		if (m_ElementArray[i] == NO_ELEMENT)
		{
			if (i < 4)
			{
				for (int y = i; y < 5; ++y)
				{
					if (m_ElementArray[y] != NO_ELEMENT)
					{
						m_ElementArray[i] = m_ElementArray[y];
						m_ElementArray[y] = NO_ELEMENT;
						break;
					}
				}
			}
		}
	}
}

ELEMENT* Player::GetElementArray()
{
	return m_ElementArray;
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

	if (OtherGo->GetObjectType() == PROJECTILE&& tempProj->getIsHostileProjectile() == true)
	{

		if (tempProj->GetElement() == FIRE)
		{
			if (m_CurrElement == WATER)
				DamagMultiplier = 0.5;
			if (m_CurrElement == FIRE)
				DamagMultiplier = 1;
			if (m_CurrElement == EARTH)
				DamagMultiplier = 1.5;
		}
		if (tempProj->GetElement() == WATER)
		{
			if (m_CurrElement == WATER)
				DamagMultiplier = 1;
			if (m_CurrElement == FIRE)
				DamagMultiplier = 1.5;
			if (m_CurrElement == EARTH)
				DamagMultiplier = 0.5;
		}
		if (tempProj->GetElement() == EARTH)
		{
			if (m_CurrElement == WATER)
				DamagMultiplier = 1.5;
			if (m_CurrElement == FIRE)
				DamagMultiplier = 0.5;
			if (m_CurrElement == EARTH)
				DamagMultiplier == 1;
		}
		//debuffs
		//steam knockback
		if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == STEAM && !deBuff_KnockBack)
		{
			deBuff_KnockBack = true;
			if (dynamic_cast<Projectile*>(OtherGo)->getVelocity().x < 0)
			{
				KnockBackDestX = m_Position.x - 3;
				KnockBackLeftRight = false;
			}
			else if (dynamic_cast<Projectile*>(OtherGo)->getVelocity().x > 0)
			{
				KnockBackDestX = m_Position.x + 3;
				KnockBackLeftRight = true;
			}
		}
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
		if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == SAND || dynamic_cast<Projectile*>(OtherGo)->GetElement() == FIRE_2)
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
		//earth 2 stun
		if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == EARTH_2)
		{
			if (deBuff_Stunned = true)
			{
				deBuff_StunTimer = 0.f;
			}
			else
			{
				deBuff_Stunned = true;
			}
		}
		TakeDamage(tempProj->getDamage());
		OtherGo->SetActive(false);
	}

}



