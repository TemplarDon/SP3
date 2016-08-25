#include "Entity.h"

#include "GameObjectManager.h"


#include "GL\glew.h"
#include "LoadTGA.h"

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
    isLockMovement = false;
    deBuff_burning = false;
    deBuff_BurningTimer = 0.f;
    deBuff_BurnTicks = 0;
    deBuff_Slowed = false;
	debuff_Edible = false;
    deBuff_SlowTimer = 0.f;
    DamagMultiplier = 1;    

	m_MaxCollisionBox.Set(99999, 99999, 0);
	m_MinCollisionBox.Set(-99999, -99999, 0);

	// Initialise Levels
	//m_ElementsPercentageMap[FIRE] = 10.f;
	//m_ElementsPercentageMap[WATER] = 10.f;
	//m_ElementsPercentageMap[EARTH] = 10.f;
	SetElementPercentage(FIRE, 10.f);
	SetElementPercentage(WATER, 8.f);
	SetElementPercentage(EARTH, 6.f);

	//m_ElementsLevelMap[FIRE] = 1;
	//m_ElementsLevelMap[WATER] = 1;
	//m_ElementsLevelMap[EARTH] = 1;
	SetElementLevel(FIRE, 1);
	SetElementLevel(WATER, 1);
	SetElementLevel(EARTH, 1);
}

Entity::~Entity()
{

}

