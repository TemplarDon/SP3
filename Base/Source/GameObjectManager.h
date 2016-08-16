#ifndef GAMEOBJECTMANAGER_H_
#define GAMEOBJECTMANAGER_H_

#include "Environment.h"
#include "MeshBuilder.h"
#include "Player.h"

class GameObjectManager
{
public:
	static GameObject* FetchGameObject(OBJECT_TYPE ObjectType);
	static void SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName = "");

	std::vector<GameObject*> GetGameObjectList();

	static std::vector<GameObject*> m_goList;
};












#endif