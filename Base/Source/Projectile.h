#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "ElementalObject.h"
#include "BaseElement.h"



class Projectile : public ElementalObject
{


public:
	Projectile();
	//Projectile(bool Direction,Vector3 m_Position,Vector3 m_Velocity,int damage);
	~Projectile();
	void projectileInit(bool Direction, Vector3 m_Position, float bulletSpeed, int damage, float lifeTime, ELEMENT element);
	void projectileUpdate(double dt);
	void setDamage(int damage);
	int	 getDamage();
	void SetBulletSpeed();
	void setVelocity(Vector3 Velocity);
	Vector3 getVelocity();

	/*void setPosition(Vector3 Position);
	Vector3 getPosition();*/

	void setDirection(bool Direction);
	bool getDirection();

	void setLifetime(float lifeTime);
	float getLifetime();

	virtual void Update(double dt);


private:
	int damage;
	Vector3 m_Velocity = Vector3(2, 0, 0);
	//Vector3 m_Position;
	Vector3 m_Normal;
	float lifeTime;
	bool Direction;
	float speedBullet;

};












#endif