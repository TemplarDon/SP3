#ifndef SCENE_ASSIGNMENT2_H
#define SCENE_ASSIGNMENT2_H

#include "Environment.h"
#include <vector>
#include "SceneBase.h"
#include <map>
#include "Map.h"
#include "GameObject_Map.h"
#include "Player.h"

class SP3 : public SceneBase
{

public:
	SP3();
	~SP3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);

	//Test jump
	int player_y;
	Vector3 Velocity;
	int gravity;

protected:

	//std::vector<GameObject *> m_goList;

	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;
	float m_gravity;

	// Player
	Player* m_Player;

	// Map
	Map* m_Map;
	GameObject_Map* m_GoMap;
};

#endif