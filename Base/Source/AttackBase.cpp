#include "AttackBase.h"
#include "GameObjectManager.h"
#include "Entity.h"
AttackBase::AttackBase()
{
    m_AttackDamage = 0;
    MAXprojectilecount = 30;
    m_projectileCount = 0;
    m_meleeCount = 0;
    m_AbilityCount = 0;
    m_AttackDirection = true;
    m_AttackDebounce = 0;
    m_Range = 0.f;
    m_CanAttack = true;
    isEnemy = false;
    m_Dashleft = false;
    m_Dashright = false;
    m_SteamBoost = false;
    m_Healbuff = false;
    m_HealDuration = 0.f;
    m_SteamDuration = 0.f;
}
AttackBase::~AttackBase()
{

}
void AttackBase::Init(int AttackDamage, float range)
{
    m_AttackDamage = AttackDamage;
    m_Range = range;
    ProjectilePH = MeshBuilder::GenerateQuad("ProjectilePlaceHolder", Color(1, 1, 1));
    m_Dashleft = false;
    m_Dashright = false;
}
void AttackBase::SetisEnemy(bool isEnemy)
{
    this->isEnemy = isEnemy;
}
void AttackBase::SetAttackType()
{
    if (m_CurrElement == NO_ELEMENT)
        m_CurrAttackType == NO_ATTACK_TYPE;
    else if (m_CurrElement == FIRE || m_CurrElement == WATER)
        m_CurrAttackType = RANGED;
	else if (m_CurrElement == EARTH)
		m_CurrAttackType = MELEE;
	else if (m_CurrElement == MISC)
		m_CurrAttackType = SUCK;
    else
        m_CurrAttackType = ABILITY;
}

int AttackBase::GetAttackDamage()
{
    return m_AttackDamage;
}


