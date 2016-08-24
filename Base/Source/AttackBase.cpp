#include "AttackBase.h"
#include "GameObjectManager.h"
#include "Entity.h"
AttackBase::AttackBase()
{
    m_AttackDamage = 1;
    MAXprojectilecount = 30;
    m_projectileCount = 0;
    m_meleeCount = 0;
    m_AbilityCount = 0;
    m_AttackDirection = true;
    m_AttackDebounce = 0;
    m_Range = 0.f;
    m_CanAttack = true;
    m_RootedForAttack = false;
    isEnemy = false;

    ab_HailStorm = false;
    ab_HailStorm_isCD = false;
    ab_Obliterate = false;
    ab_Obliterate_isCD = false;
    ab_Cataclysm = false;
    ab_Cataclysm_isCD = false;
    ab_Obliterate_Counter = 0;
    ab_HailStorm_debounce = false;
    ab_Obliterate_debounce= false;
    ab_Cataclysm_debounce = false;
    ab_FIRE2_timer = 0.f;
    ab_FIRE2_CDtimer = 0.f;

}
AttackBase::~AttackBase()
{

}
void AttackBase::Init(int AttackDamage, float range)
{
    m_AttackDamage = AttackDamage;
    m_Range = range;
    ProjectilePH = MeshBuilder::GenerateQuad("ProjectilePlaceHolder", Color(1, 1, 1));
}
void AttackBase::SetisEnemy(bool isEnemy)
{
    this->isEnemy = isEnemy;
}
void AttackBase::SetAttackType()
{
    if (m_CurrElement == NO_ELEMENT)
        m_CurrAttackType == NO_ATTACK_TYPE;
    else if (m_CurrElement == FIRE || m_CurrElement == WATER || m_CurrElement == EARTH)
        m_CurrAttackType = RANGED;
	else if (m_CurrElement == MISC)
		m_CurrAttackType = SUCK;
    else
        m_CurrAttackType = ABILITY;
}

int AttackBase::GetAttackDamage()
{
    return m_AttackDamage;
}
void  AttackBase::SetAttackElement(ELEMENT m_CurrElement)
{
	this->m_CurrElement = m_CurrElement;
}

void AttackBase::UpdateAttack(double dt, ELEMENT EntityCurrElement, Vector3 pos, bool leftright)
{
    interdt = dt;
    m_CurrElement = EntityCurrElement;
    SetAttackType();
    m_EntityPos = pos;
    m_AttackDirection = leftright;
    Debouncers(dt);
    Ability_Run();

    //Steam boost timer
   /* if (m_SteamBoost)
    {
        m_SteamDuration += 2*(float)dt;
        if (m_SteamDuration > 10.f)
        {
            m_SteamBoost = false;
            m_SteamDuration = 0.f;
        }
    }*/
}
void AttackBase::Debouncers(double dt)
{
    //basic attack debouncer
    if (!m_CanAttack)
    {
        m_AttackDebounce += 12.5f * (float)dt;
        if (m_AttackDebounce >= 5.f)
        {
            m_CanAttack = true;
            m_AttackDebounce = 0.f;
        }
    }

    //Fire 2 wave debouncer
    if (ab_Obliterate_debounce)
    {
        ab_FIRE2_timer += 50.f *(float)dt;
        if (ab_FIRE2_timer >= 5.f)
        {
            ab_Obliterate_debounce = false;
            ab_FIRE2_timer = 0.f;
        }
    }
    //fire 2 cooldown timer
    if (ab_Obliterate_isCD)
    {
        ab_FIRE2_CDtimer += (float)dt;
        if (ab_FIRE2_CDtimer >= 2.5f)
        {
            ab_Obliterate_isCD = false;
            ab_FIRE2_CDtimer = 0.f;
        }
    }
}
void AttackBase::LaunchAttack(int level)
{
    m_ElementLevel = level;
    SetAttackType();
    if (m_CanAttack)
    {
        if (m_CurrAttackType == RANGED)
            Attack_Ranged();
		else if (m_CurrAttackType == ABILITY)
			Attack_Ability();
		else if (m_CurrAttackType == SUCK)
			Attack_Suck();
     
    }
}
void::AttackBase::Attack_Ability()
{
    if (m_CurrElement == FIRE_2 && !ab_Obliterate_isCD)
    {
        ab_Obliterate = true;
        m_RootedForAttack = true;
        
    }
    if (m_CurrElement == WATER_2 && !ab_HailStorm_isCD)
    {
        ab_HailStorm = true;
    }
    if (m_CurrElement == EARTH_2 && !ab_Cataclysm_isCD)
    {
        ab_Cataclysm = true;
    }
}
void AttackBase::Ability_Run()
{
    if (ab_Obliterate && !ab_Obliterate_debounce)
    {
        if (ab_Obliterate_Counter >= m_ElementLevel + 3)
        {
            //resets
            ab_Obliterate = false;
            ab_Obliterate_Counter = 0;
            m_RootedForAttack = false;
            ab_Obliterate_debounce = false;

            //initiate cooldown
            ab_Obliterate_isCD = true;

        }
        else
        {
            float templifetime = m_ElementLevel * 0.25f + 0.3f;
            for (int i = 0; i < 7; i++)
            {
                float angletemp;
                if (i == 0)
                    angletemp = -15.f;
                else if (i == 1)
                    angletemp = -10.f;
                else if (i == 2)
                    angletemp = -5.f;
                else if (i == 3)
                    angletemp = 0.f;
                else if (i == 4)
                    angletemp = 5.f;
                else if (i == 5)
                    angletemp = 10.f;
                else if (i == 6)
                    angletemp = 15.f;

                Projectile* temp;
                temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 1, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
                temp->projectileInit(m_AttackDirection, m_EntityPos + 2, 75.0f, m_AttackDamage, templifetime, m_CurrElement, false, angletemp);

                m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
                m_AbilityCount += 1;
                if (m_AbilityCount >= MAXprojectilecount)
                {
                    m_AbilityCount = 0;
                }
               
            }
            ab_Obliterate_debounce = true;
            ab_Obliterate_Counter += 1;
        }
    }
    else if (m_CurrElement == WATER_2)
    {
            
    }
    else if (m_CurrElement == EARTH_2)
    {
    }
}

