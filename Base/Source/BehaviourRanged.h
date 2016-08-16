#ifndef BEHAVIOURRANGED_H_
#define BEHAVIOURRANGED_H_


#include "Behaviour.h"

class BehaviourRanged :public Behaviour
{

public:
	BehaviourRanged();
	~BehaviourRanged();


	void BehaviourRangedUpdate(float distancePlayerToEnemy,Vector3 playerPosition,Vector3 enemyPosition);
private:
	float distancePlayerToEnemy;
	Behaviour::BehaviourStates behaviour;


};



#endif