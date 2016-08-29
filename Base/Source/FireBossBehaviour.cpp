#include "FireBossBehaviour.h"

FireBossBehaviour::FireBossBehaviour()
{
    AttackCounter = 0;
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

void FireBossBehaviour::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map )
{
    float DistanceToPlayer = 0;
    DistanceToPlayer = (PlayerPos - CurrPos).Length();

    // Find if player is left or right of curr enemy
    bool PlayerRight = false;
    bool PlayerLeft = false;
    if (PlayerPos.x > CurrPos.x)
    {
        PlayerRight = true;
    }
    else
    {
        PlayerLeft = true;
    }

    if (DistanceToPlayer < 50 && AttackCounter < 4)
    {
        m_DestinationToReturn = CurrPos;
        m_CurrPhase = SHOOTING_PHASE;
        behaviour = ATTACK;
        Attack = true;
        AttackCounter += 1;
    }
    else if (DistanceToPlayer <50 && AttackCounter == 4)
    {
        m_DestinationToReturn = CurrPos;
        m_CurrPhase = BERSERK_PHASE;
        behaviour = ATTACK;
        Attack = true;
        AttackCounter = 0;
    }
    else if (DistanceToPlayer > 50)
    {
        m_CurrPhase = NORMAL_PHASE;
        m_DestinationToReturn = PlayerPos;
    }
}