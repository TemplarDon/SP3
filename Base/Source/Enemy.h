#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Behaviour.h"

class Enemy : public Entity
{
public:
	~Enemy();

	//Set enemy's x and y position
	Enemy(int x, int y);

	//Update enemy
	//void Update(double dt);

	// Set the destination of this enemy 
	void SetDestination(const int pos_x, const int pos_y);
	// Set the destination of this enemy 
	int GetDestination_x();
	// Set the destination of this enemy 
	int GetDestination_y();

	// ENEMY Update 
	void UpdateEnemy(Map* tilemap);
	// Strategy
	//void ChangeStrategy(Strategy* theNewStrategy, bool bDelete = true);


    virtual void Update(double dt)
    {}

private:
	Vector3 theDestination;
	//Strategy* theStrategy;

	 Behaviour* m_Behaviour;
};

#endif