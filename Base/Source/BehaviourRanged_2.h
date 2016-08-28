#ifndef _BEHAVIOUR_RANGED_H_
#define _BEHAVIOUR_RANGED_H_

#include "Behaviour.h"

class BehaviourRanged_2 : public Behaviour
{
public:
	BehaviourRanged_2(ELEMENT currElement);
	~BehaviourRanged_2();

	virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map = NULL);
	virtual Vector3 GetDestination();

	virtual void SetLastStand(bool status);
	virtual bool GetLastStand();

	virtual void SetLastStandTimer(float NewTime);
	virtual float GetLastStandTimer();

private:

	Vector3 m_DestinationToReturn;

	bool m_DirectionSet;
	bool m_RunOnce;

	float m_AttackDistance;
	float m_EvadeDistance;

	float m_LastStandTimer;
	bool m_LastStandStatus;
};
#endif // !2_BEHAVIOUR_RANGED_H
