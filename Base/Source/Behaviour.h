#ifndef BEHAVIOUR_H_
#define BEHAVIOUR_H_


#include "Vector3.h"
#include "AttackBase.h"

class Behaviour
{
	enum EnemyType
	{
		NIL,
		MELEE,
		RANGED,
	};
	enum BehaviourStates
	{
		NEUTRAL,
		ATTACK,
		EVADE,
		TOTALSTATES,
	};

public:
	
	virtual float calculateRelativeDistance(Vector3 playerPosition, Vector3 enemyPosition);
	virtual void Update(double dt, Vector3 playerPosition, Vector3 enemyPosition);
		

	virtual  void setEnemyType(EnemyType enemyType);
	virtual EnemyType getEnemyType();

	virtual  void setEstimatedDistance(float estimatedDistance);
	virtual float getEstimatedDistance();
	 
	virtual void setAttack(AttackBase *attack);
	virtual AttackBase getAttack();

	virtual void setDirection(Vector3 playerPosition, Vector3 enemyPosition);
	virtual bool getDirection();

	virtual void setBehaviour(BehaviourStates behaviour);
	virtual bool getBehaviour();

protected:
	Behaviour();
	Behaviour(EnemyType enemyType, float estimatedDistance, AttackBase *attack);
	~Behaviour();
	EnemyType enemyType;
	BehaviourStates behaviour;
	float estimatedDistance;
	AttackBase *attack;
	bool Direction;
};






#endif