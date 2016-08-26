#include "GameObjectManager.h"
#include "GL\glew.h"
#include "LoadTGA.h"

GameObject* GameObjectManager::FetchGameObject(OBJECT_TYPE ObjectType)
{
	for (std::vector<GameObject *>::iterator it = GameObjectManager::m_goList.begin(); it != GameObjectManager::m_goList.end(); ++it)
	{
		GameObject* TempGameObject = (GameObject *)*it;

		if (TempGameObject->GetActive())
			continue;

		switch (ObjectType)
		{
		case OBJECT_TYPE::ENVIRONMENT:
		{
			TempGameObject = new Environment();
			break;
		}

		case OBJECT_TYPE::TRANSITION:
		{
			TempGameObject = new Transition();
			break;
		}
		case OBJECT_TYPE::PROJECTILE:
		{
			TempGameObject = new Projectile();
			break;
		}

		case OBJECT_TYPE::PLAYER:
		{
			TempGameObject = new Player();
			break;
		}

		case OBJECT_TYPE::ENEMY:
		{
			TempGameObject = new Enemy();
			break;
		}

		case OBJECT_TYPE::COLLECTIBLE:
		{
			TempGameObject = new Collectibles();
			break;
		}
		case OBJECT_TYPE::ENEMYSPAWNER:
		{
			TempGameObject = new EnemySpawner();
			break;
		}
		}

		return TempGameObject;
	}

	for (int i = 0; i < 10; ++i)
	{
		Environment* temp = new Environment();
		temp->SetActive(false);
		m_goList.push_back(temp);
	}

	return FetchGameObject(ObjectType);
}

GameObject* GameObjectManager::SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName, bool IsSprite, SpriteAnimation* sa)
{
	GameObject* go = FetchGameObject(ObjectType);

	go->SetActive(true);
	go->SetObjectType(ObjectType);
	go->SetType(GoType);
	go->SetPosition(Position);
	go->SetScale(Scale);
	go->SetCollidable(Collidable);
	go->SetVisible(Visible);
	go->SetMesh(mesh);

	if (TargaName != "")
	{
		go->GetMesh()->textureID = LoadTGA(TargaName);
	}

	if (IsSprite)
	{
		go->SetSpriteAnimation(sa);
	}

	m_goList.push_back(go);

	return go;
}


GameObject* GameObjectManager::TestSpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName)
{
	return nullptr;
}