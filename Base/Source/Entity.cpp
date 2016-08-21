#include "Entity.h"

Entity::Entity()
	: mapOffset_x(0)
	, mapOffset_y(0)
	, mapFineOffset_x(0)
	, mapFineOffset_y(0)
	, m_CurrEntityMoveState(FALLING)

{
	//For jumping
	m_bJumping = false;
	JumpVel = 0.f;
	JUMPMAXSPEED = 30.0f;
	JUMPACCEL = 10;
	Gravity = -9.8f;
	MovementSpeed = 1;
    //for abilities
    m_Dashingleft = false;
    m_Dashingright = false;
    isLockMovement = false;
    deBuff_Stunned = false; 
    deBuff_StunTimer = 0.f;
    deBuff_burning = true;
    deBuff_BurningTimer = 0.f;
    deBuff_knockBack = false;
    deBuff_BurnTicks = 0;
    deBuff_Slowed = false;
    deBuff_SlowTimer = 0.f;
    DamagMultiplier = 1;    

    //
	m_MaxCollisionBox.Set(99999, 99999, 0);
	m_MinCollisionBox.Set(-99999, -99999, 0);
}

Entity::~Entity()
{

}

void Entity::SetEntityMaxHealth(int health)
{
	this->MaxHealth = health;
}

int Entity::GetEntityHealth()
{
	return CurrHealth;
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
}

void Entity::EntityJumpUpdate(double dt)
{
	m_PrevPos = m_Position;

	//Factor in gravity
	JumpVel += Gravity * (float)dt;  //VEL = ACCEL * TIME

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
		mapOffset_x = mapOffset_x - (int)(10 * timeDiff);

		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (m_Position.x > rightBorder)
	{
		m_Position.x = rightBorder;
		mapOffset_x = mapOffset_x + (int)(10 * timeDiff);
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
    m_Dashingleft = false;
    m_Dashingright = false;
}

void Entity::Update(double dt, GameObject_Map* Map, Camera camera)
{
	GenerateCollisionBoundary(Map);
	CheckCollisionBoundary();
	//UpdateTileMapCollision(Map);
	ConstrainPlayer(10 + mapOffset_x + mapFineOffset_x, 120 + mapOffset_x + mapFineOffset_x, 25, 580, 1.5, camera);
	mapFineOffset_x = mapOffset_x % Map->GetTileSize();
	//UpdateTileMapCollision(Map);

    AbilityMovementCheck();
    ExecuteAbility(dt);
    DebuffCheckAndApply(dt);

  //  std::cout << Attacks->GetDashLeftStatus() << "LEFT" << std::endl;
   // std::cout << Attacks->GetDashRightStatus() << "RIGHT" << std::endl;

	if (CurrHealth <= 0)
	{
		Death();
	}
}


void Entity::UpdateTileMapCollision(GameObject_Map* Map)
{
	int PlayerPos_X = (int)((mapOffset_x + m_Position.x)) / Map->GetTileSize();
	int PlayerPos_Y = (int)(m_Position.y / Map->GetTileSize());

	GameObject* CheckGameObject_1 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];

	// On ground - Check tiles on the sides
	if (m_CurrEntityMoveState == ON_GROUND)
	{
		// Right
		if (DirectionLeftRight)
		{
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X + 1];
			if ((CheckGameObject_1->GetCollidable() && CheckGameObject_1->GetActive()) || (CheckGameObject_2->GetCollidable()) && CheckGameObject_2->GetActive())
			{
				m_Position = m_PrevPos;
			}

			// here is where it's causing him to fall through the tile when falling down?
			if (!Map->m_GameObjectMap[PlayerPos_Y - 1][PlayerPos_X + 1]->GetCollidable())
			{
				m_CurrEntityMoveState = FALLING;
			}
		}
		// Left
		else
		{
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X - 1];
			if (CheckGameObject_1->GetCollidable() || CheckGameObject_2->GetCollidable())
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
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];
			if ((CheckGameObject_1->GetCollidable() && CheckGameObject_1->GetActive()) || ((CheckGameObject_2->GetCollidable()) && CheckGameObject_2->GetActive()))
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
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];
			if ((CheckGameObject_1->GetCollidable() && CheckGameObject_1->GetActive()) || ((CheckGameObject_2->GetCollidable()) && CheckGameObject_2->GetActive()))
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
		GameObject* CheckGameObject_1 = Map->m_GameObjectMap[PlayerPos_Y + 1][PlayerPos_X];
		// Right
		if (DirectionLeftRight)
		{
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];
			if ((CheckGameObject_1->GetCollidable() && CheckGameObject_1->GetActive()) || ((CheckGameObject_2->GetCollidable()) && CheckGameObject_2->GetActive()))
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
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];
			if ((CheckGameObject_1->GetCollidable() && CheckGameObject_1->GetActive()) || ((CheckGameObject_2->GetCollidable()) && CheckGameObject_2->GetActive()))
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

