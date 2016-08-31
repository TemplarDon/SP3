#include "GameObject_Map.h"
#include "GameObjectManager.h"

GameObject_Map::GameObject_Map()
	: m_Offset(0)
{
}

GameObject_Map::~GameObject_Map()
{
	if (m_Level)
	{
		delete m_Level;
		m_Level = NULL;
	}

	delete Quad;

	for (int y = 0; y < this->GetNumOfTiles_MapHeight(); ++y)
	{
		for (int x = 0; x < this->GetNumOfTiles_ScreenWidth(); ++x)
		{
			if (this->m_GameObjectMap[y][x])
			{
				m_GameObjectMap[y][x] = NULL;
			}
		}
	}

}

void GameObject_Map::Init(Map* Map, int TileSize)
{
	m_NumOfTiles_ScreenHeight = Map->GetNumOfTiles_ScreenHeight();
	m_NumOfTiles_ScreenWidth = Map->GetNumOfTiles_ScreenWidth();

	m_NumOfTiles_MapHeight = Map->GetNumOfTiles_MapHeight();
	m_NumOfTiles_MapWidth = Map->GetNumOfTiles_MapWidth();
	m_TileSize = TileSize;

	for (int y = 0; y < Map->GetNumOfTiles_MapHeight(); ++y)
	{
		std::vector<GameObject*> tempVec;
		m_GameObjectMap.push_back(tempVec);

		for (int x = 0; x < Map->GetNumOfTiles_MapWidth(); ++x)
		{
			m_GameObjectMap[y].push_back(new Environment);
		}
	}

	m_Level = new Level;

	for (int y = Map->GetNumOfTiles_MapHeight() - 1; y > 0; --y)
	{
		for (int x = 0; x < Map->GetNumOfTiles_MapWidth(); ++x)
		{
			// Create GameObject
			Vector3 Position;

			Position.x = (x * m_TileSize) + m_Offset;
			Position.y = ((Map->GetNumOfTiles_MapHeight() - y) * m_TileSize) - m_Offset;

			Vector3 Scale;
			Scale.Set(m_TileSize, m_TileSize, 1); 

			Quad = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));

			switch (Map->m_ScreenMap[y][x])
			{
			case 1:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//Tiles//fire_tile2.tga"));
				temp->SetElement(ELEMENT::NO_ELEMENT);
				temp->Init(true, false);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 91:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, false, Quad, "Image//Tiles//fire_tile2.tga"));
				temp->SetElement(ELEMENT::NO_ELEMENT);
				temp->Init(true, false);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 2:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//Tiles//fire_tile1.tga"));
				temp->SetElement(ELEMENT::NO_ELEMENT);
				temp->Init(true, false);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 3:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_WOOD, Position, Scale, true, true, Quad, "Image//Tiles//wood.tga"));
				temp->SetElement(ELEMENT::EARTH);
				temp->Init(true, true);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}

			case 4:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_ROCK, Position, Scale, true, true, Quad, "Image//Tiles//fire.tga"));
				temp->SetElement(ELEMENT::FIRE);
				temp->Init(true, true);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 5:
			{
				Collectibles* temp = dynamic_cast<Collectibles*>(GameObjectManager::SpawnGameObject(COLLECTIBLE, GO_DROP_HEALTH, Position, Vector3(3, 3, 3), true, true,Quad, "Image//UI//heart_icon.tga"));
				temp->InitCollectible(5);
				//m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 6:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_DEATHBBLOCK, Position, Scale, true, false, Quad ));
				temp->SetElement(ELEMENT::NO_ELEMENT);
				temp->Init(true, false);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 7:
			{
				//Quad = MeshBuilder::GenerateSpriteAnimation("checkpoint", 1, 3);
				//
				//SpriteAnimation* sa = static_cast<SpriteAnimation*>(Quad);
				//if (sa)
				//{
				//	sa->m_anim = new Animation();
				//	sa->m_anim->Set(0, 2, 1, 0.8f, true);
				//}
				//Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_CHECKPOINT, Position, Scale, false, true, Quad, "Image//Tiles//sprite_checkpoint.tga", true, sa));
				//temp->Init(false, false);
				//m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;

				Quad = MeshBuilder::GenerateSpriteAnimation("checkpoint", 1, 3);

				SpriteAnimation* sa = static_cast<SpriteAnimation*>(Quad);
				if (sa)
				{
					sa->m_anim = new Animation();
					sa->m_anim->Set(0, 2, 1, 0.8f, true);
				}
				Checkpoint* temp = dynamic_cast<Checkpoint*>(GameObjectManager::SpawnGameObject(CHECKPOINT, GO_CHECKPOINT, Position, Scale, false, true, Quad, "Image//Tiles//sprite_checkpoint.tga", true, sa));
				temp->Init(false, false);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				
				break;
			}
			case 8:
			{
				// ------------------ Player Spawn Code Goes Here --------------------- //

				// -------------------------------------------------------------------- //

				m_Level->InitLevel(Position);
				break;
			}
			case 9:
			{
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Tiles//door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(TEST);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 10:
			{
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Tiles//door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(TUTORIAL_LEVEL);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 11:
			{
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Portal//earth_door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(EARTH_LEVEL);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}
			case 12:
			{
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Portal//water_door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(WATER_LEVEL);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}

			case 13:
			{
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Portal//fire_door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(FIRE_LEVEL);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}

			case 14:
			{
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Portal//hub_door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(HUB_LEVEL);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}

			case 15:
			{
				// Water Enemy
				Enemy* temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Position, Scale, true, true, Quad, "Image//blue_enemy.tga"));
				temp->setMeshVector(Quad, "Water Enemy", "Image//blue_enemy.tga", 1, 3);
				temp->SetMesh(temp->getMeshVector()[0]);
				temp->setSpriteVector(temp->GetMesh(), 0, 2, 1, 0.8f, true);
				temp->SetSpriteAnimation(temp->getSpriteVector()[0]);
				temp->SetEntityMaxHealth(10);
				temp->EnemyInit(200, WATER, 5, 400);
				break;
			}

			case 16:
			{
				// Earth Enemy
				Enemy* temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Position, Scale, true, true, Quad, "Image//wood_enemy3.tga"));
				temp->setMeshVector(Quad,"Earth Enemy","Image//wood_enemy3.tga",2,5);
				temp->SetMesh(temp->getMeshVector()[0]);
				temp->setSpriteVector(temp->GetMesh(), 2, 6, 1, 0.8f, true);
				temp->SetSpriteAnimation(temp->getSpriteVector()[0]);
				temp->SetEntityMaxHealth(10);
				temp->EnemyInit(200, EARTH, 5, 400);
				break;
			}

			case 17:
			{
				// Fire Enemy
				Enemy* temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Position, Scale, true, true, Quad, "Image//wood_enemy3.tga"));
				temp->setMeshVector(Quad, "Fire Enemy", "Image//fire_enemy.tga", 1, 4);
				temp->SetMesh(temp->getMeshVector()[0]);
				temp->setSpriteVector(temp->GetMesh(), 0, 3, 1, 0.8f, true);
				temp->SetSpriteAnimation(temp->getSpriteVector()[0]);
				temp->SetEntityMaxHealth(10);
				temp->EnemyInit(200, FIRE, 5, 400);
				break;
			}

			case 25:
			{
					   // Water Boss
			   Enemy* temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Position, Vector3(20,20,20), true, true, Quad, "Image//blue_boss.tga"));
			   temp->setMeshVector(Quad, "Water Enemy", "Image//blue_boss.tga", 1, 9);
			   temp->SetMesh(temp->getMeshVector()[0]);
			   temp->setSpriteVector(temp->GetMesh(), 0, 8, 1, 0.8f, true);
			   temp->SetSpriteAnimation(temp->getSpriteVector()[0]);
			   temp->SetEntityMaxHealth(100);
			   temp->EnemyInit(200, WATER_2, 5, 400);
					   break;
			}

			case 26:
			{
				// Earth Boss
				Scale.x += 3;
				Scale.y += 3;
				Enemy* temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Position, Scale, true, true, Quad, "Image//wood_enemy3.tga"));
				temp->setMeshVector(Quad, "Earth Enemy", "Image//wood_enemy3.tga", 2, 5);
				temp->SetMesh(temp->getMeshVector()[0]);
				temp->setSpriteVector(temp->GetMesh(), 2, 6, 1, 0.8f, true);
				temp->SetSpriteAnimation(temp->getSpriteVector()[0]);
				temp->SetEntityMaxHealth(500);
				temp->EnemyInit(200, EARTH_2, 5, 400);
				break;
			}

			case 27:
			{
					   // Fire Boss
					  Enemy* temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Position, Vector3(15,15,15), true, true, Quad, "Image//fire_enemy.tga"));
					  temp->setMeshVector(Quad, "Fire Enemy", "Image//fire_enemy.tga", 1, 4);
					  temp->SetMesh(temp->getMeshVector()[0]);
					  temp->setSpriteVector(temp->GetMesh(), 0, 3, 1, 0.8f, true);
					  temp->SetSpriteAnimation(temp->getSpriteVector()[0]);
					  temp->SetEntityMaxHealth(500);
					  temp->EnemyInit(200, FIRE_2, 5, 400);
					  temp->SetElementLevel(FIRE, 3);
					   break;
			}


			case 28:
			{
				// Fire Boss portal
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Portal//fire_boss_door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(FIRE_BOSS_LEVEL);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}

			case 29:
			{
				// Water Boss portal
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Portal//water_boss_door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(WATER_BOSS_LEVEL1);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			} 

			case 30:
			{
				// Earth Boss portal
				Transition* temp = dynamic_cast<Transition*>(GameObjectManager::SpawnGameObject(TRANSITION, GO_DOOR, Position, Scale, false, true, Quad, "Image//Portal//earth_boss_door.tga"));
				temp->Init(false, false);
				temp->SetNextTransition(EARTH_BOSS_LEVEL);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}

			case 35:
			{
				EnemySpawner* temp = dynamic_cast<EnemySpawner*>(GameObjectManager::SpawnGameObject(ENEMYSPAWNER, GO_ENEMYSPAWNER, Position, Scale, true, false, Quad));
				temp->setEnemySpawnerVector(WATER, 3);
				break;
			}
			case 36:
			{
				EnemySpawner* temp = dynamic_cast<EnemySpawner*>(GameObjectManager::SpawnGameObject(ENEMYSPAWNER, GO_ENEMYSPAWNER, Position, Scale, true, false, Quad));
				temp->setEnemySpawnerVector(EARTH, 3);
				break;
			}
			case 37:
			{	
				EnemySpawner* temp = dynamic_cast<EnemySpawner*>(GameObjectManager::SpawnGameObject(ENEMYSPAWNER, GO_ENEMYSPAWNER, Position, Scale, true, false, Quad));
				temp->setEnemySpawnerVector(FIRE, 3);
				break;
			}
			case 38:
			{
				EnemySpawner* temp = dynamic_cast<EnemySpawner*>(GameObjectManager::SpawnGameObject(ENEMYSPAWNER, GO_ENEMYSPAWNER, Position, Scale, true, false, Quad));
				temp->setEnemySpawnerVector(WATER, 1);
				break;
			}

			case 39:
			{
				EnemySpawner* temp = dynamic_cast<EnemySpawner*>(GameObjectManager::SpawnGameObject(ENEMYSPAWNER, GO_ENEMYSPAWNER, Position, Scale, true, false, Quad));
				temp->setEnemySpawnerVector(EARTH, 1);
				break;
			}
			case 40:
			{
				EnemySpawner* temp = dynamic_cast<EnemySpawner*>(GameObjectManager::SpawnGameObject(ENEMYSPAWNER, GO_ENEMYSPAWNER, Position, Scale, true, false, Quad)); 
				temp->setEnemySpawnerVector(FIRE, 1);
				break;
			}

			case 101:
			{
				NPC* temp = dynamic_cast<NPC*>(GameObjectManager::SpawnGameObject(NPCS, GO_SIGNBOARD, Position, Scale, false, true, Quad, "Image//Tiles//signboardV2.tga"));
				temp->InitNPC(false);
				temp->SetDialouge("W - Jump");
				temp->SetDialouge("A - Move Left");
				temp->SetDialouge("D - Move Right");
				temp->SetDialouge("Space - Attack");
				temp->SetDialouge("F - Vaccum");
				break;
			}

			case 102:
			{
				NPC* temp = dynamic_cast<NPC*>(GameObjectManager::SpawnGameObject(NPCS, GO_SIGNBOARD, Position, Scale, false, true, Quad, "Image//Tiles//signboardV2.tga"));
				temp->InitNPC(false);
				temp->SetDialouge("Portals:");
				temp->SetDialouge("Blue: Water");
				temp->SetDialouge("Red: Fire");
				temp->SetDialouge("Green: Earth");
				break;
			}
			case 150:
			{
				NPC* temp = dynamic_cast<NPC*>(GameObjectManager::SpawnGameObject(NPCS, GO_SIGNBOARD, Position, Scale, false, true, Quad, "Image//Tiles//signboardV2.tga"));
				temp->InitNPC(false);
				temp->SetDialouge("Try Using the ");
				temp->SetDialouge("Earth Ultimate ability!");
				break;
			}
			case 151:
			{
				NPC* temp = dynamic_cast<NPC*>(GameObjectManager::SpawnGameObject(NPCS, GO_SIGNBOARD, Position, Scale, false, true, Quad, "Image//Tiles//signboardV2.tga"));
				temp->InitNPC(false);
				temp->SetDialouge("1:To save our mother Earth");
				temp->SetDialouge("from any alien attack");
				break;
			}
			case 152:
			{
				NPC* temp = dynamic_cast<NPC*>(GameObjectManager::SpawnGameObject(NPCS, GO_SIGNBOARD, Position, Scale, false, true, Quad, "Image//Tiles//signboardV2.tga"));
				temp->InitNPC(false);
				temp->SetDialouge("2:From vicious giant insects");
				temp->SetDialouge(" who have once again come back");

				break;
			}
			case 153:
			{
				NPC* temp = dynamic_cast<NPC*>(GameObjectManager::SpawnGameObject(NPCS, GO_SIGNBOARD, Position, Scale, false, true, Quad, "Image//Tiles//signboardV2.tga"));
				temp->InitNPC(false);
				temp->SetDialouge("We'll unleash all our forces,");
				temp->SetDialouge("We won't cut them any slack ");
				break;
			}
			case 154:
			{
				NPC* temp = dynamic_cast<NPC*>(GameObjectManager::SpawnGameObject(NPCS, GO_SIGNBOARD, Position, Scale, false, true, Quad, "Image//Tiles//signboardV2.tga"));
				temp->InitNPC(false);
				temp->SetDialouge("The E.D.F deploys!");
				break;
			}


			}
		}
	}
}

void GameObject_Map::SortMap()
{
	for (int y = 1; y < this->m_NumOfTiles_ScreenHeight; ++y)
	{
		for (int x = 0; x < this->m_NumOfTiles_ScreenWidth; ++x)
		{
			Environment* CheckGameObject = dynamic_cast<Environment*>(this->m_GameObjectMap[y][x]);
			Environment* CheckGameObject_Below = dynamic_cast<Environment*>(this->m_GameObjectMap[y - 1][x]);

			if (!CheckGameObject->GetActive())
				continue;

			if (CheckGameObject->GetFallStatus() && !CheckGameObject_Below->GetCollidable())
			{
				this->m_GameObjectMap[y][x] = CheckGameObject_Below;
				this->m_GameObjectMap[y - 1][x] = CheckGameObject;
			}
		}
	}
}

void GameObject_Map::AddIntoMap(GameObject* GameObjectToBeAdded)
{
	int ObjectPos_X = (int)(GameObjectToBeAdded->GetPosition().x / this->m_TileSize);
	int ObjectPos_Y = (int)(GameObjectToBeAdded->GetPosition().y / this->m_TileSize);

	this->m_GameObjectMap[ObjectPos_Y][ObjectPos_X] = GameObjectToBeAdded;
}