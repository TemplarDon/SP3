#ifndef ENTITY_H
#define ENTITY_H

#include "ElementalObject.h"
#include "AttackBase.h"
#include "GameObject_Map.h"

class Entity : public ElementalObject
{
public:
	Entity();
	~Entity();
	
	//Setter for entity health
	void SetEntityHealth(int health);
	//Getter for entity health
	int GetEntityHealth();

	//Setter for entity damage
	void SetEntityDamage(int damage);
	//Getter for entity damage
	int GetEntityDamage();

	//Setter for entity taken damage
	void SetEntityTakenDamage(int takendamage);
	//Getter for entity taken damage
	int GetEntityTakenDamage();

	//Setter for entity movement speed
	void SetEntityMovementSpeed(float movementspeed);
	//Getter for entity movement speed
	float GetEntityMovementSpeed();

	//Movement
	void MoveLeft(const float timeDiff);
	void MoveRight(const float timeDiff);

	bool GetLeftRight();
	void SetLeftRight(bool input);
	//Jeff's
	bool GetMoving_Left();
	void SetMoving_Left(bool input);
	bool GetMoving_Right();
	void SetMove_Right(bool input);

	//Jump
	void UpdateJump(double dt);
	void EntityJumpUpdate(double dt);
	bool GetJump();
	bool m_bJumping;
	float Gravity;
	float JumpVel;
	float JUMPMAXSPEED, JUMPACCEL;

	// Getter for mapOffset_x
	int GetMapOffset_x();
	// Setter for mapOffset_x
	void SetMapOffset_x(int  mapOffset_x);
	// Getter for mapOffset_y
	int GetMapOffset_y();
	// Setter for mapOffset_y
	void SetMapOffset_y(int mapOffset_y);
	// Getter for mapFineOffset_x
	int GetMapFineOffset_x();
	// Setter for mapFineOffset_x
	void SetMapFineOffset_x(int mapFineOffset_x);
	// Get mapFineOffset_y
	int GetMapFineOffset_y();
	// Setter for mapFineOffset_y
	void SetMapFineOffset_y(int mapFineOffset_y);

	// Constrain the position of the player to within the border
	void ConstrainPlayer(const int leftBorder, const int rightBorder,
		const int topBorder, const int bottomBorder,
		float timeDiff);

	// Collision Repsonse
	virtual void CollisionResponse();



    virtual void Update(double dt)
    {}

private:
	int Health;
	int Damage;
	int TakenDamage;
	float MovementSpeed;
	bool DirectionLeftRight;

	//Jeff's bool
	bool Move_Left;
	bool Move_Right;


	// For scrolling
	int mapOffset_x, mapOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
};

#endif