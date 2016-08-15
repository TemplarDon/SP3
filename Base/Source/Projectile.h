#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "ElementalObject.h"
#include "BaseElement.h"



class Projectile : public ElementalObject
{

	 
public:
	Projectile(bool Direction,Vector3 m_Position,Vector3 m_Velocity,int damage);
	~Projectile();

	void projectileUpdate(double dt);
	
	void setDamage(int damage);
	int	 getDamage();
	
	void setVelocity(Vector3 Velocity);
	Vector3 getVelocity();

	void setPosition(Vector3 Position);
	Vector3 getPosition();

	void setDirection(bool Direction);
	bool getDirection();


private:
	int damage;
	Vector3 m_Velocity;
	Vector3 m_Position;
	Vector3 m_Normal;
	bool Direction;

};












#endif