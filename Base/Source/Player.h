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

	void AddElementCharge(ELEMENT ToBeAdded);
	void RemoveElementCharge();
	void ReorderElements();

	ELEMENT* GetElementArray();

	void SetRespawnPos(Vector3 RespawnPos);
	Vector3 GetRespawnPos();

	virtual void Death();

	LEVEL GetCurrentLevel();
	void SetCurrentLevel(LEVEL newLevel);

	int GetHealthCharges();
	void AddHealthCharges();

	void UpdateHealthCharges();

	virtual void CollisionResponse(GameObject* OtherGo);
private:
	// Player's information
	int jumpspeed;

	// For Collision
	Vector3 m_PrevPosition;

	// For Storing Of Elements
	ELEMENT m_ElementArray[5];

	// Pos of last checkpoint
	Vector3 m_RespawnPos;

	// Current Level
	LEVEL m_CurrLevel;

	// Health Charges
	int m_HealthCharges;
};



#endif