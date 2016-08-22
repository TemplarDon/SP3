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
	}
	else
	{
		rotation =180-rotation;
		m_Velocity.Set(m_Position.x * cos(Math::DegreeToRadian(rotation)), m_Position.y *sin(Math::DegreeToRadian(rotation)), 1);
	}
	
}
Vector3  Projectile::getVelocity()
{
	return m_Velocity;
}
void Projectile::Update(double dt)
{
	lifeTime -= (float)dt;
	if (lifeTime < 0)
	{
		m_Active = false;
	}

	UpdatePhysics(dt);
}


void Projectile::UpdatePhysics(double dt, Vector3 Gravity)
{
	if (m_CurrElement == FIRE)
	{
		Vector3 dv = Gravity * dt; // Eqn 1 (Vec3 = Vec3 * float)
		this->m_Velocity += (dv);
	}

	Vector3 ds = this->m_Velocity * dt; // Eqn 2 (Vec3 = Vec3 * float)
	this->m_Position += (ds);
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

void Projectile::CollisionResponse(GameObject* OtherGo)
{
	Vector3 u1 = this->m_Velocity;
	Vector3 N = (OtherGo->GetPosition() - this->m_Position).Normalized();
	Vector3 u1N = u1.Dot(N) * N;
	
	this->m_Velocity = (u1 - 2 * (u1N));
}
void Projectile::setIsHostileProjectile(bool isHostileProjectile)
{
	this->isHostileProjectile = isHostileProjectile;
}
bool Projectile::getIsHostileProjectile()
{
	return isHostileProjectile;
}