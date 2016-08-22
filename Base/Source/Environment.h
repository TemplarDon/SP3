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
   
	bool GetFallStatus();

protected:

	bool m_Destructible;
	bool m_CanFall;
	float m_FallSpeed;


	virtual void CollisionResponse(GameObject* OtherGo);
};

#endif // !ENVIRONMENT_H