void Entity::SetEntityMaxHealth(int health)
{
	this->MaxHealth = health;
    if (!isEnemyEntity)
    {
        CurrSheild = health;
        MaxSheild = health;
    }
    else
    {
        CurrSheild = 0.f;
        MaxSheild = 0.f;
    }
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

	//if (Move_Left)
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
	this->m_Position.y += JumpVel * 0.1f; //DIST = VEL * TIME

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
	const int bottomBorder, const int topBorder,
	float timeDiff, Camera camera)	
{
	if (m_Position.x < leftBorder)
	{
		m_Position.x = (float)leftBorder;
		mapOffset_x = mapOffset_x - (int)(10 * timeDiff);

		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (m_Position.x > rightBorder)
	{
        m_Position.x = (float)rightBorder;
		mapOffset_x = mapOffset_x + (int)(10 * timeDiff);
		if (mapOffset_x > 800)	// This must be changed to soft-coded
			mapOffset_x = 800;
	}

	if (m_Position.y > topBorder)
	{
        m_Position.y = (float)topBorder;
		mapOffset_y = mapOffset_y + (int)(2 * timeDiff);
	}
	else if (m_Position.y < bottomBorder)
	{
        m_Position.y = (float)bottomBorder;
		mapOffset_y = mapOffset_y - (int)(2 * timeDiff);
	}

}



void Entity::CollisionResponse(GameObject* OtherGo)
{
	//Projectile* tempProj;
	//tempProj = dynamic_cast<Projectile*>(OtherGo);

	//if (OtherGo->GetObjectType() == PROJECTILE)
	//{
	//	if (this->m_ObjectType == ENEMY && tempProj->GetElement() == MISC && tempProj->getIsHostileProjectile() == false)
	//	{
	//		this->debuff_Edible = true;
	//	}
	//}
	//if (this->GetObjectType() == PLAYER)
	//{
	//	if (OtherGo->GetObjectType() == PROJECTILE&& tempProj->getIsHostileProjectile() == true)
	//	{

 //           if (tempProj->GetElement() == FIRE || tempProj->GetElement() == FIRE_2)
	//		{
	//			if (m_CurrElement == WATER)
	//				DamagMultiplier = 0.5;
	//			if (m_CurrElement == FIRE)
	//				DamagMultiplier = 1;
	//			if (m_CurrElement == EARTH)
	//				DamagMultiplier = 1.5;
	//		}
 //           if (tempProj->GetElement() == WATER)
	//		{
	//			if (m_CurrElement == WATER)
	//				DamagMultiplier = 1;
	//			if (m_CurrElement == FIRE)
	//				DamagMultiplier = 1.5;
	//			if (m_CurrElement == EARTH)
	//				DamagMultiplier = 0.5;
	//		}
 //           if (tempProj->GetElement() == EARTH)
	//		{
	//			if (m_CurrElement == WATER)
	//				DamagMultiplier = 1.5;
	//			if (m_CurrElement == FIRE)
	//				DamagMultiplier = 0.5;
	//			if (m_CurrElement == EARTH)
	//				DamagMultiplier == 1;
	//		}	
	//		//fire 2 burn
	//		if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == FIRE_2)
	//		{
	//			if (deBuff_burning = true)
	//			{
	//				deBuff_BurningTimer = 0.f;
	//			}
	//			else
	//			{
	//				deBuff_burning = true;
	//			}
	//		}
	//		//Water
 //           if (dynamic_cast<Projectile*>(OtherGo)->GetElement() == WATER || dynamic_cast<Projectile*>(OtherGo)->GetElement() == WATER_2)
	//		{
	//			if (deBuff_Slowed)
	//			{
	//				deBuff_SlowTimer = 0.f;
	//			}
	//			else
	//			{
	//				deBuff_Slowed = true;
	//			}
	//		}
 //			TakeDamage(tempProj->getDamage());
	//		OtherGo->SetActive(false);
	//	}
	//}
   
}

void Entity::Update(double dt, GameObject_Map* Map, Camera camera)
{
    interDT = dt;
	GenerateCollisionBoundary(Map);
	CheckCollisionBoundary();
	ConstrainPlayer(15 + mapOffset_x + mapFineOffset_x, 120 + mapOffset_x + mapFineOffset_x, 25 + mapOffset_y + mapFineOffset_y, 60 + mapOffset_y + mapFineOffset_y, 1.5, camera);
	mapFineOffset_x = mapOffset_x % Map->GetTileSize();

    ExecuteAbility(dt);
    DebuffCheckAndApply(dt);

    //Sheilds
    if (!isEnemyEntity)
    {
        if (!SheildRegen)
        {
            SheildRegenTimer += (float)dt;
            if (SheildRegenTimer >= 4)
            {
                SheildRegen = true;
                SheildRegenTimer = 0.f;
            }
        }
        if (SheildRegen)
        {
            CurrSheild += 50 * (float)dt;
            if (CurrSheild > MaxSheild)
            {
                CurrSheild = MaxSheild;
            }
        }
    }
    
	if (CurrHealth <= 0)
	{
		Death();
	}
}

float Entity::GetCurrShield()
{
	return CurrSheild;
}

void Entity::GenerateCollisionBoundary(GameObject_Map* Map)
{
	int PlayerPos_X = (int)(m_Position.x / Map->GetTileSize());
	int PlayerPos_Y = (int)(m_Position.y / Map->GetTileSize());

	GameObject* CheckGameObject_1 = Map->m_GameObjectMap[PlayerPos_Y][PlayerPos_X];

	// X-Axis Boundary (Right-Side)
	for (int i = PlayerPos_X; i < Map->GetNumOfTiles_MapWidth() - 1; ++i)
	{
		GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y /*+ 1*/][i + 1];
		if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive() && i != PlayerPos_X)
		{
			m_MaxCollisionBox.x = (CheckGameObject_2->GetPosition().x) - (Map->GetTileSize()) - 0.5;
			break;
		}
		m_MaxCollisionBox.x = (Map->GetNumOfTiles_MapWidth() * Map->GetTileSize()) - (Map->GetTileSize());
	}

	// X-Axis Boundary (Left-Side)
	for (int i = PlayerPos_X; i >= 0; --i)
	{
		GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y /*+ 1*/][i];
		if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive() && i != PlayerPos_X)
		{
			m_MinCollisionBox.x = (CheckGameObject_2->GetPosition().x) + (Map->GetTileSize()) + 0.5;
			break;
		}
		m_MinCollisionBox.x = (Map->GetTileSize() + 0.5);
	}


	// Y-Axis Boundary (Top)
	for (int i = PlayerPos_Y; i < Map->GetNumOfTiles_MapHeight(); ++i)
	{
		GameObject* CheckGameObject_2 = Map->m_GameObjectMap[i][PlayerPos_X];
		GameObject* CheckGameObject_3 = Map->m_GameObjectMap[i][PlayerPos_X - 1];
		if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive() && i != PlayerPos_Y)
		{
			m_MaxCollisionBox.y = (CheckGameObject_2->GetPosition().y) - (Map->GetTileSize()) - 0.5;
			break;
		}
		m_MaxCollisionBox.y = Map->GetNumOfTiles_MapHeight() * Map->GetTileSize() - (Map->GetTileSize());
	}

	// Y-Axis Boundary (Bottom)
	for (int i = PlayerPos_Y; i >= 0; --i)
	{
		GameObject* CheckGameObject_2 = Map->m_GameObjectMap[i][PlayerPos_X];
		GameObject* CheckGameObject_3 = Map->m_GameObjectMap[i][PlayerPos_X + 1];
		GameObject* CheckGameObject_4 = Map->m_GameObjectMap[i][PlayerPos_X - 1];

		if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive())
		{
			m_MinCollisionBox.y = (CheckGameObject_2->GetPosition().y) + (Map->GetTileSize()) + 0.1;
			break;
		}
		else if(!CheckGameObject_2->GetCollidable() && !CheckGameObject_2->GetActive())
		{
			if (CheckGameObject_3->GetCollidable() && CheckGameObject_3->GetActive())
			{
				m_MinCollisionBox.y = (CheckGameObject_3->GetPosition().y) + (Map->GetTileSize()) + 0.1;
				break;
			}
		}

		m_MinCollisionBox.y = (0.5 * Map->GetTileSize());

	}
	

	GameObject* CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y - 1][PlayerPos_X];
	GameObject* CheckGameObject_3 = Map->m_GameObjectMap[PlayerPos_Y - 1][PlayerPos_X + 1];
	GameObject* CheckGameObject_4 = Map->m_GameObjectMap[PlayerPos_Y - 1][PlayerPos_X - 1];
	if ( (!CheckGameObject_2->GetCollidable() && !CheckGameObject_2->GetActive() && !CheckGameObject_3->GetCollidable() && !CheckGameObject_3->GetActive()) ||
	   (!CheckGameObject_2->GetCollidable() && !CheckGameObject_2->GetActive() && !CheckGameObject_4->GetCollidable() && !CheckGameObject_4->GetActive()) )
	{
		m_CurrEntityMoveState = FALLING;
	}

	CheckGameObject_2 = Map->m_GameObjectMap[PlayerPos_Y + 1][PlayerPos_X];
	if (CheckGameObject_2->GetCollidable() && CheckGameObject_2->GetActive())
	{
		JumpVel = 0;
		m_CurrEntityMoveState = FALLING;
	}
}

