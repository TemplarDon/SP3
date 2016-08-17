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
}
void Projectile::projectileInit(bool Direction, Vector3 m_Position,float bulletSpeed,int damage,float time, ELEMENT element)
{
	this->Direction = Direction;
	this->m_Position = m_Position;
	this->speedBullet = bulletSpeed;
	this->damage = damage;
	this->lifeTime = time;
	this->m_CurrElement = element;
	m_Normal.Set(0, 1, 0);
}

Projectile::~Projectile()
{

}

void Projectile::projectileUpdate(double dt)
{
	if (Direction)
		this->m_Position.x += speedBullet*dt;
	else if (!Direction)
		this->m_Position -= speedBullet*dt;

    lifeTime -= dt * 5;
    if (lifeTime < 0)
    {
        m_Active = false;
    }
}

void Projectile::Update(double dt)
{
    if (Direction)
        this->m_Position.x += speedBullet*dt;
    else if (!Direction)
        this->m_Position -= speedBullet*dt;

    lifeTime -= dt;
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