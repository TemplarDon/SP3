#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include <vector>
#include "SpriteAnimation.h"

enum LEVEL
{
	TEST,
	TUTORIAL_LEVEL,
	HUB_LEVEL,
	EARTH_LEVEL,
	FIRE_LEVEL,
	WATER_LEVEL,
	FIRE_BOSS_LEVEL,
	WATER_BOSS_LEVEL1,
	WATER_BOSS_LEVEL2,
	WATER_BOSS_LEVEL3,
	EARTH_BOSS_LEVEL,
};

enum OBJECT_TYPE
{
	NO_TYPE = 0,
    PLATFORM,
	ENVIRONMENT,
	TRANSITION,
	PROJECTILE,
	PLAYER,
	ENEMY,
	COLLECTIBLE,
	ENEMYSPAWNER,
	NPCS,
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
    GO_ATTACK,
    GO_SHEILD,
	GO_ENEMY,
	GO_BACKGROUND,
	GO_ROCK,
	GO_WOOD,
	GO_CHECKPOINT,
	GO_EARTH_WALL,
	GO_DOOR,
	GO_DROP_HEALTH,
	GO_ENEMYSPAWNER,
	GO_SIGNBOARD,
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


	virtual bool EmpricalCheckCollisionWith(GameObject* OtherGo, double dt, float offset = 30);

	virtual bool getRotate();
	virtual void setRotate(bool rotate);

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
	bool rotate;
	SpriteAnimation* m_SpriteAnimation;

	Mesh* m_ObjectMesh;
};

#endif