void AttackBase::UpdateAttack(double dt, ELEMENT EntityCurrElement, Vector3 pos, bool leftright)
{
    interdt = dt;
    m_CurrElement = EntityCurrElement;
    SetAttackType();
    m_EntityPos = pos;
    m_AttackDirection = leftright;
    
    if (!m_CanAttack)
    {
        m_AttackDebounce += 12.5 * (float)dt;
        if (m_AttackDebounce >= 5.f)
        {
            m_CanAttack = true;
            m_AttackDebounce = 0.f;
        }
    }

    //Steam boost timer
    if (m_SteamBoost)
    {
        m_SteamDuration += 2*(float)dt;
        if (m_SteamDuration > 10.f)
        {
            m_SteamBoost = false;
            m_SteamDuration = 0.f;
        }
    }
}
void AttackBase::LaunchAttack()
{
    SetAttackType();
    if (m_CanAttack)
    {
        if (m_CurrAttackType == MELEE)
            Attack_Melee();
        else if (m_CurrAttackType == RANGED)
            Attack_Ranged();
		else if (m_CurrAttackType == ABILITY)
			Attack_Ability();
		else if (m_CurrAttackType == SUCK)
			Attack_Suck();
     
    }
}
void AttackBase::Attack_Ability()
{
    if (m_CurrElement == FIRE_2)
    {
        Projectile* temp;
        temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 5, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
        temp->projectileInit(m_AttackDirection, m_EntityPos, 50.0f, m_AttackDamage, 0.5f, m_CurrElement, false,0);

        m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
        m_AbilityCount += 1;
        if (m_AbilityCount >= MAXprojectilecount)
        {
            m_AbilityCount = 0;
        }
        m_CanAttack = false;
    }
    else if (m_CurrElement == WATER_2)
    {
        if (m_AttackDirection && !m_Dashleft)//right
        {
            m_Dashright = true;
  
            m_CanAttack = false;
        }
        else if (!m_AttackDirection && !m_Dashright)//left
        {
            m_Dashleft = true;

            m_CanAttack = false;
        }
    
    }
    else if (m_CurrElement == EARTH_2)
    {
        Projectile* temp;
		//SpriteAnimation* sa=
        temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(5, 5, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
		temp->projectileInit(m_AttackDirection, m_EntityPos + 2, 50.0f, m_AttackDamage, 0.1f, m_CurrElement, false, 0);

        m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
        m_AbilityCount += 1;
        if (m_AbilityCount >= MAXprojectilecount)
        {
            m_AbilityCount = 0;
        }
        m_CanAttack = false;
    }
    else if (m_CurrElement == SAND)
    {
        //do sand stuff
    }
    else if (m_CurrElement == STEAM)
    {
        float a = 0.f;
        m_SteamBoost = true;
        for (int i = 0; i < 5 ; i++)
        {
            Vector3 tempVecpos = m_EntityPos;
            tempVecpos.x = m_EntityPos.x + 2 - i;
     
            if (i < 3)
                a = m_EntityPos.y + i;
            else
                a = m_EntityPos.y - 1;
            tempVecpos.y = m_EntityPos.y;
            Projectile* temp;
            temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 5, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
            if (i <3)
				temp->projectileInit(m_AttackDirection, tempVecpos, 50.0f, m_AttackDamage, 0.1f, m_CurrElement, false, 0);
            else
				temp->projectileInit(!m_AttackDirection, tempVecpos, 50.0f, m_AttackDamage, 0.1f, m_CurrElement, false, 0);

            m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
            m_AbilityCount += 1;
            if (m_AbilityCount >= MAXprojectilecount)
            {
                m_AbilityCount = 0;
            }
        }
        m_CanAttack = false;
    }
    else if (m_CurrElement == WOOD)
    {
        //do wood stuff
        m_Healbuff = true;

    }
}

void AttackBase::Attack_Melee()
{
    Projectile* temp;
    temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_MeleeStrike[m_meleeCount].GetPosition(), Vector3(1,5,2), true, true, ProjectilePH, "Image//Projectiles/earth_projectile.tga"));
	temp->projectileInit(m_AttackDirection, m_EntityPos, 5.0f, m_AttackDamage, 0.2f, m_CurrElement, isEnemy, 30);
    //temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_MeleeStrike[m_meleeCount].GetPosition(), Vector3(1,5,2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
    //temp->projectileInit(m_AttackDirection, m_EntityPos, 50.0f, m_AttackDamage, 0.1f,isEnemy);

    m_MeleeStrike[m_meleeCount].SetElement(m_CurrElement);
    m_meleeCount += 1;
    if (m_meleeCount >= MAXprojectilecount)
    {
        m_meleeCount = 0;
    }
    m_CanAttack = false;

}
void AttackBase::Attack_Ranged()
{
    Vector3 tempscale;
    if (m_projectileCount <= 5)
        tempscale = Vector3(2, 2, 2);
    else
        tempscale = Vector3(1, 1, 1);
    //GameObjectManager::SpawnProjectileObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, 2, 5,m_AttackDirection , 50.0f ,ProjectilePH, "Image//Tiles/projectilePH.tga");

    Projectile* temp;
	if (m_CurrElement == FIRE)
	{
		temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, ProjectilePH, "Image//Projectiles/fire_projectile.tga"));
	}
	else if(m_CurrElement == WATER)
	{
		temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, ProjectilePH, "Image//Projectiles/water_projectile.tga"));
	}
    
	temp->projectileInit(m_AttackDirection, m_EntityPos, 5.f, m_AttackDamage, 1, m_CurrElement, isEnemy, -50);
    //temp->projectileInit(m_AttackDirection,m_EntityPos,50.0f,m_AttackDamage,10.0f, isEnemy);

    m_Projectiles[m_projectileCount].SetElement(m_CurrElement);
    m_projectileCount += 1;

    if (m_projectileCount >= MAXprojectilecount)
    {
        m_projectileCount = 0;
    }
    m_CanAttack = false;

}
void AttackBase::Attack_Suck()
{
	Projectile* temp;
	temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), Vector3(2, 2, 2), true, true, ProjectilePH));
	temp->projectileInit(m_AttackDirection, m_EntityPos, 5.f, 0, 1, m_CurrElement, isEnemy, 0);
	m_Projectiles[m_projectileCount].SetElement(m_CurrElement);
	m_projectileCount += 1;
	if (m_projectileCount >= MAXprojectilecount)
	{
		m_projectileCount = 0;
	}
	m_CanAttack = false;
}
bool AttackBase::GetDashLeftStatus()
{
    return m_Dashleft;
}
bool AttackBase::GetDashRightStatus()
{
    return m_Dashright;
}
void AttackBase::SetDashStatus(bool dashleft, bool dashright)
{
    m_Dashleft = dashleft;
    m_Dashright = dashright;
}
bool AttackBase::GetSteamStatus()
{
    return m_SteamBoost;
}
void AttackBase::SetSteamStatus(bool steamstatus)
{
    m_SteamBoost = steamstatus;
}