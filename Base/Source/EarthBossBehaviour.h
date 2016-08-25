#ifndef _EARTH_BOSS_BEHAVIOUR_H
#define _EARTH_BOSS_BEHAVIOUR_H

#include "Behaviour.h"

class EarthBehaviour : public Behaviour
{
public:
	EarthBehaviour();
	~EarthBehaviour();

	enum EARTH_PHASE
	{
		NORMAL_ATTACK_PHASE,
		ABILITY_ATTACK_PHASE,
		RETREAT_PHASE,
	};

	virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map = NULL);
	virtual Vector3 GetDestination();

	EARTH_PHASE GetBossState();

private:

	Vector3 m_DestinationToReturn;
	EARTH_PHASE m_CurrPhase;

	bool m_DirectionSet;
	bool m_RunOnce;
};

#endif // !_EARTH_BOSS_BEAHVIOUR_H
