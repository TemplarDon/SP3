#include "AttackBase.h"
AttackBase::AttackBase(ELEMENT EntityElement, Vector3 EntityPos, int AttackDamage, float range)
{
    m_CurrElement = EntityElement;
    m_AttackDamage = AttackDamage;
    m_EntityPos = EntityPos;
    SetAttackType();
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

void AttackBase::UpdateAttack(double dt)
{
    if (m_CurrAttackType == MELEE)
        Update_Melee();
    else if (m_CurrAttackType == RANGED)
        Update_Ranged();
    else if (m_CurrAttackType == ABILITY)
        Update_Ability();
}

