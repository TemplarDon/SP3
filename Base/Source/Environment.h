#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "ElementalObject.h"

class Environment : public ElementalObject
{
public:
	Environment();
	virtual ~Environment();

	virtual void Init(bool Destructible, bool CanFall);
	virtual void Update(double dt, GameObject_Map* Map);
    virtual void Update_Sheild(Vector3 playerPos);

	virtual void CollisionResponse(GameObject* OtherGo, GameObject_Map* Map);

	bool GetFallStatus();

	void SetLifeTimeBool(bool);
	void SetLifeTime(float);

protected:

	bool m_Destructible;
	bool m_CanFall;
	float m_FallSpeed;

	bool m_HasLifeTime;
	float m_LifeTime;


};

#endif // !ENVIRONMENT_H
