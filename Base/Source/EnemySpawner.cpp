#include "EnemySpawner.h"
#include "GameObjectManager.h"




EnemySpawner::EnemySpawner()
	:m_timer(0)
{

}
EnemySpawner::~EnemySpawner()
{

}



void EnemySpawner::setEnemySpawnerVector(ELEMENT m_CurrElement, int howMany)
{
	for (int a = 0; a < howMany; a++)
	{
		char * temp = "";
		switch (m_CurrElement)
		{
		case FIRE:
		{
			temp = "Image//fire_enemy.tga";
			break;
		}

		case FIRE_2:
		{
			temp = "Image//wood_enemy3.tga";
			break;
		}

		case WATER:
		{
			temp = "Image//blue_enemy.tga";
			break;
		}

		case WATER_2:
		{
			temp = "Image//wood_enemy3.tga";
			break;
		}

		case EARTH:
		{
			temp = "Image//wood_enemy3.tga";
			break;
		}

		case EARTH_2:
		{
			temp = "Image//wood_enemy3.tga";
			break;
		}
		}
		Vector3 randPos(m_Position.x + Math::RandFloatMinMax(-50, 50), m_Position.y, m_Position.z);
		Enemy* tempEnemy = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, randPos, Vector3(5, 5, 5), true, true, MeshBuilder::GenerateQuad("enemy", Color(1, 1, 1)), temp));
		tempEnemy->SetEntityMovementSpeed(Math::RandFloatMinMax(0.05f, 0.1f));

		if (m_CurrElement == FIRE || m_CurrElement == FIRE_2)
		{
			tempEnemy->setMeshVector(MeshBuilder::GenerateQuad("enemy", Color(1, 1, 1)), "Enemy", temp, 1, 4);
			tempEnemy->SetMesh(tempEnemy->getMeshVector()[0]);
			tempEnemy->setSpriteVector(tempEnemy->GetMesh(), 0, 3, 1, 0.8f, true);
		}
		else if (m_CurrElement == EARTH || m_CurrElement == EARTH_2)
		{
			tempEnemy->setMeshVector(MeshBuilder::GenerateQuad("enemy", Color(1, 1, 1)), "Enemy", temp, 2, 5);
			tempEnemy->SetMesh(tempEnemy->getMeshVector()[0]);
			tempEnemy->setSpriteVector(tempEnemy->GetMesh(), 2, 6, 1, 0.8f, true);

		}
		else if (m_CurrElement == WATER || m_CurrElement == WATER_2)
		{
			tempEnemy->setMeshVector(MeshBuilder::GenerateQuad("enemy", Color(1, 1, 1)), "Enemy", temp, 1, 3);
			tempEnemy->SetMesh(tempEnemy->getMeshVector()[0]);
			tempEnemy->setSpriteVector(tempEnemy->GetMesh(), 0, 2, 1, 0.8f, true);
		}
		tempEnemy->SetSpriteAnimation(tempEnemy->getSpriteVector()[0]);
		tempEnemy->SetEntityMaxHealth(10);
		tempEnemy->EnemyInit(200, m_CurrElement, 5, 400);
		this->enemyList.push_back(tempEnemy);
	}
}
void EnemySpawner::Update(double dt)
{
	for (std::vector<Enemy*>::iterator it = enemyList.begin(); it != enemyList.end(); it++)
	{
		Enemy * enemy= *it;
		if (!enemy->GetActive())
		{
			m_timer += dt;
			if (m_timer >= 5)
			{
				enemy->SetActive(true);
				enemy->EnemyInit(enemy->getEstimatedDistance(), enemy->GetElement(), enemy->GetEntityDamage(), enemy->getDetectionRange());
				enemy->SetMoveState(NO_STATE);
				enemy->setEntityHealth(10);
				m_timer = 0;
				break;
			}

		}
	
	} 

}
std::vector<Enemy*> EnemySpawner::getEnemySpawnerVector()
{
	return enemyList;
}
