#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	 Player();
	~Player();

	// Player Init
	void Init(void);

	// Player Update
	void PlayerUpdate(GameObject_Map* m_cMap);

	// Set Animation Invert status of the player
	void SetAnimationInvert(bool heroAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);
    AttackBase *Attacks;
	
	// Set player position
	void SetPlayerPos(Vector3 PlayerPos);
	// Get player position
	Vector3 GetPlayerPos();


private:
	// Player's information
	int jumpspeed;
	bool hero_inMidAir_Up;
	bool hero_inMidAir_Down;
	bool heroAnimationInvert;
	int heroAnimationCounter;
	Vector3 PlayerPos;

	// For Collision
	Vector3 m_PrevPosition;
	
};



#endif