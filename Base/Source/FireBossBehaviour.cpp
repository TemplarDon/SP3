#include "FireBossBehaviour.h"

FireBossBehaviour::FireBossBehaviour()
{  
    phaseTimer = 0.f;
    isNormalPhase = true;
    isRestPhase = false;
    isBeserkPhase = false;
}
FireBossBehaviour::~FireBossBehaviour()
{

}

Vector3 FireBossBehaviour::GetTargetLocation()
{
    return m_TargetLocation;
}

FireBossBehaviour::FIRE_PHASE FireBossBehaviour::GetBossState()
{
    return m_CurrPhase;
}

void FireBossBehaviour::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map, double dt)
{
    if (isNormalPhase)
    {

    }
    
}