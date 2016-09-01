#include "FireBossBehaviour.h"

FireBossBehaviour::FireBossBehaviour()
{  
    trackTimer = 0.f;
    phaseTimer = 0.f;
    isNormalPhase = true;
    isRestPhase = false;
    isBeserkPhase = false;
	playmusic = true;
	music.playSE("Music//fire_boss.wav");
}
FireBossBehaviour::~FireBossBehaviour()
{


}

Vector3 FireBossBehaviour::GetTargetLocation()
{
    return m_TargetLocation;
}

void FireBossBehaviour::SetInternalDT(double dt)
{
    internalDT = dt;
}

FireBossBehaviour::FIRE_PHASE FireBossBehaviour::GetBossState()
{
    if (isNormalPhase)
        m_CurrPhase = NORMAL_PHASE;
    else if (isBeserkPhase)
        m_CurrPhase = BERSERK_PHASE;
    else if (isRestPhase)
        m_CurrPhase = REST_PHASE;

    return m_CurrPhase;
}

void FireBossBehaviour::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map)
{
    phaseTimer += (float)internalDT;
    trackTimer += (float)internalDT;
    if (isNormalPhase)
	{		
        if (trackTimer >= 0.25f)
        {
            m_TargetLocation = PlayerPos;
            trackTimer = 0.f;
        }
        if (phaseTimer >= 4.f)
        {
            trackTimer = 0.f;
            phaseTimer = 0.f;
            isNormalPhase = false;
            isBeserkPhase = true;
        }
    }
    else if (isBeserkPhase)
    {
        if (trackTimer >= 0.1f)
        {
            m_TargetLocation = PlayerPos;
            trackTimer = 0.f;
        }
        if (phaseTimer >= 4.5f)
        {
            trackTimer = 0.f;
            phaseTimer = 0.f;
            isBeserkPhase = false;
            isRestPhase = true;
        }
    }
    else if (isRestPhase)
    {
        m_TargetLocation = CurrPos;
        if (phaseTimer >= 3.f)
        {
            trackTimer = 0.f;
            phaseTimer = 0.f;
            isRestPhase = false;
            isNormalPhase = true;
        }
    }
        
    
}

