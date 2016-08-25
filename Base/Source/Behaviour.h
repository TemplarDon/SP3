#ifndef BEHAVIOUR_H_
#define BEHAVIOUR_H_


#include "Vector3.h"
#include "AttackBase.h"

#include "Entity.h"
class Behaviour 
{
public:
	Behaviour();
	virtual ~Behaviour();

	enum BehaviourStates
	{
		NEUTRAL,
		ATTACK,
		EVADE,
		TOTALSTATES,
	};

	virtual void Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack, ENTITY_MOVE_STATE &m_currEntityMoveState, float detectionRange);
	virtual void BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map = NULL);

	virtual void setBehaviourStates(BehaviourStates behaviour);
	virtual BehaviourStates getBehaviourStates();

	virtual Vector3 GetDestination();

protected:
	
	BehaviourStates behaviour;

	Vector3 m_DestinationToReturn;

	bool m_DirectionSet;
	bool m_RunOnce;
	
};






#endif