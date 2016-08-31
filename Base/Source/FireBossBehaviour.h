#ifndef FIREBOSSBEHAVIOUR_H
#define FIREBOSSBEHAVIOUR_H
#include "Behaviour.h"
#include "Sound.h"

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
    
    virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map = NULL);
    virtual Vector3 GetTargetLocation();
    virtual void SetInternalDT(double dt);

    FIRE_PHASE GetBossState();
private:
	Sound music;
	bool playmusic;
    FIRE_PHASE m_CurrPhase;
    float DistanceToPlayer;
    Vector3 m_TargetLocation;

    double internalDT;

    float phaseTimer;
    float trackTimer;
    //normal phase stuff
    bool isNormalPhase;
    //rest phase
    bool isRestPhase;
    //berserkPhase
    bool isBeserkPhase;



};

#endif