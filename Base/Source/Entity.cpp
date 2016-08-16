#include "Entity.h"

Entity::Entity()
	: mapOffset_x(0)
	, mapOffset_y(0)
	, mapFineOffset_x(0)
	, mapFineOffset_y(0)
	, m_CurrEntityMoveState(ON_GROUND)

{
	//For jumping
	m_bJumping = false;
	JumpVel = 0.f;
	JUMPMAXSPEED = 30.0f;
	JUMPACCEL = 10;
	Gravity = -9.8f;
	MovementSpeed = 1;
	m_PrevPos.Set(120, 0, 0);
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

void Entity::SetEntityMovementSpeed(float movementspeed)
{
	this->MovementSpeed = movementspeed;
}

float Entity::GetEntityMovementSpeed()
{
	return MovementSpeed;
}


bool Entity::GetLeftRight()
{
	return DirectionLeftRight;
}

void Entity::SetLeftRight(bool input)
{
	this->DirectionLeftRight = input;
}

void Entity::MoveLeft(const float timeDiff)
{
	m_PrevPos = m_Position;

	if (Move_Left)
	{
		//SetLeftRight(false);
		DirectionLeftRight = false;
		Move_Left = false;
		this->m_Position.x -= (float)(10.0f * timeDiff * this->MovementSpeed);
	}
}

void Entity::MoveRight(const float timeDiff)
{
	m_PrevPos = m_Position;

	if (Move_Right)
	{
		//SetLeftRight(true);
		DirectionLeftRight = true;
		Move_Right = true;
		this->m_Position.x += (float)(10.0f * timeDiff * this->GetEntityMovementSpeed());
	}
}

bool Entity::GetMoving_Left()
{
	return Move_Left;
}

void Entity::SetMoving_Left(bool input)
{
	this->Move_Left = input;
}

bool Entity::GetMoving_Right()
{
	return Move_Right;
}

void Entity::SetMove_Right(bool input)
{
	this->Move_Right = input;
}

ENTITY_MOVE_STATE Entity::GetMoveState()
{
	return m_CurrEntityMoveState;
}

void Entity::SetMoveState(ENTITY_MOVE_STATE SetState)
{
	m_CurrEntityMoveState = SetState;
}


// Jump
void Entity::UpdateJump(double dt)
{
	m_PrevPos = m_Position;

	m_CurrEntityMoveState = JUMPING;

	//Calculate the jump velocity
	JumpVel = JUMPACCEL;

	JumpVel += Gravity * dt;  //VEL = ACCEL * TIME

	this->m_Position.y += JumpVel * 0.1; //DIST = VEL * TIME
}

void Entity::EntityJumpUpdate(double dt)
{
	m_PrevPos = m_Position;

	//Factor in gravity
	JumpVel += Gravity * dt;  //VEL = ACCEL * TIME

	//Update the camera and target position
	this->m_Position.y += JumpVel * 0.1; //DIST = VEL * TIME

	if (JumpVel < 0)
	{	
		m_CurrEntityMoveState = FALLING;
	}
	
}

bool Entity::GetJump()
{
	return m_bJumping;
}

// Get mapOffset_x
int Entity::GetMapOffset_x()
{
	return mapOffset_x;
}

// Set mapOffset_x
void Entity::SetMapOffset_x(int mapOffset_x)
{
	this->mapOffset_x = mapOffset_x;
}

// Get mapOffset_y
int Entity::GetMapOffset_y()
{
	return mapOffset_y;
}

// Set mapOffset_y
void Entity::SetMapOffset_y(int mapOffset_y)
{
	this->mapOffset_y = mapFineOffset_y;
}

// Get mapFineOffset_X
int Entity::GetMapFineOffset_x()
{
	return mapFineOffset_x;
}

// Set mapOffset_X
void Entity::SetMapFineOffset_x(int mapFineOffset_X)
{
	this->mapFineOffset_x = mapFineOffset_X;
}

// Get mapFineOffset_Y
int Entity::GetMapFineOffset_y()
{
	return mapFineOffset_y;
}

// Set mapFineOffset_Y
void Entity::SetMapFineOffset_y(int mapFineOffset_y)
{
	this->mapFineOffset_y = mapFineOffset_y;
}

// Constrain the position of the Entity to within the border
void Entity::ConstrainPlayer(const int leftBorder, const int rightBorder,
	const int topBorder, const int bottomBorder,
	float timeDiff, Camera camera)	
{
	if (m_Position.x < leftBorder)
	{
		m_Position.x = leftBorder;
		mapOffset_x = mapOffset_x - (100 * timeDiff);
		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (m_Position.x > rightBorder)
	{
		m_Position.x = rightBorder;
		mapOffset_x = mapOffset_x + (100 * timeDiff);
		if (mapOffset_x > 800)	// This must be changed to soft-coded
			mapOffset_x = 800;
	}

	if (m_Position.y < topBorder)
		m_Position.y = topBorder;
	else if (m_Position.y > bottomBorder)
		m_Position.y = bottomBorder;
}

void Entity::CollisionResponse()
{

}

void Entity::Update(double dt, GameObject_Map* Map, Camera camera)
{
	ConstrainPlayer(5 + mapOffset_x + mapFineOffset_x, 150 + mapOffset_x + mapFineOffset_x, 25, 580, dt, camera);
	UpdateTileMapCollision(Map);
}

void Entity::UpdateTileMapCollision(GameObject_Map* Map)
{
	int PlayerPos_X = (int)((mapOffset_x + m_Position.x)) / Map->GetTileSize();
	int PlayerPos_Y = (int)(m_Position.y / Map->GetTileSize());

	// On ground - Check tiles on the sides
	if (m_CurrEntityMoveState == ON_GROUND)
	{
		// Right
		if (DirectionLeftRight)
		{
			if (Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X]->GetCollidable() || Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X + 1]->GetCollidable())
			{
				m_Position = m_PrevPos;
			}

			if (!Map->m_GameObjectMap[PlayerPos_Y - 1][PlayerPos_X + 1]->GetCollidable())
			{
				m_CurrEntityMoveState = FALLING;
			}
		}
		// Left
		else
		{
			if (Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X]->GetCollidable() || Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X - 1]->GetCollidable())
			{
				m_Position = m_PrevPos;
			}

			if (!Map->m_GameObjectMap[PlayerPos_Y - 1][PlayerPos_X - 1]->GetCollidable())
			{
				m_CurrEntityMoveState = FALLING;
			}
		}
	}
	// Falling - Check tiles below
	else if (m_CurrEntityMoveState == FALLING)
	{
		// Right
		if (DirectionLeftRight)
		{
			if (Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X]->GetCollidable() || Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X + 1]->GetCollidable())
			{
				m_Position = m_PrevPos;
				m_bJumping = false;
				m_CurrEntityMoveState = ON_GROUND;
				JumpVel = 0;
			}
		}
		// Left
		else
		{
			if (Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X]->GetCollidable() || Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X - 1]->GetCollidable())
			{
				m_Position = m_PrevPos;
				m_bJumping = false;
				m_CurrEntityMoveState = ON_GROUND;
				JumpVel = 0;
			}
		}
	}
	// Jumping - Check tiles above
	else if (m_CurrEntityMoveState == JUMPING)
	{
		// Right
		if (DirectionLeftRight)
		{
			if (Map->m_GameObjectMap[PlayerPos_Y + 1][PlayerPos_X]->GetCollidable() || Map->m_GameObjectMap[PlayerPos_Y + 1][PlayerPos_X + 1]->GetCollidable())
			{
				m_Position = m_PrevPos;
				m_bJumping = false;
				m_CurrEntityMoveState = FALLING;
				JumpVel = 0;
			}
		}
		// Left
		else
		{
			if (Map->m_GameObjectMap[PlayerPos_Y + 1][PlayerPos_X]->GetCollidable() || Map->m_GameObjectMap[PlayerPos_Y + 1][PlayerPos_X - 1]->GetCollidable())
			{
				m_Position = m_PrevPos;
				m_bJumping = false;
				m_CurrEntityMoveState = FALLING;
				JumpVel = 0;
			}
		}
	}

	mapFineOffset_x = mapOffset_x % Map->GetTileSize();
}