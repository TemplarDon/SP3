#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include <vector>
#include "mesh.h"

enum OBJECT_TYPE
{
	NO_TYPE = 0,
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
	GO_TOTAL,
};

class GameObject
{
public:

	virtual ~GameObject();

	virtual GAMEOBJECT_TYPE GetType();
	virtual void SetType(GAMEOBJECT_TYPE SetType);

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

	virtual bool EmpricalCheckCollisionWith(GameObject* OtherGo, double dt);
	virtual float MathematicalCheckCollisionWith(GameObject* OtherGo);
	virtual void CollisionResponse(GameObject* OtherGo);

protected:

	GameObject();

	GAMEOBJECT_TYPE m_Type;
	Vector3 m_Position;
	Vector3 m_Scale;
	bool m_Active;
	bool m_Collidable;
	bool m_Visible;

	Mesh* m_ObjectMesh;

	// ----------------- These variables should be moved to Projectile Class ----------------- // 
	//Vector3 m_Velocity;
	//Vector3 m_Direction;
	//Vector3 m_Normal;
	//float m_Mass;
	// --------------------------------------------------------------------------------------- //

};

#endif