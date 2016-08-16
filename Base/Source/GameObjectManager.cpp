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
		break;
	}
	}

	return TempGameObject;
}

GameObject* GameObjectManager::SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName)
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

	m_goList.push_back(go);

	return go;
}

Player* GameObjectManager::SpawnPlayerObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName)
{
	Player* go = new Player();

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

	m_goList.push_back(go);

	return go;
}

Projectile* GameObjectManager::SpawnProjectileObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, float LifetTime, int Damage, bool Directions,float speedBullet, Mesh* mesh, const char* TargaName)
{
    Projectile* go = new Projectile();

    go->SetActive(true);
	go->SetObjectType(ObjectType);
    go->SetType(GoType);
    go->SetPosition(Position);
    go->SetScale(Scale);
    go->SetCollidable(Collidable);
    go->SetVisible(Visible);
    go->projectileInit(Directions,Position,speedBullet,Damage,LifetTime);
    // May need to add for velocityy and element

    go->SetMesh(mesh);

    if (TargaName != "")
    {
        go->GetMesh()->textureID = LoadTGA(TargaName);
    }

    m_goList.push_back(go);

    return go;
}

GameObject* GameObjectManager::TestSpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName)
{
	return nullptr;
}