void Entity::GenerateCollisionBoundary(GameObject_Map* Map)
{
	int PlayerPos_X = (int)(m_Position.x / Map->GetTileSize());
	int PlayerPos_Y = (int)(m_Position.y / Map->GetTileSize());

	GameObject* CheckGameObject_1 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];

	// X-Axis Boundary (Right-Side)
	for (int i = PlayerPos_X; i < Map->GetNumOfTiles_MapWidth(); ++i)
	{
		GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y + 1][i];
		if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive() && i != PlayerPos_X)
		{
			m_MaxCollisionBox.x = (CheckGameObject_2->GetPosition().x) - (Map->GetTileSize());
			break;
		}
		m_MaxCollisionBox.x = (Map->GetNumOfTiles_MapWidth() * Map->GetTileSize()) - (Map->GetTileSize());
	}

	// X-Axis Boundary (Left-Side)
	for (int i = PlayerPos_X; i >= 0; --i)
	{
		GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y + 1][i];
		if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive() && i != PlayerPos_X)
		{
			m_MinCollisionBox.x = (CheckGameObject_2->GetPosition().x) + (Map->GetTileSize()) + 0.5;
			break;
		}
		m_MinCollisionBox.x = (Map->GetTileSize() + 0.5);
	}

	if (m_CurrEntityMoveState != ON_GROUND)
	{
		// Y-Axis Boundary (Top)
		for (int i = PlayerPos_Y; i < Map->GetNumOfTiles_MapHeight(); ++i)
		{
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[i][PlayerPos_X];
			if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive() && i != PlayerPos_Y)
			{
				m_MaxCollisionBox.y = (CheckGameObject_2->GetPosition().y) - (Map->GetTileSize());
				break;
			}
			m_MaxCollisionBox.y = Map->GetNumOfTiles_MapHeight() * Map->GetTileSize() - (Map->GetTileSize());
		}

		// Y-Axis Boundary (Bottom)
		for (int i = PlayerPos_Y; i >= 0; --i)
		{
			GameObject* CheckGameObject_2 = Map->m_GameObjectMap[i][PlayerPos_X];
			GameObject* CheckGameObject_3 = Map->m_GameObjectMap[i][PlayerPos_X+1];
			if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive())
			{
				m_MinCollisionBox.y = (CheckGameObject_2->GetPosition().y) + (Map->GetTileSize());

				// Top-Left Hotfix
				// if (CheckGameObject_3)

				break;
			}
			m_MinCollisionBox.y = (0.5 * Map->GetTileSize());
		}
	}

	GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y - 1][PlayerPos_X];
	if (!CheckGameObject_1->GetCollidable() && !CheckGameObject_1->GetActive())
	{
		m_CurrEntityMoveState = FALLING;
	}

}

void Entity::CheckCollisionBoundary()
{
	if (m_Position.x < m_MinCollisionBox.x)
	{
        CollisionResponse();
		m_Position.x = m_MinCollisionBox.x;
		JumpVel = 0;
	}

	if (m_Position.x > m_MaxCollisionBox.x)
	{
        CollisionResponse();
		m_Position.x = m_MaxCollisionBox.x;
		JumpVel = 0;
	}

	if (m_Position.y < m_MinCollisionBox.y)
	{
		m_Position.y = m_MinCollisionBox.y;
		JumpVel = 0;
		m_CurrEntityMoveState = ON_GROUND;
	}

	if (m_Position.y > m_MaxCollisionBox.y)
	{
		m_Position.y = m_MaxCollisionBox.y;
		m_CurrEntityMoveState = FALLING;
	}


}

void Entity::AbilityMovementCheck()
{
    if (Attacks->GetDashLeftStatus())
    {
        isLockMovement = true;
        DashDestinationX = m_Position.x - 20.f;
        m_PrevState = m_CurrEntityMoveState;
        m_Dashingleft = true;
        Attacks->SetDashStatus(false, false);


    }
    if (Attacks->GetDashRightStatus())
    {
        isLockMovement = true;
        DashDestinationX = m_Position.x + 20.f;
        m_PrevState = m_CurrEntityMoveState;
        m_Dashingright = true;
        Attacks->SetDashStatus(false, false);
    }
}

void Entity::ExecuteAbility(double dt)
{
    if (m_Dashingright == true)
    {
        if (m_Position.x < DashDestinationX)
        {
            m_Position.x += 75 * (float)dt;
        }
        else
        {
            m_Dashingright = false;
        }
    }
    else if (m_Dashingleft == true)
    {
        if (m_Position.x > DashDestinationX)
        {
            m_Position.x -= 75 * (float)dt;
        }
        else
        {
            m_Dashingleft = false;
        }
    }
    else
    {
        isLockMovement = false;
    }

    if (Attacks->GetSteamStatus())
    {
        MovementSpeed = 3;
    }
    else
    {
        MovementSpeed = 1;
    }
 
      
}

bool Entity::GetControlLock()
{
    return isLockMovement;
}

void Entity::DebuffCheckAndApply(double dt)
{
    if (deBuff_Stunned)
    {
        isLockMovement = true;
        deBuff_StunTimer += 2 * (float)dt;
        if (deBuff_StunTimer >= 10.f)
        {
            deBuff_Stunned = false;
            isLockMovement = false;
            deBuff_StunTimer = 0.f;
        }
    }
    if (deBuff_burning)
    {
        deBuff_BurningTimer += (float)dt;
        if (deBuff_BurningTimer >= 1)
        {
            CurrHealth -= MaxHealth * 0.02;
            //std::cout << "burn " <<CurrHealth << std::endl;
            deBuff_BurningTimer = 0.f;
            deBuff_BurnTicks += 1;
        }
            
        if (deBuff_BurnTicks == 5)
        {
            deBuff_burning = false;
            deBuff_BurningTimer = 0.f;
            deBuff_BurnTicks = 0;
        }
    }
    if (deBuff_knockBack)
    {

    }
    if (deBuff_Slowed)
    {
        MovementSpeed = 0.5;
        deBuff_SlowTimer += 2 * (float)dt;
        if (deBuff_SlowTimer >= 10.f)
        {
            deBuff_Slowed = false;
            MovementSpeed = 1;
            deBuff_SlowTimer = 0.f;
        }
    }
    if (Application::IsKeyPressed('B'))
    {
        deBuff_Slowed = true;
    }
}

void Entity::TakeDamage(int input)
{
    CurrHealth -= input * DamagMultiplier;
}