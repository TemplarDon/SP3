#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{

}

void Entity::SetEntityHealth(int health)
{
	this->Health = health;
}

int Entity::GetEntityHealth()
{
	return Health;
}

void Entity::SetEntityDamage(int damage)
{
	this->Damage = damage;
}

int Entity::GetEntityDamage()
{
	return Damage;
}

void Entity::SetEntityTakenDamage(int takendamage)
{
	this->TakenDamage = takendamage;
}

int Entity::GetEntityTakenDamage()
{
	return TakenDamage;
}

void Entity::SetEntityMovementSpeed(int movementspeed)
{
	this->MovementSpeed = movementspeed;
}

int Entity::GetEntityMovementSpeed()
{
	return MovementSpeed;
}