#ifndef _GAME_OBJECT_MAP
#define _GAME_OBJECT_MAP

#include "GameObject.h"
#include "Map.h"
#include "MeshBuilder.h"
#include "Level.h"

class GameObject_Map
{
public:
	GameObject_Map();
	~GameObject_Map();

	std::vector<std::vector<GameObject*>> m_GameObjectMap;

	void Init(Map* Map, int TileSize = 5);
	void SortMap();
	void AddIntoMap(GameObject* ObjectToBeAdded);

	int GetTileSize()
	{
		return m_TileSize;
	}

	int GetNumOfTiles_ScreenHeight()
	{
		return m_NumOfTiles_ScreenHeight;
	}

	int GetNumOfTiles_ScreenWidth()
	{
		return m_NumOfTiles_ScreenWidth;
	}

	int GetNumOfTiles_MapHeight()
	{
		return m_NumOfTiles_MapHeight;
	}

	int GetNumOfTiles_MapWidth()
	{
		return m_NumOfTiles_MapWidth;
	}

	float GetOffset()
	{
		return m_Offset;
	}

	Level* GetLevel()
	{
		return m_Level;
	}

private:
	int m_TileSize;

	int m_NumOfTiles_ScreenHeight;
	int m_NumOfTiles_ScreenWidth;


	int m_NumOfTiles_MapHeight;
	int m_NumOfTiles_MapWidth;

	float m_Offset;

	Level* m_Level;
	Mesh* Quad;
	
};

#endif // !OBJECT_MAP
