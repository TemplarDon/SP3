#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "BehaviourRanged.h"
#include "BehaviourMelee.h"
#include "BehaviourRanged_2.h"
#include "EarthBossBehaviour.h"
#include "BehaviourWaterBoss.h"
#include "FireBossBehaviour.h"

class Enemy : public Entity
{


public:
	enum EnemyType
	{
		NIL,
		MELEE,
		RANGED,
		BOSS,
		WATERBOSS,
	};
	Enemy();
	~Enemy();

	//Set enemy's x and y position
	//Enemy(float x, float y, Behaviour::EnemyType enemyType, float estimatedDistance, AttackBase* Attack);

	//Update enemy
	//void Update(double dt);

	//virtual void setEnemyPosition(Vector3 enemyPosition);
	//virtual Vector3 getEnemyPosition();


	virtual void EnemyInit( float estimatedDistance, ELEMENT m_CurrElement, int Damage, float detectionRange);

	virtual void Update(double dt, Vector3 playerPosition, GameObject_Map * map, Camera camera);

	virtual void setBehaviour(Behaviour* behaviour);
	virtual Behaviour* getBehaviour();

	virtual void setAttack(AttackBase* attack);
	virtual AttackBase* getAttack();

	virtual  void setEnemyType(EnemyType enemyType);
	virtual EnemyType getEnemyType();

	virtual void setDistancePlayerToEnemy(Vector3 playerPosition, Vector3 enemyPosition);

	virtual float getDistancePlayerToEnemy();

	virtual void setEstimatedDistance(float estimatedDistance);
	virtual float getEstimatedDistance();

	virtual void setDirectionBasedOnDistance(Vector3 playerPosition, Vector3 enemyPosition);

	virtual void setDetectionRange(float detectionRange);
	virtual float getDetectionRange();

	
	virtual void CollisionResponse(GameObject* OtherGo, GameObject_Map* Map);
	virtual void Death();

private:

	float musictimer;
    int fireCount;
	//Strategy* theStrategy;
	Behaviour* m_Behaviour;
	EnemyType enemyType;
	float distancePlayerToEnemy;
	float estimatedDistance;
	float detectionRange;

	bool moveTowardsPlayer;
	float timer;
	bool timerBool;

	//BehaviourRanged* behaviourRanged;
	// BehaviourMelee* behaviourMelee;
	/* bool moveLeft;
	bool moveRight;
	bool jump;*/


	Vector3 m_Destination;
};

#endif