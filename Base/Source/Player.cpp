#include "Player.h"

Player::Player(void)
	: hero_inMidAir_Up(false)
	, hero_inMidAir_Down(false)
	, jumpspeed(0)
	, heroAnimationCounter(0)
	, heroAnimationInvert(false)
{
}

Player::~Player(void)
{
}

// Player Init
void Player::Init(void)
{
	SetEntityHealth(10);
	SetEntityDamage(5);
	SetEntityMovementSpeed(0.1);
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

// Player Update
void Player::PlayerUpdate(GameObject_Map* Map)
{ 
	ConstrainPlayer(20, 750, 25, 575, 1.0f);
}
