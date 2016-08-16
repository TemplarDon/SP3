#include "Enemy.h"

Enemy::Enemy(int x, int y)
{
	theDestination.x = x;
	theDestination.y = y;
	m_Behaviour = new Behaviour();
	//if (theStrategy != NULL)
	//{
	//	theStrategy->SetDestination(theDestination.x, theDestination.y);
	//}

	
}

Enemy::~Enemy()
{}

// Set the destination of this enemy 
int Enemy::GetDestination_x()
{
	return theDestination.x;
}
// Set the destination of this enemy 
int Enemy::GetDestination_y()
{
	return theDestination.y;
}

void Enemy::UpdateEnemy(Map* tilemap)
{
	//m_Behaviour->Update(d)
}

//void Enemy::ChangeStrategy(Strategy* theNewStrategy, bool bDelete)
//{
//	if (bDelete == true)
//	{
//		if (theStrategy != NULL)
//		{
//			delete theStrategy;
//			theStrategy = NULL;
//		}
//	}
//	theStrategy = theNewStrategy;
//	if (theStrategy != NULL)
//	{
//		theStrategy->SetDestination(theDestination.x, theDestination.y);
//		theStrategy->SetEnemyPosition(Position.x, Position.y);
//	}
//}