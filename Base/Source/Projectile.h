#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "ElementalObject.h"
#include "BaseElement.h"



class Projectile : public ElementalObject
{

	 
public:
	Projectile(bool Direction,);
	~Projectile();

	void projectileUpdate();
	//void movementUpdate();

	void spawnProjectile(bool direction, Vector3 entityPosition, Vector3 scale,Mesh* mesh);
	//int calculateDamage(int playerHealth);



private:
	int damage;
	Vector3 m_Velocity;
//	Vector3 m_Direction;
	Vector3 m_Normal;
	float m_Mass;
	float bulletVelocity;
	//int dmgResistance;

};












#endif