void AttackBase::Attack_Ranged()
{
    Vector3 tempscale;
	tempscale = Vector3(2, 2, 2);

    Projectile* temp;
	if (m_CurrElement == EARTH)
	{
		temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, ProjectilePH, "Image//Projectiles/fire_projectile.tga"));
		temp->projectileInit(m_AttackDirection, m_EntityPos, 30.f, m_AttackDamage, 1, m_CurrElement, isEnemy, 45);

	}
	else if(m_CurrElement == WATER)
	{
		temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, ProjectilePH, "Image//Projectiles/water_projectile.tga"));
		temp->projectileInit(m_AttackDirection, m_EntityPos, 10.f, m_AttackDamage, 5, m_CurrElement, isEnemy, 0);
	}
    else if (m_CurrElement == FIRE)
    {
        float templifetime = m_ElementLevel *0.25f + 0.3f ;
        for (int i = 0; i < 7; i++)
        {
            float angletemp;
            if (i == 0)
                angletemp = -35.f;
            else if (i == 1)
                angletemp = -25.f;
            else if (i == 2)
                angletemp = -15.f;
            else if (i == 3)
                angletemp = 0.f;
            else if (i == 4)
                angletemp = 15.f;
            else if (i == 5)
                angletemp = 25.f;
            else if (i == 6)
                angletemp = 35.f;

            Projectile* temp;
            temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 1, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
            temp->projectileInit(m_AttackDirection, m_EntityPos + 2, 50.0f, m_AttackDamage, templifetime, m_CurrElement, false, angletemp);

            m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
            m_AbilityCount += 1;
            if (m_AbilityCount >= MAXprojectilecount)
            {
                m_AbilityCount = 0;
            }
            m_CanAttack = false;
        }

        m_Projectiles[m_projectileCount].SetElement(m_CurrElement);
        m_projectileCount += 1;

        if (m_projectileCount >= MAXprojectilecount)
        {
            m_projectileCount = 0;
        }
        m_CanAttack = false;
    }

}
void AttackBase::Attack_Suck()
{
	Projectile* temp;
	temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), Vector3(2, 2, 2), true, true, ProjectilePH,"Image//blue Idle.tga"));
	temp->projectileInit(m_AttackDirection, m_EntityPos, 50.f, 0, 1, m_CurrElement, isEnemy, 0);
	m_Projectiles[m_projectileCount].SetElement(m_CurrElement);
	m_projectileCount += 1;
	if (m_projectileCount >= MAXprojectilecount)
	{
		m_projectileCount = 0;
	}
	m_CanAttack = false;
}
