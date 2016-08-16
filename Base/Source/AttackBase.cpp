#include "AttackBase.h"
#include "GameObjectManager.h"
AttackBase::AttackBase()
{
    MAXprojectilecount = 50;
    m_projectileCount = 0;
    m_meleeCount = 0;
    m_AbilityCount = 0;
    m_AttackDirection = true;
}
void AttackBase::Init(int AttackDamage, float range)
{
    m_AttackDamage = AttackDamage;
    m_Range = range;

    ProjectilePH = MeshBuilder::GenerateQuad("ProjectilePlaceHolder", Color(1, 1, 1));
}

void AttackBase::SetAttackType()
{
    if (m_CurrElement == NO_ELEMENT)
        m_CurrAttackType == NO_ATTACK_TYPE;
    else if (m_CurrElement == FIRE || m_CurrElement == WATER)
        m_CurrAttackType = RANGED;
    else if (m_CurrElement == EARTH)
        m_CurrAttackType = MELEE;
    else
        m_CurrAttackType = ABILITY;
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

    Update_Ranged(dt);
    Update_Melee(dt);
    Update_Ability(dt);
}
void AttackBase::LaunchAttack()
{
    SetAttackType();
    if (m_CurrAttackType == MELEE)
        Attack_Melee();
    else if (m_CurrAttackType == RANGED)
        Attack_Ranged();
    else if (m_CurrAttackType == ABILITY)
        Attack_Ability();
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
    m_MeleeStrike[m_meleeCount].projectileInit(m_AttackDirection, m_EntityPos,5.0f, m_AttackDamage, 0.5f);
    GameObjectManager::SpawnProjectileObject(PROJECTILE, GO_EARTHMELEE_PROJECTILE, m_MeleeStrike[m_meleeCount].GetPosition(),Vector3(1,5,1),true,true,0.1,5,m_AttackDirection,50.0f,ProjectilePH, "Image/Tiles/ProjectilePlaceHolder.tga");
    m_MeleeStrike[m_meleeCount].SetElement(m_CurrElement);
    m_meleeCount += 1;
    if (m_meleeCount >= MAXprojectilecount)
    {
        m_meleeCount = 0;
    }
}
void AttackBase::Attack_Ranged()
{
    Vector3 tempscale;
    m_Projectiles[m_projectileCount].projectileInit(m_AttackDirection, m_EntityPos, 5.0f, m_AttackDamage, 2.0f);
    if (m_projectileCount <= 5)
        tempscale = Vector3(2, 2, 2);
    else
        tempscale = Vector3(1, 1, 1);
    GameObjectManager::SpawnProjectileObject(PROJECTILE, GO_EARTHMELEE_PROJECTILE, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, 2, 5,m_AttackDirection , 50.0f ,ProjectilePH, "Image//Tiles/projectilePH.tga");
    m_Projectiles[m_projectileCount].SetElement(m_CurrElement);
    m_projectileCount += 1;

    if (m_projectileCount >= MAXprojectilecount)
    {
        m_projectileCount = 0;
    }
}

void AttackBase::Update_Ranged(double dt)
{
    for (int i = 0; i < m_projectileCount; i++)
    {
        if (m_Projectiles[i].GetActive() == true)
        {
            m_Projectiles[i].projectileUpdate(dt);
            m_Projectiles[i].SetElement(m_CurrElement);
        }
    }
}
void AttackBase::Update_Melee(double dt)
{
    for (int i = 0; i < m_projectileCount; i++)
    {
        if (m_MeleeStrike[i].GetActive() == true)
        {
            m_MeleeStrike[i].projectileUpdate(dt);
            m_MeleeStrike[i].SetElement(m_CurrElement);
        }
    }
}
void AttackBase::Update_Ability(double dt)
{

}