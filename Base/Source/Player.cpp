#include "Player.h"

Player::Player(void)
	: hero_inMidAir_Up(false)
	, hero_inMidAir_Down(false)
	, jumpspeed(0)
	, heroAnimationCounter(0)
	, heroAnimationInvert(false)
	, mapOffset_x(0)
	, mapOffset_y(0)
	, mapFineOffset_x(0)
	, mapFineOffset_y(0)
{
}

Player::~Player(void)
{
}

// Initialise this class instance
void Player::Init(void)
{
	m_Position.x = 32;
	m_Position.y = 160;
	SetEntityHealth(10);
	SetEntityDamage(5);
	SetEntityMovementSpeed(2);
}

// Returns true if the player is on ground
bool Player::isOnGround(void)
{
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == false)
		return true;

	return false;
}

// Returns true if the player is jumping upwards
bool Player::isJumpUpwards(void)
{
	if (hero_inMidAir_Up == true && hero_inMidAir_Down == false)
		return true;

	return false;
}

// Returns true if the player is on freefall
bool Player::isFreeFall(void)
{
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == true)
		return true;

	return false;
}

// Set the player's status to free fall mode
void Player::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall == true)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
		jumpspeed = 0;
	}
}

// Set the player to jumping upwards
void Player::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards == true)
	{
		hero_inMidAir_Up = true;
		hero_inMidAir_Down = false;
		jumpspeed = 15;
	}
}

/********************************************************************************
Hero Jump
********************************************************************************/
void Player::HeroJump()
{
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == false)
	{
		hero_inMidAir_Up = true;
		jumpspeed = 10;
	}
}

// Set Jumpspeed of the player
void Player::SetJumpspeed(int jumpspeed)
{
	this->jumpspeed = jumpspeed;
}

// Stop the player's movement
void Player::SetToStop(void)
{
	hero_inMidAir_Up = false;
	hero_inMidAir_Down = false;
	jumpspeed = 0;
}

void Player::MoveLeft(const float timeDiff)
{
	this->m_Position.x += m_Position.x - (int)(5.0f * timeDiff);
}

void Player::MoveRight(const float timeDiff)
{
	this->m_Position += m_Position.x + (int)(5.0f * timeDiff);
}

// Get Jumpspeed of the player
int Player::GetJumpspeed(void)
{
	return jumpspeed;
}

// Get mapOffset_x
int Player::GetMapOffset_x(void)
{
	return mapOffset_x;
}
// Get mapOffset_y
int Player::GetMapOffset_y(void)
{
	return mapOffset_y;
}

// Get mapFineOffset_x
int Player::GetMapFineOffset_x(void)
{
	return mapFineOffset_x;
}
// Get mapFineOffset_y
int Player::GetMapFineOffset_y(void)
{
	return mapFineOffset_y;
}

// Update Jump Upwards
void Player::UpdateJumpUpwards()
{
	m_Position.y -= jumpspeed;
	jumpspeed -= 1;
	if (jumpspeed == 0)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
	}
}

// Update FreeFall
void Player::UpdateFreeFall()
{
	m_Position.y += jumpspeed;
	jumpspeed += 1;
}

// Set Animation Invert status of the player
void Player::SetAnimationInvert(bool heroAnimationInvert)
{
	this->heroAnimationInvert = heroAnimationInvert;
}
// Get Animation Invert status of the player
bool Player::GetAnimationInvert(void)
{
	return heroAnimationInvert;
}

// Constrain the position of the Hero to within the border
void Player::ConstrainPlayer(const int leftBorder, const int rightBorder,
	const int topBorder, const int bottomBorder,
	float timeDiff)
{
	if (m_Position.x < leftBorder)
	{
		m_Position.x = leftBorder;
		mapOffset_x = mapOffset_x - (int)(5.0f * timeDiff);
		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (m_Position.x > rightBorder)
	{
		m_Position.x = rightBorder;
		mapOffset_x = mapOffset_x + (int)(5.0f * timeDiff);
		if (mapOffset_x > 800)	// This must be changed to soft-coded
			mapOffset_x = 800;
	}

	if (m_Position.y < topBorder)
		m_Position.y = topBorder;
	else if (m_Position.y > bottomBorder)
		m_Position.y = bottomBorder;
}

/********************************************************************************
Hero Update
********************************************************************************/
void Player::PlayerUpdate(Map* m_cMap)
{ 

	ConstrainPlayer(25, 750, 25, 575, 1.0f);
}

void Player::CollisionResponse()
{

}