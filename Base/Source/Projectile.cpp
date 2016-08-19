#include "Projectile.h"
#include "GameObjectManager.h"



Projectile::Projectile()
{
	Direction = true;
	m_Position.Set(0, 0, 0);
	damage = 0;
	lifeTime = 0;
	speedBullet = 0;
	m_Normal.Set(0, 1, 0);
	rotation = 0;
}
void Projectile::projectileInit(bool Direction, Vector3 m_Position, float bulletSpeed, int damage, float time, ELEMENT element, bool enemypewpew,float rotation)
{
	this->Direction = Direction;
	this->m_Position = m_Position;
	this->speedBullet = bulletSpeed;
	this->damage = damage;
	this->lifeTime = time;
	this->m_CurrElement = element;
    this->isHostileProjectile = enemypewpew;
	m_Normal.Set(0, 1, 0);
	this->rotation = rotation;
	setVelocity();
}

Projectile::~Projectile()
{

}

void Projectile::projectileUpdate(double dt)
{
	/*static Vector3 shootVec(0, 0, 1);
	if (Direction != true)
	{
		this->rotation += 90;
	}
	shootVec.Set(m_Position.x * cos(Math::DegreeToRadian(rotation)), m_Position.y *sin(Math::DegreeToRadian(rotation)), 1);
	m_Position += shootVec.Normalize();
    lifeTime -= (float)dt * 5;
	if (lifeTime < 0)
	{
		m_Active = false;
	}*/
}
void  Projectile::setVelocity()
{
	if (Direction==true)
	{
		m_Velocity.Set(m_Position.x * cos(Math::DegreeToRadian(rotation)), m_Position.y *sin(Math::DegreeToRadian(rotation)), 1);
		m_Velocity.Normalize();
	}
	else
	{
		rotation += 90;
		m_Velocity.Set(m_Position.x * cos(Math::DegreeToRadian(rotation)), m_Position.y *sin(Math::DegreeToRadian(rotation)), 1);
		m_Velocity.Normalize();
	}
	
}
Vector3  Projectile::getVelocity()
{
	return m_Velocity;
}
void Projectile::Update(double dt)
{
	if (Direction != true&& rotation<90)
	{
		rotation += 180;
		if (rotation >= 180)
		{
			rotation -= 90;
		}
	}
	
	m_Position += m_Velocity;
	

	lifeTime -= (float)dt;
	if (lifeTime < 0)
	{
		m_Active = false;
	}
}
void Projectile::setDamage(int damage)
{
	this->damage = damage;
}
int	Projectile::getDamage()
{
	return damage;
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

void Projectile::setRotation(float rotation)
{
	this->rotation = rotation;
}
float Projectile::getRotation()
{
	return rotation;
}