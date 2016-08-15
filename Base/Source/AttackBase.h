#ifndef ATTACKBASE_H
#define ATTACKBASE_H
#include "BaseElement.h"
#include "Vector3.h"
#include "Projectile.h"


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
    void UpdateAttack(double dt, ELEMENT EntityCurrElement);
    //generic init
    void Init(ELEMENT EntityElement, Vector3 EntityPos, int AttackDamage = 0, float range = 0);
    Projectile *m_Projectiles[25];
    
    

protected:   

    bool m_AttackDirection;//true is right false is left
    int m_AttackDamage;
    float m_Range;
    Vector3 m_EntityPos;//Position of entity using the attack   
    Vector3 m_Velocity;
    ATTACK_TYPE m_CurrAttackType;
    ELEMENT m_CurrElement;

    void SetAttackType();//always corresponds to element type
    //specific updates
    void Update_Ranged();
    void Update_Melee();
    void Update_Ability();
    //specific inits
    void Init_Ranged();
    void Init_Melee();
    void Init_Ability();
    
    


};

#endif