#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "ElementalObject.h"

class Environment : public ElementalObject
{
public:
	Environment();
	virtual ~Environment();

protected:

	bool m_Destructible;

	virtual void CollisionResponse(GameObject* OtherGo);
};

#endif // !ENVIRONMENT_H
