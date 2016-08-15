#ifndef GAME_OBJECT_MAP
#define GAME_OBJECT_MAP

#include "GameObjectManager.h"
#include "MeshBuilder.h"
#include "Map.h"

struct GameObject_Map
{
	GameObject_Map();
	~GameObject_Map();

	std::vector<std::vector<GameObject*>> m_GameObjectMap;

	void Init(Map* Map)
	{
		for (int y = Map->GetNumOfTiles_MapHeight() - 1; y >= 0; --y)
		{
			for (int x = 0; x < Map->GetNumOfTiles_MapWidth(); ++x)
			{
				// Create GameObject
				Vector3 Position;

				Position.x = (x * 5) + 2.5;
				Position.y = ((Map->GetNumOfTiles_MapHeight() - y) * 5) - 2.5;

				Vector3 Scale;
				Scale.Set(5, 5, 1);

				Mesh* Quad = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));

				switch (Map->m_ScreenMap[y][x])
				{
				case 1:
				{
					GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//Tiles//testground.tga");
					//m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad, "Image//Tiles//testground.tga");
					break;
				}
					
				}

				
			}
		}
	}
};

#endif // !OBJECT_MAP
