#include "AttackBase.h"
#include "GameObjectManager.h"
#include "Entity.h"
#include <math.h>
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
    m_CurrAttackType = NO_ATTACK_TYPE;
    m_CurrElement = NO_ELEMENT;

    ab_HailStorm = false;
    ab_HailStorm_isCD = false;
    ab_Obliterate = false;
    ab_Obliterate_isCD = false;
    ab_Cataclysm = false;
    ab_Cataclysm_isCD = false;
    ab_Obliterate_Counter = 0;
    ab_HailStorm_debounce = false;
    ab_HailStorm_Counter = 0;
    ab_Obliterate_debounce= false;
    ab_FIRE2_timer = 0.f;
    ab_FIRE2_CDtimer = 0.f;
    ab_WATER2_timer = 0.f;
    ab_WATER2_CDtimer = 0.f;

}
AttackBase::~AttackBase()
{
    //delete[] BulletPos;
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


int AttackBase::GetAttackDamage()
{
    return m_AttackDamage;
}


void AttackBase::UpdateAttack(double dt, Vector3 pos, bool leftright)
{
    interdt = dt;
    m_EntityPos = pos;
    m_AttackDirection = leftright;
    Debouncers(dt);
    Ability_Run();

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
    //water 2 wave 
    if (ab_HailStorm_debounce)
    {
        ab_WATER2_timer += (float)dt;
        if (ab_WATER2_timer >= 1)
        {
            ab_HailStorm_debounce = false;
            ab_WATER2_timer = 0.f;
        }
    }
    //water 2 CD timer
    if (ab_HailStorm_isCD)
    {
        ab_WATER2_CDtimer += (float)dt;
        if (ab_WATER2_CDtimer >= 2.5f)
        {
            ab_HailStorm_isCD = false;
            ab_WATER2_CDtimer = 0.f;
        }
    }
    //earth 2 cooldowntimer
    if (ab_Cataclysm_isCD)
    {
        ab_EARTH2_CDtimer += (float)dt;
        if (ab_EARTH2_CDtimer >= 4)
        {
            ab_Cataclysm_isCD = false;
            ab_EARTH2_CDtimer = 0.f;
        }
    }
}

void::AttackBase::Attack_Ability(ELEMENT CurrElement, int elementLevel)
{
    m_CurrElement = CurrElement;
    m_ElementLevel = elementLevel;
    if (m_CurrElement == FIRE && !ab_Obliterate_isCD)
    {
        ab_Obliterate = true;
        m_RootedForAttack = true;
        
    }
    if (m_CurrElement == WATER && !ab_HailStorm_isCD)
    {
        ab_HailStorm = true;
    }
    if (m_CurrElement == EARTH && !ab_Cataclysm_isCD)
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
                    angletemp = -9.f;
                else if (i == 1)
                    angletemp = -6.f;
                else if (i == 2)
                    angletemp = -3.f;
                else if (i == 3)
                    angletemp = 0.f;
                else if (i == 4)
                    angletemp = 3.f;
                else if (i == 5)
                    angletemp = 6.f;
                else if (i == 6)
                    angletemp = 9.f;

                Projectile* temp;
                temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 1, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
                temp->projectileInit(m_AttackDirection, m_EntityPos + 2, 100.0f, m_AttackDamage, templifetime, m_CurrElement, false, angletemp);

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
    else if (ab_HailStorm && !ab_HailStorm_debounce)
    {

        if (ab_HailStorm_Counter >= m_ElementLevel + 5)
        {
            //resets
            ab_HailStorm = false;
            ab_HailStorm_Counter = 0;
            ab_HailStorm_debounce = false;

            //initiate cooldown
            ab_HailStorm_isCD = true;

        }
        else 
        {
            Vector3 BulletPos;
            int RainCloudSizeOffset = m_ElementLevel * 5 + 10;
            int NumOfBullets = m_ElementLevel * 2 + 5;
           
           
            for (int i = 0; i < NumOfBullets; i++)
            {
                BulletPos = Vector3(Math::RandFloatMinMax(m_EntityPos.x - RainCloudSizeOffset, m_EntityPos.x + RainCloudSizeOffset), Math::RandFloatMinMax(m_EntityPos.y + 15, m_EntityPos.y + 25), 0);
                Projectile* temp;
                temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1.5, 1.5, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
                temp->projectileInit(m_AttackDirection, BulletPos, 15.0f, m_AttackDamage, 2.f, m_CurrElement, false, -80.f);

                m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
                m_AbilityCount += 1;
                if (m_AbilityCount >= MAXprojectilecount)
                {
                    m_AbilityCount = 0;
                }
                ab_HailStorm_debounce = true;
            }                
            ab_HailStorm_Counter += 1;
        }
    }
    else if (ab_Cataclysm)
    {
        Projectile* temp;
        temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 1, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
        temp->projectileInit(m_AttackDirection, m_EntityPos, 40.0f, m_AttackDamage, 5, m_CurrElement, false, 50);

        // These Variables shouldn't change
        // Bullet Speed = 40.f
        // Theta = 50

        m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
        m_AbilityCount += 1;
        if (m_AbilityCount >= MAXprojectilecount)
        {
            m_AbilityCount = 0;
        }
        ab_Cataclysm_isCD = true;
    }
}

void AttackBase::Attack_Ranged(ELEMENT elementInput, int Level)
{
    m_CurrElement = elementInput;
    m_ElementLevel = Level;
    if (m_CanAttack)
    {
        Vector3 tempscale;
        tempscale = Vector3(2, 2, 2);

        Projectile* temp;
        if (m_CurrElement == EARTH)
        {
            Projectile* temp;
            temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 1, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
            temp->projectileInit(m_AttackDirection, m_EntityPos, 40.0f, m_AttackDamage, 5, m_CurrElement, false, 50);

            // These Variables shouldn't change
            // Bullet Speed = 40.f
            // Theta = 50

            m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
            m_AbilityCount += 1;
            if (m_AbilityCount >= MAXprojectilecount)
            {
                m_AbilityCount = 0;
            }
            m_CanAttack = false;
        }
        else if (m_CurrElement == WATER)
        {
            temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, ProjectilePH, "Image//Projectiles/water_projectile.tga"));
            temp->projectileInit(m_AttackDirection, m_EntityPos, 10.f, m_AttackDamage, 5, m_CurrElement, isEnemy, 0);
        }
        else if (m_CurrElement == FIRE)
        {
            float templifetime = m_ElementLevel *0.25f + 0.3f;
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
