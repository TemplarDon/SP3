#include "AttackBase.h"
AttackBase::AttackBase(ELEMENT EntityElement, Vector3 EntityPos, int AttackDamage, float range)
{
    m_CurrElement = EntityElement;
    m_AttackDamage = AttackDamage;
    m_EntityPos = EntityPos;
    SetAttackType();
    Init();
}
void AttackBase::Init()
{
    if (m_CurrAttackType == MELEE)
        Init_Melee();
    else if (m_CurrAttackType == RANGED)
        Init_Ranged();
    else if (m_CurrAttackType == ABILITY)
        Init_Ability();
}

void AttackBase::Init_Melee()
{
    //init a fixed range
}
void AttackBase::Init_Ranged()
{
    //init array of projectiles
}
void AttackBase::Init_Ability()
{

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

void AttackBase::UpdateAttack(double dt, ELEMENT EntityCurrElement)
{
    m_CurrElement = EntityCurrElement;
    SetAttackType();
    if (m_CurrAttackType == MELEE)
        Update_Melee();
    else if (m_CurrAttackType == RANGED)
        Update_Ranged();
    else if (m_CurrAttackType == ABILITY)
        Update_Ability();
}

void AttackBase::Update_Ability()
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

void AttackBase::Update_Melee()
{
    //do melee stuff
}
void AttackBase::Update_Ranged()
{
    //do ranged stuff
}
