#include "GameObject_Map.h"
#include "GameObjectManager.h"

GameObject_Map::GameObject_Map()
{}

GameObject_Map::~GameObject_Map()
{}

void GameObject_Map::Init(Map* Map)
{
	for (int y = 0; y < Map->GetNumOfTiles_MapHeight(); ++y)
	{
		std::vector<GameObject*> tempVec;
		m_GameObjectMap.push_back(tempVec);

		for (int x = 0; x < Map->GetNumOfTiles_MapWidth(); ++x)
		{
			m_GameObjectMap[y].push_back(nullptr);
		}
	}

	for (int y = Map->GetNumOfTiles_MapHeight() - 1; y > 0; --y)
	{
		for (int x = 0; x < Map->GetNumOfTiles_MapWidth(); ++x)
		{
			// Create GameObject
			Vector3 Position;

			float offset = 2.5;

			Position.x = (x * 5) + offset;
			Position.y = ((Map->GetNumOfTiles_MapHeight() - y) * 5) - offset;

			Vector3 Scale;
			Scale.Set(5, 5, 1);

			Mesh* Quad = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));

			switch (Map->m_ScreenMap[y][x])
			{
			case 1:
			{
				//GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//Tiles//testground.tga");
				m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//Tiles//testground.tga");
				break;
			}

			}


		}
	}
}