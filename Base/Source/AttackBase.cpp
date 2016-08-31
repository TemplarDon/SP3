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
    ab_EARTH2_CDtimer = 0.f;


}
AttackBase::~AttackBase()
{
    //delete[] BulletPos;
    delete[] m_Projectiles;
    delete[] m_AbilityProjectiles;
    delete Projectile_Earth;
    delete Projectile_Fire;
    delete Projectile_Water;
    delete Projectile_Suck;

//	delete temp;

}
void AttackBase::Init(int AttackDamage, float range)
{
    m_AttackDamage = AttackDamage;
    m_Range = range;
    Projectile_Earth = MeshBuilder::GenerateQuad("Projectile_Earth", Color(1, 1, 1));
    Projectile_Fire = MeshBuilder::GenerateQuad("Projectile_Fire", Color(1, 1, 1));
    Projectile_Water = MeshBuilder::GenerateQuad("Projectile_Water", Color(1, 1, 1));
    Projectile_Suck = MeshBuilder::GenerateQuad("Projectile_Water", Color(1, 1, 1));
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
        if (m_AttackDebounce >= 10.f)
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
        if (ab_EARTH2_CDtimer >= 2.5)
        {
            ab_Cataclysm_isCD = false;
            ab_EARTH2_CDtimer = 0.f;
        }
    }
}

