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
	virtual void SetEntityHealth(int health);
	//Getter for entity health
	virtual int GetEntityHealth();

	//Setter for entity damage
	virtual void SetEntityDamage(int damage);
	//Getter for entity damage
	virtual int GetEntityDamage();

	//Setter for entity taken damage
	virtual void SetEntityTakenDamage(int takendamage);
	//Getter for entity taken damage
	virtual int GetEntityTakenDamage();

	//Setter for entity movement speed
	virtual void SetEntityMovementSpeed(float movementspeed);
	//Getter for entity movement speed
	virtual float GetEntityMovementSpeed();

	//Movement
	virtual void MoveLeft(const float timeDiff);
	virtual void MoveRight(const float timeDiff);

	virtual bool GetLeftRight();
	virtual void SetLeftRight(bool input);
	
	//Jeff's
	virtual bool GetMoving_Left();
	virtual void SetMoving_Left(bool input);
	virtual bool GetMoving_Right();
	virtual void SetMove_Right(bool input);

	//Jump
	virtual void UpdateJump(double dt);
	virtual void EntityJumpUpdate(double dt);
	virtual bool GetJump();
	

	// Getter for mapOffset_x
	virtual int GetMapOffset_x();
	// Setter for mapOffset_x
	virtual void SetMapOffset_x(int  mapOffset_x);
	// Getter for mapOffset_y
	virtual int GetMapOffset_y();
	// Setter for mapOffset_y
	virtual void SetMapOffset_y(int mapOffset_y);
	// Getter for mapFineOffset_x
	virtual int GetMapFineOffset_x();
	// Setter for mapFineOffset_x
	virtual void SetMapFineOffset_x(int mapFineOffset_x);
	// Get mapFineOffset_y
	virtual int GetMapFineOffset_y();
	// Setter for mapFineOffset_y
	virtual void SetMapFineOffset_y(int mapFineOffset_y);

	// Constrain the position of the player to within the border
	virtual void ConstrainPlayer(const int leftBorder, const int rightBorder,
		const int topBorder, const int bottomBorder,
		float timeDiff);

	// Collision Repsonse
	virtual void CollisionResponse();
	
	// CollisionWithTileMap
	virtual void UpdateTileMapCollision(GameObject_Map* Map);


    virtual void Update(double dt)
    {}

protected:
	int Health;
	int Damage;
	int TakenDamage;


	//Jeff's bool
	bool Move_Left;
	bool Move_Right;


	// For scrolling
	int mapOffset_x, mapOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
	int MovementSpeed;

	// ----------------- Temporary Values ----------------- //
	bool EntityInAir_Up;
	bool EntityInAir_Down;

	float EntityMapOffsetX;
	// ----------------- Temporary Values ----------------- //

	bool DirectionLeftRight;
	Vector3 m_PrevPos;
	
	bool m_bJumping;
	float Gravity;
	float JumpVel;
	float JUMPMAXSPEED, JUMPACCEL;
};

#endif