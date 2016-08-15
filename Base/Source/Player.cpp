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
	PlayerPosition.x = 0;
	PlayerPosition.y = 0;
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

// Set position x of the player
void Player::SetPos_x(int pos_x)
{
	PlayerPosition.x = pos_x;
}

// Set position y of the player
void Player::SetPos_y(int pos_y)
{
	PlayerPosition.y = pos_y;
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

/********************************************************************************
Hero Move Up Down
********************************************************************************/
void Player::MoveUpDown(const bool mode, const float timeDiff)
{
	if (mode)
	{
		PlayerPosition.y = PlayerPosition.y + (int)(5.0f * timeDiff);
	}
	else
	{
		PlayerPosition.y = PlayerPosition.y - (int)(5.0f * timeDiff);
	}
}

/********************************************************************************
Hero Move Left Right
********************************************************************************/
void Player::MoveLeftRight(const bool mode, const float timeDiff)
{
	if (mode)
	{
		PlayerPosition.x = PlayerPosition.x - (int)(5.0f * timeDiff);
		heroAnimationInvert = true;
		heroAnimationCounter--;
		if (heroAnimationCounter == 0)
			heroAnimationCounter = 3;
	}
	else
	{
		PlayerPosition.x = PlayerPosition.x + (int)(5.0f * timeDiff);
		heroAnimationInvert = false;
		heroAnimationCounter++;
		if (heroAnimationCounter>3)
			heroAnimationCounter = 0;
	}
}


// Get position x of the player
int Player::GetPos_x(void)
{
	return PlayerPosition.x;
}

// Get position y of the player
int Player::GetPos_y(void)
{
	return PlayerPosition.y;
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
	PlayerPosition.y -= jumpspeed;
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
	PlayerPosition.y += jumpspeed;
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
void Player::ConstrainHero(const int leftBorder, const int rightBorder,
	const int topBorder, const int bottomBorder,
	float timeDiff)
{
	if (PlayerPosition.x < leftBorder)
	{
		PlayerPosition.x = leftBorder;
		mapOffset_x = mapOffset_x - (int)(5.0f * timeDiff);
		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (PlayerPosition.x > rightBorder)
	{
		PlayerPosition.x = rightBorder;
		mapOffset_x = mapOffset_x + (int)(5.0f * timeDiff);
		if (mapOffset_x > 800)	// This must be changed to soft-coded
			mapOffset_x = 800;
	}

	if (PlayerPosition.y < topBorder)
		PlayerPosition.y = topBorder;
	else if (PlayerPosition.y > bottomBorder)
		PlayerPosition.y = bottomBorder;
}

/********************************************************************************
Hero Update
********************************************************************************/
void Player::HeroUpdate(Map* m_cMap)
{ 
	ConstrainHero(25, 750, 25, 575, 1.0f);
}

void Player::CollisionResponse()
{

}