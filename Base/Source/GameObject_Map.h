#ifndef _GAME_OBJECT_MAP
#define _GAME_OBJECT_MAP

#include "GameObject.h"
#include "Map.h"
#include "MeshBuilder.h"

class GameObject_Map
{
public:
	GameObject_Map();
	~GameObject_Map();

	std::vector<std::vector<GameObject*>> m_GameObjectMap;

	void Init(Map* Map);
};

#endif // !OBJECT_MAP
