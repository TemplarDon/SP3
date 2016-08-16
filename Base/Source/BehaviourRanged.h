#ifndef BEHAVIOURRANGED_H_
#define BEHAVIOURRANGED_H_


#include "Vector3.h"
#include "AttackBase.h"
class BehaviourRanged 
{
	
public:
	enum BehaviourStates
	{
		NEUTRAL,
		ATTACK,
		EVADE,
		TOTALSTATES,
	};
	BehaviourRanged();
	~BehaviourRanged();

	
	void BehaviourRangedUpdate(float distancePlayerToEnemy, float estimatedDistance, Vector3 &enemyPosition, double dt, AttackBase *attack, bool &moveLeft, bool &moveRight,bool &jump, bool Direction);
	 void Update(double dt, Vector3 playerPosition, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump);

	 void setBehaviour(BehaviourStates behaviour);
	 BehaviourStates getBehaviour();
private:
	int random;
	BehaviourStates behaviour;

};



#endif