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

	virtual void Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack,  ENTITY_MOVE_STATE m_currEntityMoveState);
	virtual void setBehaviourStates(BehaviourStates behaviour);
	virtual BehaviourStates getBehaviourStates();



protected:
	
	BehaviourStates behaviour;
	
};






#endif