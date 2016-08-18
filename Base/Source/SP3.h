#ifndef SCENE_ASSIGNMENT2_H
#define SCENE_ASSIGNMENT2_H

#include "Environment.h"
#include <vector>
#include "SceneBase.h"
#include <map>
#include "Map.h"
#include "GameObject_Map.h"
#include "GameObject.h"
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
	void RenderParallaxMap();


protected:

	//std::vector<GameObject *> m_goList;

	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;
	float m_gravity;
    float m_ChangeElementDebounce;
    bool m_CanChangeElement;


	// Player
	Player* m_Player = new Player;
    ELEMENT currentSelectedEle;

	// Map
	Map* m_Map;
	GameObject_Map* m_GoMap;

	// Parallax Map
	Map* m_ParallaxMap;
	int paraWallOffset_x, paraWallOffset_y;
	int paraWallTileOffset_x, paraWallTileOffset_y;
	int paraWallFineOffset_x, paraWallFineOffset_y;
	GameObject_Map* m_GoMap2;
};

#endif