#include "Behaviour.h"


Behaviour::Behaviour()
{
	behaviour = NEUTRAL;
}

Behaviour::~Behaviour()
{

}

void Behaviour::Update(double dt, float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump, bool& Direction, ELEMENT m_CurrElement, AttackBase* attack, ENTITY_MOVE_STATE &m_currEntityMoveState, float detectionRange)
{

}

void Behaviour::BehaviourUpdate(Vector3 PlayerPos, Vector3 CurrPos, bool &Attack, GameObject_Map* Map)
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

Vector3 Behaviour::GetDestination()
{
	return Vector3(0, 0, 0);
}