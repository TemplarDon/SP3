#include "GameObject_Map.h"
#include "GameObjectManager.h"

GameObject_Map::GameObject_Map()
	: m_Offset(0)
{}

GameObject_Map::~GameObject_Map()
{}

void GameObject_Map::Init(Map* Map, int TileSize)
{
	m_NumOfTiles_ScreenHeight = Map->GetNumOfTiles_ScreenHeight();
	m_NumOfTiles_ScreenWidth = Map->GetNumOfTiles_ScreenWidth();
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

	for (int y = Map->GetNumOfTiles_MapHeight() - 1; y > 0; --y)
	{
		for (int x = 0; x < Map->GetNumOfTiles_MapWidth(); ++x)
		{
			// Create GameObject
			Vector3 Position;

			Position.x = (x * m_TileSize) + m_Offset;
			Position.y = ((Map->GetNumOfTiles_MapHeight() - y) * m_TileSize) - m_Offset;

			Vector3 Scale;
			Scale.Set(5, 5, 1);

			Mesh* Quad = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));

			switch (Map->m_ScreenMap[y][x])
			{
			case 1:
			{
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//Tiles//testground.tga");
				break;
			}
			//case 3:
			//{
			//	m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//tree.tga");
			//	break;
			//}

			case 8:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_WOOD, Position, Scale, true, true, Quad, "Image//Tiles//wood.tga"));
				temp->SetElement(ELEMENT::EARTH);
				temp->Init(true, true);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
				break;
			}

			case 9:
			{
				Environment* temp = dynamic_cast<Environment*>(GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_ROCK, Position, Scale, true, true, Quad, "Image//Tiles//fire.tga"));
				temp->SetElement(ELEMENT::FIRE);
				temp->Init(true, true);
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = temp;
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



			if (CheckGameObject->GetCollidable() && !CheckGameObject_Below->GetCollidable())
			{
				//this->m_GameObjectMap[y][x] = CheckGameObject_Below;
				//this->m_GameObjectMap[y - 1][x] = CheckGameObject;
			}
		}
	}
}