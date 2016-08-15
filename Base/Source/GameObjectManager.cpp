#include "GameObjectManager.h"





GameObject* GameObjectManager::FetchGameObject(OBJECT_TYPE ObjectType)
{
	GameObject* TempGameObject = NULL;

	switch (ObjectType)
	{
	case OBJECT_TYPE::ENVIRONMENT:
	{
		TempGameObject = new Environment();
		break;
	}

	case OBJECT_TYPE::PROJECTILE:
	{
		break;
	}

	case OBJECT_TYPE::PLAYER:
	{
		break;
	}

	case OBJECT_TYPE::ENEMY:
	{
		break;
	}
	}

	return TempGameObject;
}
void  GameObjectManager::SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, std::vector<GameObject *> m_goList)
{
	GameObject* go = FetchGameObject(ObjectType);

	go->SetType(GoType);
	go->SetPosition(Position);
	go->SetScale(Scale);
	go->SetCollidable(Collidable);
	go->SetVisible(Visible);

	switch (GoType)
	{
	case GO_BALL:
	{
		go->SetMesh(mesh);
		break;
	}
	}

	m_goList.push_back(go);
}
//std::vector<GameObject *> GameObjectManager::getGameObjectList()
//{
//	return m_goList;
//}
//void  GameObjectManager::setGameObjectList(std::vector<GameObject *> m_goList)
//{
//	this->m_goList = m_goList;
//}