#include "Player.h"

Player::Player(void)
	: hero_inMidAir_Up(false)
	, hero_inMidAir_Down(false)
	, jumpspeed(0)
	, heroAnimationCounter(0)
	, heroAnimationInvert(false)
{
    m_CurrElement = STEAM;
    Attacks = new AttackBase;

	SetPlayerPos(m_Position);
}

Player::~Player(void)
{
}

// Player Init
void Player::Init(void)
{
	SetEntityHealth(10);
	SetEntityDamage(5);
	SetEntityMovementSpeed(1);
    Attacks->Init(GetEntityDamage(), 10.f);
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
}

// Set player position
void Player::SetPlayerPos(Vector3 PlayerPos)
{
	this->m_Position = PlayerPos;
}

// Get player position
Vector3 Player::GetPlayerPos()
{
	return PlayerPos;
}


