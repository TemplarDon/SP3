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
    void projectileInit(bool Direction, Vector3 m_Position, float bulletSpeed, int damage, float lifeTime, ELEMENT element,bool isHostileProjectile,float rotation);

	void projectileUpdate(double dt);
	void setDamage(int damage);
	int	 getDamage();
	void SetBulletSpeed();

	void setVelocity();
	Vector3 getVelocity();

	void setDirection(bool Direction);
	bool getDirection();

	void setLifetime(float lifeTime);
	float getLifetime();
	
	void setRotation(float rotation);
	float getRotation();
	virtual void Update(double dt);

	virtual void UpdatePhysics(double dt, Vector3 Gravity = Vector3(0, -60, 0));
	virtual void CollisionResponse(GameObject* OtherGo);


private:
	int damage;
	Vector3 m_Velocity ;
	//Vector3 m_Position;
	Vector3 m_Normal;
	float lifeTime;
	bool Direction;
	float speedBullet;
    bool isHostileProjectile;
	float rotation;
};












#endif