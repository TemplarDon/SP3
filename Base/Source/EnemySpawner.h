#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_


#include "Enemy.h"

class EnemySpawner : public ElementalObject
{


public:
	EnemySpawner();
	~EnemySpawner();



	virtual void setEnemySpawnerVector(ELEMENT m_CurrElement, int howMany);
	virtual std::vector<Enemy*> getEnemySpawnerVector();
	
	virtual void Update(double dt);


private:
	std::vector <Enemy*> enemyList;
	double m_timer;
};







#endif