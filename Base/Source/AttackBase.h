#ifndef ATTACKBASE_H
#define ATTACKBASE_H
#include "BaseElement.h"
#include "Vector3.h"
#include "Projectile.h"


enum ATTACK_TYPE
{
    NO_TYPE,//use this for non-interactable blocks
    MELEE,
    RANGED,
    ABILITY,
    TOTAL_TYPE,
};
class AttackBase
{
public:
    AttackBase(ELEMENT EntityElement, Vector3 EntityPos, int AttackDamage, float range);
    ~AttackBase();
    int GetAttackDamage();
    //generic update to be used in Entity classes
    void UpdateAttack(double dt);
    //generic init
    void Init();
    
    

protected:   

    bool m_AttackDirection;//true is right false is left
    int m_AttackDamage;
    float m_Range;
    Vector3 m_EntityPos;//Position of entity using the attack    
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