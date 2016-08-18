#include "Behaviour.h"


Behaviour::Behaviour()
{
	behaviour = ATTACK;
}

Behaviour::~Behaviour()
{

}

void Behaviour::Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack,  ENTITY_MOVE_STATE m_currEntityMoveState)
{

}
void Behaviour::setBehaviourStates(BehaviourStates behaviour)
{
	this->behaviour = behaviour;
}
Behaviour::BehaviourStates Behaviour::getBehaviourStates()
{
	return behaviour;
}

