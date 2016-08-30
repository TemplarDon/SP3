#ifndef FIREBOSSBEHAVIOUR_H
#define FIREBOSSBEHAVIOUR_H
#include "Behaviour.h"
class FireBossBehaviour : public Behaviour
{
public:
    FireBossBehaviour();
    ~FireBossBehaviour();

    enum FIRE_PHASE
    {
        NORMAL_PHASE,
        REST_PHASE,
        BERSERK_PHASE,
    };
    
    virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map = NULL, double dt);
    virtual Vector3 GetTargetLocation();

    FIRE_PHASE GetBossState();
private:
    FIRE_PHASE m_CurrPhase;
    float DistanceToPlayer;
    Vector3 m_TargetLocation;

    float phaseTimer;
    //normal phase stuff
    bool isNormalPhase;
    //rest phase
    bool isRestPhase;
    //berserkPhase
    bool isBeserkPhase;


};

#endif