void Entity::CheckCollisionBoundary()
{
	if (m_Position.x < m_MinCollisionBox.x)
	{
		m_Position.x = m_MinCollisionBox.x;
		JumpVel = 0;
        
	}

	if (m_Position.x > m_MaxCollisionBox.x)
	{
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


void Entity::ExecuteAbility(double dt)
{
  
      
}

bool Entity::GetControlLock()
{
    return isLockMovement;
}

void Entity::DebuffCheckAndApply(double dt)
{
    if (deBuff_burning)
    {
        deBuff_BurningTimer += (float)dt;
        if (deBuff_BurningTimer >= 1)
        {
            CurrHealth -= MaxHealth * 0.03f;
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
	if (debuff_Edible)
	{
		/*isLockMovement = true;
		deBuff_StunTimer += 2 * (float)dt;

		this->SetMoveState(EDIBLE);
		if (deBuff_StunTimer >= 10.f)
		{
			deBuff_Stunned = false;
			isLockMovement = false;
			deBuff_StunTimer = 0.f;
		}*/
	}
    if (Application::IsKeyPressed('B'))
    {
        deBuff_burning = true;
    }
}

void Entity::TakeDamage(int input)
{
    input = input * DamagMultiplier;
    float DmgToHealth;
    float DmgToSheild;
    SheildRegen = false;
    if (CurrSheild > 0)
    {
        if (input <= CurrSheild)
        {
            DmgToHealth = 0.f;
            DmgToSheild = input;
        }
        else
        {
            DmgToHealth = input - CurrSheild;
            DmgToSheild = CurrSheild;
        }
    }
    else
    {
        DmgToHealth = input;
        DmgToSheild = 0;
    }
    CurrSheild -= DmgToSheild;
    CurrHealth -= DmgToHealth;
    
}


void Entity::setSpriteVector(Mesh* mesh, int startFrame, int endFrame, int repeat, float time, bool active)
{
	SpriteAnimation* sa = static_cast<SpriteAnimation*>(mesh);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(startFrame,endFrame,repeat, time, active);
	}
	AnimationSpriteList.push_back(sa);
}
std::vector<SpriteAnimation*> Entity::getSpriteVector()
{
	return AnimationSpriteList;
}

void Entity::setMeshVector(Mesh* mesh, std::string Name, const char* targaName, int numRow, int numCol)
{
	mesh = MeshBuilder::GenerateSpriteAnimation(Name, numRow, numCol);
	mesh->textureID = LoadTGA(targaName);
	AnimationMeshList.push_back(mesh);
}
std::vector<Mesh*>  Entity::getMeshVector()
{
	return AnimationMeshList;
}

void Entity::GainExp(ELEMENT ElementToGain, float Amount)
{
	m_ElementsPercentageMap[ElementToGain] += Amount;

	if (m_ElementsPercentageMap[ElementToGain] >= 100)
	{
		LevelUp(ElementToGain);
	}
}

void Entity::LevelUp(ELEMENT ElementToLevel)
{
	m_ElementsLevelMap[ElementToLevel] += 1;

	switch (ElementToLevel)
	{
	case FIRE:
	{
		this->Damage += 2;
		break;
	}
	case WATER:
	{
		this->MaxHealth += 5;
		break;
	}
	case EARTH:
	{
		this->MaxSheild += 5;
		break;
	}
	}
}

void Entity::SetElementPercentage(ELEMENT ElementType, float percentage)
{
	//float i = m_ElementsPercentageMap[FIRE];
	//m_ElementsPercentageMap[ElementType] = percentage;
	//this->Percentage = percentage;

	if (ElementType == FIRE)
	{
		this->FirePercentage = percentage;
	}
	else if (ElementType == WATER)
	{
		this->WaterPercentage = percentage;
	}
	else if (ElementType == EARTH)
	{
		this->EarthPercentage = percentage;
	}
}

float Entity::GetElementPercentage(ELEMENT ELementType)
{
	if (ELementType == FIRE)
	{
		return FirePercentage;
	}
	else if (ELementType == WATER)
	{
		return WaterPercentage;
	}
	else if (ELementType == EARTH)
	{
		return EarthPercentage;
	}
}

void Entity::SetElementLevel(ELEMENT ElementType, float level)
{
	if (ElementType == FIRE)
	{
		this->FireLevel = level;
	}
	else if (ElementType == WATER)
	{
		this->WaterLevel = level;
	}
	else if (ElementType == EARTH)
	{
		this->EarthLevel = level;
	}
}

int Entity::GetElementLevel(ELEMENT ELementType)
{
	if (ELementType == FIRE)
	{
		return FireLevel;
	}
	else if (ELementType == WATER)
	{
		return WaterLevel;
	}
	else if (ELementType == EARTH)
	{
		return EarthLevel;
	}
}