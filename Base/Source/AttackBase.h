#ifndef ATTACKBASE_H
#define ATTACKBASE_H
#include "Projectile.h"


enum ATTACK_TYPE
{
	NO_ATTACK_TYPE,//use this for non-interactable blocks
    RANGED,
    ABILITY,
	SUCK,
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
    void Init(int AttackDamage, float range);
    //launch an attack
    void LaunchAttack();
	//void LaunchAttack(ELEMENT m_CurrElement);
    void SetisEnemy(bool);


	void SetAttackElement(ELEMENT m_CurrElement);
    

protected:   
    bool isEnemy;
    bool m_AttackDirection;//true is right false is left
    int m_AttackDamage;
    float m_Range;//bullet lifetime
    Vector3 m_EntityPos;//Position of entity using the attack   
    Vector3 m_Velocity;
    ATTACK_TYPE m_CurrAttackType = NO_ATTACK_TYPE;
    ELEMENT m_CurrElement = NO_ELEMENT;

    float m_AttackDebounce;
    bool m_CanAttack;

    double interdt;

    int MAXprojectilecount;
    int m_projectileCount;
    int m_meleeCount;
    int m_AbilityCount;
    Projectile *m_Projectiles = new Projectile[30];
    Projectile *m_AbilityProjectiles = new Projectile[50];

    Mesh* ProjectilePH;

    void SetAttackType();//always corresponds to element type

    //Attack calls
    void Attack_Ranged();

    void Attack_Ability();
	void Attack_Suck();

    


};

#endif