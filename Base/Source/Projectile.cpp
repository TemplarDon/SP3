#include "Projectile.h"
#include "GameObjectManager.h"




Projectile::Projectile(bool Direction, Vector3 m_Position, Vector3 m_Velocity)
{
	this->Direction = Direction;
	this->m_Position = m_Position;
	this->m_Velocity = m_Velocity;
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


