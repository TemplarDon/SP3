#ifndef ATTACKBASE_H
#define ATTACKBASE_H
#include "BaseElement.h"
#include "Vector3.h"
#include "Projectile.h"
#include "GameObjectManager.h"
#include "MeshBuilder.h"



enum ATTACK_TYPE
{
	NO_ATTACK_TYPE,//use this for non-interactable blocks
    MELEE,
    RANGED,
    ABILITY,
    TOTAL_ATTACK_TYPE,
};
class AttackBase
{
public:
    AttackBase();
    ~AttackBase();
    int GetAttackDamage();
    //generic update to be used in Entity classes
    void UpdateAttack(double dt, ELEMENT EntityCurrElement, Vector3 pos, bool leftright);
    //generic init
    void Init(int AttackDamage = 0, float range = 0);
    //launch an attack
    void LaunchAttack();
    
    
    

protected:   

    bool m_AttackDirection;//true is right false is left
    int m_AttackDamage;
    float m_Range;//bullet lifetime
    Vector3 m_EntityPos;//Position of entity using the attack   
    Vector3 m_Velocity;
    ATTACK_TYPE m_CurrAttackType;
    ELEMENT m_CurrElement;
    Projectile *m_Projectiles[MAXprojectilecount];
    Projectile *m_MeleeStrike[MAXprojectilecount];

    int MAXprojectilecount;
    int m_projectileCount;
    int m_meleeCount;
    int m_AbilityCount;

    Mesh* ProjectilePH;

    void SetAttackType();//always corresponds to element type
    //specific updates
    void Update_Ranged(double dt);
    void Update_Melee(double dt);
    void Update_Ability(double dt);
    //Attack calls
    void Attack_Ranged();
    void Attack_Melee();
    void Attack_Ability();

    


};

#endif