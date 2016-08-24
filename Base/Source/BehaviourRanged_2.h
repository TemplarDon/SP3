#ifndef _BEHAVIOUR_RANGED_H_
#define _BEHAVIOUR_RANGED_H_

#include "Behaviour.h"

class BehaviourRanged_2 : public Behaviour
{
public:
	BehaviourRanged_2();
	~BehaviourRanged_2();

	virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack);
	virtual Vector3 GetDestination();

private:

	Vector3 m_DestinationToReturn;
};
#endif // !2_BEHAVIOUR_RANGED_H
