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

GameObject* GameObjectManager::SpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName, bool IsSprite)
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
		SpriteAnimation* sa = static_cast<SpriteAnimation*>(mesh);
		if (sa)
		{
			sa->m_anim = new Animation();
			sa->m_currentTime = 0;
			sa->m_row = 0;
			sa->m_col = 0;
			sa->m_anim->Set(0, 2, 1, 0.8f, true);
			go->SetSpriteAnimation(sa);
		}
	}

	m_goList.push_back(go);

	return go;
}
GameObject* GameObjectManager::TestSpawnGameObject(OBJECT_TYPE ObjectType, GAMEOBJECT_TYPE GoType, Vector3 Position, Vector3 Scale, bool Collidable, bool Visible, Mesh* mesh, const char* TargaName)
{
	return nullptr;
}