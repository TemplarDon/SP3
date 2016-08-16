#include "AttackBase.h"
AttackBase::AttackBase()
{
    m_projectileCount = 0;
    m_meleeCount = 0;
    m_AbilityCount = 0;
}
void AttackBase::Init(int AttackDamage, float range)
{
    m_AttackDamage = AttackDamage;
    m_Range = range;
 
}

void AttackBase::SetAttackType()
{
    if (m_CurrElement == NO_ELEMENT)
        m_CurrAttackType == NO_TYPE;
    else if (m_CurrElement == FIRE || m_CurrElement == WATER)
        m_CurrAttackType == RANGED;
    else if (m_CurrElement == EARTH)
        m_CurrAttackType == MELEE;
    else
        m_CurrAttackType == ABILITY;
}

int AttackBase::GetAttackDamage()
{
    return m_AttackDamage;
}

void AttackBase::UpdateAttack(double dt, ELEMENT EntityCurrElement, Vector3 pos, bool leftright)
{
    m_CurrElement = EntityCurrElement;
    SetAttackType();
    m_EntityPos = pos;
    m_AttackDirection = leftright;

   
    
}

void AttackBase::Attack_Ability()
{
    if (m_CurrElement == FIRE_2)
    {
        //do fire2 stuff
        
    }
    else if (m_CurrElement == WATER_2)
    {
        //do water 2 stuff
    }
    else if (m_CurrElement == EARTH_2)
    {
        //do earth 2 stuff
    }
    else if (m_CurrElement == SAND)
    {
        //do sand stuff
    }
    else if (m_CurrElement == STEAM)
    {
        //do steam stuff
    }
    else if (m_CurrElement == WOOD)
    {
        //do wood stuff
    }
}

void AttackBase::Attack_Melee()
{
    //m_MeleeStrike[m_meleeCount]->projectileInit(m_AttackDirection, m_EntityPos, );

    
}
void AttackBase::Attack_Ranged()
{
    //do ranged stuff
}

void AttackBase::Update_Ranged(double dt)
{
    for (int i = 0; i < m_projectileCount; i++)
    {
        if (m_Projectiles[i]->GetActive() == true)
        {
            m_Projectiles[i]->projectileUpdate(dt);
            m_Projectiles[i]->SetElement(m_CurrElement);
        }
    }
}
void AttackBase::Update_Melee(double dt)
{
    for (int i = 0; i < m_projectileCount; i++)
    {
        if (m_MeleeStrike[i]->GetActive() == true)
        {
            m_MeleeStrike[i]->projectileUpdate(dt);
            m_MeleeStrike[i]->SetElement(m_CurrElement);
        }
    }
}
void AttackBase::Update_Ability(double dt)
{

}