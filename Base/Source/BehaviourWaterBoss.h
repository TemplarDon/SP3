#ifndef _BEHAVIOURWATERBOSS_H_
#define _BEHAVIOURWATERBOSS_H_

#include "Behaviour.h"
#include "Sound.h"

class BehaviourWaterBoss : public Behaviour
{
	
public:
	enum WaterBossState
	{
		PHASE1,
		PHASE2,
		PHASE3,
	};
	BehaviourWaterBoss();
	~BehaviourWaterBoss();

	virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map = NULL);
	virtual Vector3 GetDestination();

	virtual WaterBossState getBossState();
	virtual void setBossState(WaterBossState bossState);
private:
	Sound music;
	bool playmusic;
	Vector3 m_DestinationToReturn;

	WaterBossState bossState;
	bool m_DirectionSet;
	bool m_RunOnce;
};

#endif
