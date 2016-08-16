#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "ElementalObject.h"
#include "Map.h"
#include "Mesh.h"
#include "Vector3.h"
#include "AttackBase.h"

class Entity : public ElementalObject
{
public:
	Entity();
	~Entity();
	
	//Setter for entity health
	void SetEntityHealth(int health);
	//Getter for entity health
	int GetEntityHealth();

	//Setter for entity damage
	void SetEntityDamage(int damage);
	//Getter for entity damage
	int GetEntityDamage();

	//Setter for entity taken damage
	void SetEntityTakenDamage(int takendamage);
	//Getter for entity taken damage
	int GetEntityTakenDamage();

	//Setter for entity movement speed
	void SetEntityMovementSpeed(int movementspeed);
	//Getter for entity movement speed
	int GetEntityMovementSpeed();


private:
	int Health;
	int Damage;
	int TakenDamage;
	int MovementSpeed;
};

#endif