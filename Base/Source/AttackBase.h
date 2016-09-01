#ifndef ATTACKBASE_H
#define ATTACKBASE_H
#include "Projectile.h"
#include "Sound.h"

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
	void SetAttackDamage(int Damage);
    int GetAttackDamage();
    //generic update to be used in Entity classes
    void UpdateAttack(double dt, Vector3 pos, bool leftright);
    //generic init
    void Init(int AttackDamage, float range);
	//void LaunchAttack(ELEMENT m_CurrElement);
    void SetisEnemy(bool);
    bool GetControlLock();
    bool Attack_Basic(ELEMENT CurrElement, int elementLevel);
    bool Attack_Ability(ELEMENT CurrElement, int elementLevel, bool ShootDown = false);
	void Attack_Suck(ELEMENT  CurrElement, bool Direction);

	void setpleaseplaysound(bool yes);
	bool getpleaseplaysound();
protected:   
	Sound music;

	bool pleaseplaysound;
    bool isEnemy;
    bool m_AttackDirection;//true is right false is left
    int m_AttackDamage;
    int m_ElementLevel;
    float m_Range;//bullet lifetime
    Vector3 m_EntityPos;//Position of entity using the attack   
    Vector3 m_Velocity;
    ATTACK_TYPE m_CurrAttackType;
    ELEMENT m_CurrElement;

    float m_AttackDebounce;
    bool m_CanAttack;
    bool m_RootedForAttack;

    double interdt;

    int MAXprojectilecount;
    int m_projectileCount;
    int m_meleeCount;
    int m_AbilityCount;
    Projectile *m_Projectiles = new Projectile[30];
    Projectile *m_AbilityProjectiles = new Projectile[50];

    Mesh* Projectile_Fire;
    Mesh* Projectile_Water;
    Mesh* Projectile_Earth;
    Mesh* Projectile_Suck;

    //void SetAttackType();//always corresponds to element type

    //Attack calls
   
    void Ability_Run();

    void Debouncers(double dt);

    //Ability stuff
    bool ab_HailStorm;
    bool ab_HailStorm_isCD;
    bool ab_Obliterate;
    bool ab_Obliterate_isCD;
    bool ab_Cataclysm;
    bool ab_Cataclysm_isCD;

    bool ab_HailStorm_debounce;
    bool ab_Obliterate_debounce;

    int ab_Obliterate_Counter;
    int ab_HailStorm_Counter;
    bool m_Downwardshot;
    //Vector3 *BulletPos = new Vector3[];
    float ab_FIRE2_timer;
    float ab_FIRE2_CDtimer;
    float ab_EARTH2_CDtimer;
    float ab_WATER2_timer;
    float ab_WATER2_CDtimer;

	Projectile* temp;
};

#endif