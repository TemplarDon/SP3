#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include <vector>
#include "SpriteAnimation.h"

enum OBJECT_TYPE
{
	NO_TYPE = 0,
    PLATFORM,
	ENVIRONMENT,
	PROJECTILE,
	PLAYER,
	ENEMY,
	TOTAL_TYPE,
};

enum GAMEOBJECT_TYPE
{
	GO_NONE = 0,
	GO_BALL,
	GO_WALL,
	GO_PILLAR,
	GO_BLOCK,
	GO_TEST,
	GO_PLAYER,
    GO_EARTHMELEE_PROJECTILE,
	GO_ENEMY,
	GO_BACKGROUND,
	GO_ROCK,
	GO_WOOD,
	GO_TOTAL,
};

class GameObject
{
public:

	virtual ~GameObject();

	virtual GAMEOBJECT_TYPE GetType();
	virtual void SetType(GAMEOBJECT_TYPE SetType);

	virtual OBJECT_TYPE GetObjectType();
	virtual void SetObjectType(OBJECT_TYPE SetObjectType);

	virtual Vector3 GetPosition();
	virtual void SetPosition(Vector3 SetPos);

	virtual Vector3 GetScale();
	virtual void SetScale(Vector3 SetScale);

	virtual bool GetActive();
	virtual void SetActive(bool SetActive);

	virtual bool GetCollidable();
	virtual void SetCollidable(bool SetCollidable);

	virtual bool GetVisible();
	virtual void SetVisible(bool SetVisible);

	virtual Mesh* GetMesh();
	virtual void SetMesh(Mesh* SetMesh);

	virtual SpriteAnimation* GetSpriteAnimation();
	virtual void SetSpriteAnimation(SpriteAnimation* SetSpriteAnimation);

	virtual bool EmpricalCheckCollisionWith(GameObject* OtherGo, double dt);
	virtual float MathematicalCheckCollisionWith(GameObject* OtherGo);
	virtual void CollisionResponse(GameObject* OtherGo);

    virtual void Update(double dt)
    {}

protected:

	GameObject();

	GAMEOBJECT_TYPE m_Type;
	OBJECT_TYPE m_ObjectType;
	Vector3 m_Position;
	Vector3 m_Scale;
	bool m_Active;
	bool m_Collidable;
	bool m_Visible;
	SpriteAnimation* m_SpriteAnimation;

	Mesh* m_ObjectMesh;
};

#endif