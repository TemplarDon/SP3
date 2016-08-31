#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "CheckPoint.h"

class Player : public Entity
{
public:
	 Player();
	~Player();

	// Player Init
	void Init(void);

	// Player Update
	virtual void Update(double dt, GameObject_Map* Map, Camera camera);
	void SetRespawnPos(Vector3 RespawnPos);
	Vector3 GetRespawnPos();

	virtual void Death();

	LEVEL GetCurrentLevel();
	void SetCurrentLevel(LEVEL newLevel);

	int GetHealthCharges();
	void AddHealthCharges();

	void UseHealthCharge();

	void SetInvulnerability(bool status);
	bool GetInvulnerability();

	virtual void CollisionResponse(GameObject* OtherGo, GameObject_Map* Map);

	bool CheckIsDead();

	Checkpoint* GetCheckpoint();

private:
	// Player's information
	int jumpspeed;

	// For Collision
	Vector3 m_PrevPosition;

	// Pos of last checkpoint
	Vector3 m_RespawnPos;
	Checkpoint* m_LastCheckpoint;

	// Current Level
	LEVEL m_CurrLevel;

	// Health Charges
	int m_HealthCharges;

	// Invulnerability
	bool m_Invulnerability;
	float m_InvulTimer;
};



#endif