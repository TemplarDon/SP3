#ifndef GAMEOBJECTMANAGER_H_
#define GAMEOBJECTMANAGER_H_

#include "Environment.h"

class GameObjectManager
{
public:

	static GameObject* FetchGameObject(OBJECT_TYPE ObjectType);
	static void SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, std::vector<GameObject *> m_goList);

	std::vector<GameObject *> getGameObjectList();
	void setGameObjectList(std::vector<GameObject *> m_goList);

protected:
	std::vector<GameObject *> m_goList;

};












#endif