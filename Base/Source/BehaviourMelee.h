#ifndef BEHAVIOURANGED_H_
#define BEHAVIOURANGED_H_
#include"Behaviour.h"

class BehaviourMelee : public Behaviour
{
public:

	BehaviourMelee();
	virtual ~BehaviourMelee();

	virtual void Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, int ElementLevel,AttackBase* attack, ENTITY_MOVE_STATE &m_currEntityMoveState, float detectionRange);

private:

};


#endif
