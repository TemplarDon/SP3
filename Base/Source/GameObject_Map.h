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

	void Init(Map* Map, std::vector<GameObject*> GoList)
	{
		for (int y = Map->GetNumOfTiles_MapHeight(); y >= 0; --y)
		{
			for (int x = 0; x < Map->GetNumOfTiles_MapWidth(); ++x)
			{
				// Create GameObject
				// Pushback object into GoList

				Vector3 Position;

				Position.x = x * Map->GetTileSize();
				Position.y = (Map->GetNumOfTiles_MapHeight() - y) * Map->GetTileSize();
				Vector3 Scale;

				Mesh* Quad = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));

				switch (Map->m_ScreenMap[y][x])
				{
				case 1:
				{
					GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_BLOCK, Position, Scale, true, true, Quad);
					break;
				}
					
				}

				// Add GameObject to m_GameObjectMap
				//m_GameObjectMap[Map->GetNumOfTiles_MapHeight() - y][x] = new GameObject;
			}
		}
	}
};

#endif // !OBJECT_MAP
