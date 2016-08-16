#ifndef BEHAVIOUR_H_
#define BEHAVIOUR_H_


#include "Vector3.h"
#include "AttackBase.h"
#include "BehaviourRanged.h"
class Behaviour
{
	

public:
	enum EnemyType
	{
		NIL,
		MELEE,
		RANGED,
	};

	virtual float calculateRelativeDistance(Vector3 playerPosition, Vector3 enemyPosition);
	virtual void Update(double dt, Vector3 playerPosition, Vector3 &enemyPosition, bool &moveLeft, bool &moveRight, bool &jump);
		

	virtual  void setEnemyType(EnemyType enemyType);
	virtual EnemyType getEnemyType();

	virtual  void setEstimatedDistance(float estimatedDistance);
	virtual float getEstimatedDistance();
	 
	virtual void setAttack(AttackBase *attack);
	virtual AttackBase getAttack();

	virtual void setDirection(Vector3 playerPosition, Vector3 enemyPosition);
	virtual bool getDirection();

	//virtual void setBehaviour(BehaviourStates behaviour);
	//virtual BehaviourStates getBehaviour();
	
	virtual void setBehaviourRanged(BehaviourRanged* behaviourRanged);
	virtual BehaviourRanged* getBehaviourRanged();
	Behaviour();
	Behaviour(EnemyType enemyType, float estimatedDistance, AttackBase *attack);
	~Behaviour();
	//virtual void setEnemyPosition(Vector3 enemyPosition);
	//virtual Vector3 setEnemyPosition();

protected:
	
	EnemyType enemyType;
	//BehaviourStates behaviour;
	float estimatedDistance;
	AttackBase *attack;
	bool Direction;
	//Vector3 enemyPosition;
	BehaviourRanged* behaviourRanged;
	float m_Speed;
};






#endif