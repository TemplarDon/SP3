#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H

#include "GameObject.h"

class Collectibles : public GameObject
{
public:
	Collectibles();
	~Collectibles();

	virtual void InitCollectible(int factor);

	virtual int GetFactor();
	virtual void SetFactor(int factor);

	virtual void CollisionResponse(GameObject* OtherGo);

private:
	int m_Factor;
};

#endif // !COLLECTIBLES_H
