#include "Projectile.h"
#include "GameObjectManager.h"



Projectile::Projectile()
{
	Direction = true;
	m_Position.Set(0, 0, 0);
	m_Velocity.Set(0, 0, 0);
	damage = 0;
	lifeTime = 0;
	m_Normal.Set(0, 1, 0);
}
void Projectile::projectileInit(bool Direction, Vector3 m_Position, Vector3 m_Velocity,int damage,float time)
{
	this->Direction = Direction;
	this->m_Position = m_Position;
	this->m_Velocity = m_Velocity;
	this->damage = damage;
	this->lifeTime = time;
	m_Normal.Set(0, 1, 0);
}

Projectile::~Projectile()
{

}

void Projectile::projectileUpdate(double dt)
{
	if (Direction)
		this->m_Position += m_Velocity*dt;
	else if (!Direction)
		this->m_Position -= m_Velocity*dt;
}
void Projectile::setDamage(int damage)
{
	this->damage = damage;
}
int	Projectile::getDamage()
{
	return damage;
}

void Projectile::setVelocity(Vector3 Velocity)
{
	this->m_Velocity.Set(Velocity.x, Velocity.y, Velocity.z);
}
Vector3 Projectile::getVelocity()
{
	return m_Velocity;
}

void Projectile::setPosition(Vector3 Position)
{
	this->m_Position.Set(Position.x, Position.y, Position.z);
}
Vector3 Projectile::getPosition()
{
	return m_Position;
}

void Projectile::setDirection(bool Direction)
{
	this->Direction = Direction;
}
bool Projectile::getDirection()
{
	return Direction;
}

void  Projectile::setLifetime(float lifeTime)
{
	this->lifeTime = lifeTime;
}
float  Projectile::getLifetime()
{
	return lifeTime;
}