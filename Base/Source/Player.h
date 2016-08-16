#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	 Player();
	~Player();

	// Initialise this class instance
	void Init(void);

	// Returns true if the player is on ground
	bool isOnGround(void);
	// Returns true if the player is jumping upwards
	bool isJumpUpwards(void);
	// Returns true if the player is on freefall
	bool isFreeFall(void);
	// Set the player's status to free fall mode
	void SetOnFreeFall(bool isOnFreeFall);
	// Set the player to jumping upwards
	void SetToJumpUpwards(bool isOnJumpUpwards);
	// Stop the player's movement
	void SetToStop(void);
	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);
	//Hero Jump
	void HeroJump();
	// Get Jumpspeed of the player
	int GetJumpspeed(void);
	// Update Jump Upwards
	void UpdateJumpUpwards();
	// Update FreeFall
	void UpdateFreeFall();

	//Player movement
	void MoveLeft(const float timeDiff);
	void MoveRight(const float timeDiff);

	// Get mapOffset_x
	int GetMapOffset_x(void);
	// Get mapOffset_y
	int GetMapOffset_y(void);
	// Get mapFineOffset_x
	int GetMapFineOffset_x(void);
	// Get mapFineOffset_y
	int GetMapFineOffset_y(void);

	// Set Animation Invert status of the player
	void SetAnimationInvert(bool heroAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);

	// Constrain the position of the player to within the border
	void ConstrainPlayer(const int leftBorder, const int rightBorder,
		const int topBorder, const int bottomBorder,
		float timeDiff);
	// Collision Repsonse
	virtual void CollisionResponse();

	// Player Update
	void PlayerUpdate(GameObject_Map* m_cMap);
	


private:
	// Hero's information
	
	int jumpspeed;
	bool hero_inMidAir_Up;
	bool hero_inMidAir_Down;
	bool heroAnimationInvert;
	int heroAnimationCounter;

	// For scrolling.
	int mapOffset_x, mapOffset_y;
	int mapFineOffset_x, mapFineOffset_y;

	// For Collision
	Vector3 m_PrevPosition;
};



#endif