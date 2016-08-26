#ifndef GAMEOBJECTMANAGER_H_
#define GAMEOBJECTMANAGER_H_

#include "Transition.h"
#include "Enemy.h"
#include "Player.h"
#include "MeshBuilder.h"
#include "Collectibles.h"
#include "EnemySpawner.h"

class GameObjectManager
{
public:
	static GameObject* FetchGameObject(OBJECT_TYPE ObjectType);
	static GameObject* SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName = "", bool IfSprite = false, SpriteAnimation* sa = NULL);

	static std::vector<GameObject*> m_goList;

	// ----------- Try static cast pointer to make function generic (SpriteAnimation) ----------- //

	static GameObject* TestSpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName = "");

};












#endif