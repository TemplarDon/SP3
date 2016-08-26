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
        BERSERK_PHASE,
        KITE_PHASE,
    };
    
    virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map = NULL);
    virtual Vector3 GetTargetLocation();

private:

};

#endif