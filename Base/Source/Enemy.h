#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Behaviour.h"

class Enemy : public Entity
{
public:
	~Enemy();

	//Set enemy's x and y position
	Enemy(int x, int y, Behaviour::EnemyType enemyType, float estimatedDistance, AttackBase* Attack);

	//Update enemy
	//void Update(double dt);

	virtual void setEnemyPosition(Vector3 enemyPosition);
	virtual Vector3 getEnemyPosition();

	 
	virtual void UpdateEnemy(double dt, Vector3 playerPosition);

	virtual void setBehaviour(Behaviour* behaviour);
	virtual Behaviour* getBehaviour(Behaviour* behaviour);

	virtual void setAttack(AttackBase* attack);
	virtual AttackBase* getAttack();

	 void setMoveLeft(bool moveLeft);
	 bool getMoveLeft();

	 void setMoveRight(bool moveRight);
	 bool getMoveRight();
     void setJump(bool jump);
	 bool getJump();
private:
	Vector3  enemyPosition;
	//Strategy* theStrategy;
	AttackBase *attack;
	 Behaviour* m_Behaviour;
	 bool moveLeft;
	 bool moveRight;
	 bool jump;
};

#endif