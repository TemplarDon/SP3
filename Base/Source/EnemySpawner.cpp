#include "EnemySpawner.h"
#include "GameObjectManager.h"




EnemySpawner::EnemySpawner()
	:m_timer(6)
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
			temp = "Image//wood_enemy3.tga";
			break;
			}

			case FIRE_2:
			{
			temp = "Image//wood_enemy3.tga";
			break;
			}

			case WATER:
			{
			temp = "Image//wood_enemy3.tga";
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
		Vector3 randPos(m_Position.x + Math::RandFloatMinMax(-250, 250), m_Position.y, m_Position.z);
		Enemy* tempEnemy = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, randPos, Vector3(5, 5, 5), true, true, MeshBuilder::GenerateQuad("enemy", Color(1, 1, 1)), temp));
		tempEnemy->SetEntityMovementSpeed(Math::RandFloatMinMax(0.05f, 0.1f));
		tempEnemy->setMeshVector(MeshBuilder::GenerateQuad("enemy", Color(1, 1, 1)), "Earth Enemy", "Image//wood_enemy3.tga", 2, 5);
		tempEnemy->SetMesh(tempEnemy->getMeshVector()[0]);
		tempEnemy->setSpriteVector(tempEnemy->GetMesh(), 2, 6, 1, 0.8f, true);
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
			if (m_timer >= 5)
			{
				enemy->SetActive(true);
				m_timer = 0;
			}
		}
	
	}
	m_timer += dt;

}
std::vector<Enemy*> EnemySpawner::getEnemySpawnerVector()
{
	return enemyList;
}
