#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "ElementalObject.h"

class Entity : public ElementalObject
{
public:
	Entity();
	~Entity();
	
	//Getter for entity health
	int GetEntityHealth();
	//Setter for enetity health
	void SetEntityHealth(int health);

	

private:

	int Health;
	int Damage;
	int TakenDamage;
	int MovementSpeed;

};

#endif