#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "ElementalObject.h"
#include "BaseElement.h"



class Projectile : public ElementalObject
{

	 
public:
	Projectile(bool Direction,Vector3 m_Position,Vector3 m_Velocity);
	~Projectile();

	void projectileUpdate(double dt);
	



private:
	int damage;
	Vector3 m_Velocity;
	Vector3 m_Position;
	Vector3 m_Normal;
	bool Direction;

};












#endif