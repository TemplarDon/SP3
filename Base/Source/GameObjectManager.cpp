#include "GameObjectManager.h"
#include "GL\glew.h"
#include "LoadTGA.h"

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
		TempGameObject = new Player();
		break;
	}

	case OBJECT_TYPE::ENEMY:
	{
		break;
	}
	}

	return TempGameObject;
}
void GameObjectManager::SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName)
{
	GameObject* go = FetchGameObject(ObjectType);

	go->SetActive(true);
	go->SetType(GoType);
	go->SetPosition(Position);
	go->SetScale(Scale);
	go->SetCollidable(Collidable);
	go->SetVisible(Visible);
	go->SetMesh(mesh);
	go->GetMesh()->textureID = LoadTGA(TargaName);

	m_goList.push_back(go);
}