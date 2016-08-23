#ifndef ENTITY_H
#define ENTITY_H

#include "ElementalObject.h"
#include "AttackBase.h"

#include "Camera.h"

enum ENTITY_MOVE_STATE
{
	NO_STATE,
    STUNNED,
	ON_GROUND,
	FALLING,
	JUMPING,
	TOTAL_MOVE_STATE,
};

class Entity : public ElementalObject
{
public:
	Entity();
	~Entity();
	
	//Setter for entity health
	virtual void SetEntityMaxHealth(int health);
	//Getter for entity health
	virtual int GetEntityHealth();

	//Getter for entity damage
	virtual int GetEntityDamage();
    virtual void TakeDamage(int damagetaken);
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
		float timeDiff, Camera camera);

	// Get and Set for Entitymove state
	virtual ENTITY_MOVE_STATE GetMoveState();
	virtual void SetMoveState(ENTITY_MOVE_STATE SetState);


	// Collision Repsonse
	virtual void DisableDash();	
	void CollisionResponse(GameObject* OtherGo);
	// CollisionWithTileMap
	virtual void UpdateTileMapCollision(GameObject_Map* Map);

	// Collision Box
	virtual void GenerateCollisionBoundary(GameObject_Map* Map);
	virtual void CheckCollisionBoundary();

	virtual void setSpriteVector(Mesh* mesh, int startFrame, int endFrame, int repeat, float time, bool active);
	virtual std::vector<SpriteAnimation*> getSpriteVector();

	virtual void setMeshVector(Mesh* mesh, std::string Name, const char* targaName, int numRow, int numCol);
	virtual std::vector<Mesh*> getMeshVector();
	virtual void Update(double dt, GameObject_Map* Map, Camera camera);
    AttackBase *Attacks = new AttackBase;
    bool GetControlLock();
	virtual void Death()
	{}


protected:
	float CurrHealth;
    float MaxHealth;
	float Damage;
	float TakenDamage;
    int DamagMultiplier;
    bool isEnemyEntity;

	//Jeff's bool
	bool Move_Left;
	bool Move_Right;

	// For scrolling
	int mapOffset_x, mapOffset_y;
	float mapFineOffset_x, mapFineOffset_y;
	float MovementSpeed;
    float prevMS;
    Mesh* SheildMesh;
    



	// ----------------- For jumping and collision check ----------------- //
	ENTITY_MOVE_STATE m_CurrEntityMoveState;

	Vector3 m_MaxCollisionBox;
	Vector3 m_MinCollisionBox;
	float EntityMapOffsetX;

	// ------------------------------------------------------------------- //
    // ----------------- For element abilities checks -------------------- //
    void AbilityMovementCheck();
    void ExecuteAbility(double dt);
    float DashDestinationX;
    bool m_Dashingleft, m_Dashingright;
    ENTITY_MOVE_STATE m_PrevState;
    void DebuffCheckAndApply(double dt);//stunned, slowed, burning, knockback 
    bool deBuff_Stunned, deBuff_burning, deBuff_Slowed, deBuff_KnockBack;
    float deBuff_StunTimer, deBuff_BurningTimer, deBuff_SlowTimer;
    float KnockBackDestX;
    float m_HealTimer;
    bool KnockBackLeftRight;
    bool SheildUp;
    int deBuff_BurnTicks;
    double interDT;
    // ------------------------------------------------------------------- //

	bool DirectionLeftRight;
	Vector3 m_PrevPos;
	
	bool m_bJumping;
	float Gravity;
	float JumpVel;
	float JUMPMAXSPEED, JUMPACCEL;

    //For Special abilities
   
	bool isLockMovement;

	std::vector<Mesh*> AnimationMeshList;
	std::vector<SpriteAnimation*> AnimationSpriteList;

    
};

#endif