bool AttackBase::Attack_Ability(ELEMENT CurrElement, int elementLevel, bool Shootdown)
{
    m_Downwardshot = Shootdown;
    m_CurrElement = CurrElement;
    m_ElementLevel = elementLevel;
    if (m_CurrElement == FIRE && !ab_Obliterate_isCD)
    {
		music.playSE("Music//fire2_atk.wav");
        ab_Obliterate = true;
        m_RootedForAttack = true;
		return true;
        
    }
    if (m_CurrElement == WATER && !ab_HailStorm_isCD)
    {
		music.playSE("Music//water2_atk.wav");
        ab_HailStorm = true;
		return true;
    }
    if (m_CurrElement == EARTH && !ab_Cataclysm_isCD)
    {
		music.playSE("Music//earth2_atk.wav");
        ab_Cataclysm = true;
		return true;
    }
	return false;
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

                
                temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 1, 2), true, true, Projectile_Fire, "Image//Projectiles/fire_projectile.tga"));
                temp->projectileInit(m_AttackDirection, m_EntityPos + 2, 50.0f, m_AttackDamage, templifetime, FIRE_2, false, angletemp);
				temp->setIsHostileProjectile(this->isEnemy);

                m_AbilityProjectiles[m_AbilityCount].SetElement(FIRE_2);
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
                temp;
                temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1.5, 1.5, 2), true, true, Projectile_Water, "Image//Projectiles/water_projectile.tga"));
                temp->projectileInit(m_AttackDirection, BulletPos, 15.0f, m_AttackDamage, 3.5f, WATER_2, false, -80.f);
				temp->setIsHostileProjectile(this->isEnemy);

                m_AbilityProjectiles[m_AbilityCount].SetElement(WATER_2);
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
        float tempAngle;
        if (m_Downwardshot)
        {
            tempAngle = -80.f;
        }
        else
        {
            tempAngle = 0.f;
        }
        temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(4, 4, 2), true, true, Projectile_Earth, "Image//Projectiles/earth_projectile.tga"));
        temp->projectileInit(m_AttackDirection, m_EntityPos, 20.0f, m_AttackDamage, 5, EARTH_2, false, tempAngle, m_ElementLevel);
		temp->setIsHostileProjectile(this->isEnemy);
        m_AbilityProjectiles[m_AbilityCount].SetElement(EARTH_2);
        m_AbilityCount += 1;
        if (m_AbilityCount >= MAXprojectilecount)
        {
            m_AbilityCount = 0;
        }
        ab_Cataclysm_isCD = true;
		ab_Cataclysm = false;

    }
}
bool AttackBase::GetControlLock()
{
    return m_RootedForAttack;
}
bool AttackBase::Attack_Basic(ELEMENT elementInput, int Level)
{
    m_CurrElement = elementInput;
    m_ElementLevel = Level;
    if (m_CanAttack)
    {
        Vector3 tempscale;
        tempscale = Vector3(2, 2, 2);

        if (m_CurrElement == EARTH)
        {
			music.playSE("Music//earth_atk.wav");
            temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(3, 3, 1), true, true, Projectile_Earth, "Image//Projectiles/earth_projectile.tga"));
            temp->projectileInit(m_AttackDirection, m_EntityPos, 20.0f, m_AttackDamage, 30.f, m_CurrElement, false, 60.f);
			temp->setIsHostileProjectile(this->isEnemy);

            // These Variables shouldn't change
            // Bullet Speed = 20.0f
            // Theta = 60.f

            m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
            m_AbilityCount += 1;
            if (m_AbilityCount >= MAXprojectilecount)
            {
                m_AbilityCount = 0;
            }
            m_CanAttack = false;
			return true;
        }
        else if (m_CurrElement == WATER)
        {
			music.playSE("Music//water_atk.wav");
            temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, Projectile_Water, "Image//Projectiles/water_projectile.tga"));
            temp->projectileInit(m_AttackDirection, m_EntityPos, 25.f, m_AttackDamage, 5.f, m_CurrElement, isEnemy, 0);
			temp->setIsHostileProjectile(this->isEnemy);
            m_CanAttack = false;
			return true;
        }
        else if (m_CurrElement == FIRE)
        {
			music.playSE("Music//fire_atk.wav");
            float templifetime = m_ElementLevel *0.25f + 0.3f;
            for (int i = 0; i < 5; i++)
            {
                float angletemp;
                if (i == 0)
                    angletemp = -20.f;
                else if (i == 1)
                    angletemp = -10.f;
                else if (i == 2)
                    angletemp = -0.f;
                else if (i == 3)
                    angletemp = 10.f;
                else if (i == 4)
                    angletemp = 20.f;
               

                temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 1, 2), true, true, Projectile_Fire, "Image//Projectiles/fire_projectile.tga"));
                temp->projectileInit(m_AttackDirection, m_EntityPos + 2, 50.0f, m_AttackDamage, templifetime, m_CurrElement, false, angletemp);
				temp->setIsHostileProjectile(this->isEnemy);

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
			return true;
        }
    }
	return false;
}
void AttackBase::Attack_Suck(ELEMENT currElement,bool Direction)
{
	if (Direction == true)
	{
		music.playSE("Music//vacuum.wav");
		temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), Vector3(20, 1, 0), true, true, Projectile_Suck, "Image//blue Idle.tga"));
		temp->projectileInit(m_AttackDirection, Vector3(m_EntityPos.x + 10, m_EntityPos.y+5, m_EntityPos.z), 1, 0, 0.5f, currElement, isEnemy, 0);
		temp->setIsHostileProjectile(this->isEnemy);
	}
	else
	{
		music.playSE("Music//vacuum.wav");
		temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_ATTACK, m_Projectiles[m_projectileCount].GetPosition(), Vector3(20, 1, 0), true, true, Projectile_Suck, "Image//blue Idle.tga"));
		temp->projectileInit(m_AttackDirection, Vector3(m_EntityPos.x -10, m_EntityPos.y+5, m_EntityPos.z), 1, 0, 0.5f, currElement, isEnemy, 0);
		temp->setIsHostileProjectile(this->isEnemy);
	}
	//temp->projectileInit(m_AttackDirection, m_EntityPos, 1, 0, 0.5f, currElement, isEnemy, 0);
	m_Projectiles[m_projectileCount].SetElement(currElement);
	m_projectileCount += 1;
	if (m_projectileCount >= MAXprojectilecount)
	{
		m_projectileCount = 0;
	}
	m_CanAttack = false;
}
