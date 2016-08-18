#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "BehaviourRanged.h"
#include "BehaviourMelee.h"
class Enemy : public Entity
{


public:
	enum EnemyType
	{
		NIL,
		MELEE,
		RANGED,
	};
	Enemy();
	~Enemy();

	//Set enemy's x and y position
	//Enemy(float x, float y, Behaviour::EnemyType enemyType, float estimatedDistance, AttackBase* Attack);

	//Update enemy
	//void Update(double dt);

	//virtual void setEnemyPosition(Vector3 enemyPosition);
	//virtual Vector3 getEnemyPosition();



	virtual void EnemyInit(Vector3 playerPosition, EnemyType enemyType, float estimatedDistance, ELEMENT m_CurrElement, int Damage);


	virtual void Update(double dt, Vector3 playerPosition, GameObject_Map * map, Camera camera);
	virtual void UpdateTileMapCollision(GameObject_Map* Map)
	{
	}
	virtual void setBehaviour(Behaviour* behaviour);
	virtual Behaviour* getBehaviour(Behaviour* behaviour);

	virtual void setAttack(AttackBase* attack);
	virtual AttackBase* getAttack();



	virtual  void setEnemyType(EnemyType enemyType);
	virtual EnemyType getEnemyType();

	virtual void setDistancePlayerToEnemy(Vector3 playerPosition, Vector3 enemyPosition);
	virtual float getDistancePlayerToEnemy();

	virtual void setEstimatedDistance(float estimatedDistance);
	virtual float getEstimatedDistance();

	virtual void setDirectionBasedOnDistance(Vector3 playerPosition, Vector3 enemyPosition);

private:

	//Strategy* theStrategy;
	AttackBase* attack;
	Behaviour* m_Behaviour;
	EnemyType enemyType;
	float distancePlayerToEnemy;
	float estimatedDistance;

	//BehaviourRanged* behaviourRanged;
	// BehaviourMelee* behaviourMelee;
	/* bool moveLeft;
	bool moveRight;
	bool jump;*/
};

#endif