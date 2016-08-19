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
        m_CanAttack = false;
    }
}
void AttackBase::Attack_Ability()
{
    if (m_CurrElement == FIRE_2)
    {
        Projectile* temp;
        temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_EARTHMELEE_PROJECTILE, m_AbilityProjectiles[m_AbilityCount].GetPosition(), Vector3(1, 5, 2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
        temp->projectileInit(m_AttackDirection, m_EntityPos, 50.0f, m_AttackDamage, 0.1f, m_CurrElement, false);



        m_AbilityProjectiles[m_AbilityCount].SetElement(m_CurrElement);
        m_AbilityCount += 1;
        if (m_AbilityCount >= MAXprojectilecount)
        {
            m_AbilityCount = 0;
        }
        
    }
    else if (m_CurrElement == WATER_2)
    {
        if (m_AttackDirection && !m_Dashleft)//right
        {
            m_Dashright = true;
            std::cout << "set right" << std::endl;
        }
        else if (!m_AttackDirection && !m_Dashright)//left
        {
            m_Dashleft = true;
            std::cout << "set left" << std::endl;

        }
    
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
    }
    else if (m_CurrElement == WOOD)
    {
        //do wood stuff
    }
}

void AttackBase::Attack_Melee()
{
    Projectile* temp;
    temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_EARTHMELEE_PROJECTILE, m_MeleeStrike[m_meleeCount].GetPosition(), Vector3(1,5,2), true, true, ProjectilePH, "Image//Projectiles/earth_projectile.tga"));
	temp->projectileInit(m_AttackDirection, m_EntityPos, 50.0f, m_AttackDamage, 0.2f, m_CurrElement, isEnemy);
    //temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_EARTHMELEE_PROJECTILE, m_MeleeStrike[m_meleeCount].GetPosition(), Vector3(1,5,2), true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
    //temp->projectileInit(m_AttackDirection, m_EntityPos, 50.0f, m_AttackDamage, 0.1f,isEnemy);

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
    if (m_projectileCount <= 5)
        tempscale = Vector3(2, 2, 2);
    else
        tempscale = Vector3(1, 1, 1);
    //GameObjectManager::SpawnProjectileObject(PROJECTILE, GO_EARTHMELEE_PROJECTILE, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, 2, 5,m_AttackDirection , 50.0f ,ProjectilePH, "Image//Tiles/projectilePH.tga");

    Projectile* temp;
    temp = dynamic_cast<Projectile*>(GameObjectManager::SpawnGameObject(PROJECTILE, GO_EARTHMELEE_PROJECTILE, m_Projectiles[m_projectileCount].GetPosition(), tempscale, true, true, ProjectilePH, "Image//Tiles/projectilePH.tga"));
    temp->projectileInit(m_AttackDirection,m_EntityPos,50.0f,m_AttackDamage,1,m_CurrElement, isEnemy);
    //temp->projectileInit(m_AttackDirection,m_EntityPos,50.0f,m_AttackDamage,10.0f, isEnemy);

    m_Projectiles[m_projectileCount].SetElement(m_CurrElement);
    m_projectileCount += 1;

    if (m_projectileCount >= MAXprojectilecount)
    {
        m_projectileCount = 0;
    }
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