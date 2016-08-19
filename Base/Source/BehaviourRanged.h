#ifndef BEHAVIOURRANGED_H_
#define BEHAVIOURRANGED_H_


#include "Vector3.h"
#include "Behaviour.h"
class BehaviourRanged :public Behaviour
{
	
public:
	
	BehaviourRanged();
	virtual ~BehaviourRanged();

	//using Behaviour::Update;
	virtual void Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack, ENTITY_MOVE_STATE &m_currEntityMoveState, float detectionRange);


private:
	int random;
};



#endif