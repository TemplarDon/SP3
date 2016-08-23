#ifndef SP3_H_
#define SP3_H_

#include "Environment.h"
#include <vector>
#include "SceneBase.h"
#include <map>
#include "Map.h"
#include "GameObject_Map.h"
#include "GameObject.h"
#include "Player.h"

enum GAMESTATES
{
	PLAY,
	LOADING,
};

class SP3 : public SceneBase
{

public:
	SP3();
	~SP3();

	enum MENU_OPTIONS
	{
		START_GAME,
		INSTRUCTIONS,
		OPTIONS,
		QUIT,
	};

	enum GAMESTATE
	{
		MENU,
		GAME,
		LOAD_LVL_1,
		LOAD_LVL_2,
		LOAD_LVL_3,
		LOAD_LVL_4,
	};

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);
	void RenderParallaxMap();

	void SwitchLevel(LEVEL NextLevel);
	void UpdateUI(double dt);
	void UpdateUI2(double dt);
	void RenderUI();

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
	Vector3 OrignialCamPos;
	Vector3 OrignialCamTarget;

	// Map
	Map* m_Map;
	GameObject_Map* m_GoMap;

	// Parallax Map
	Map* m_ParallaxMap;
	int paraWallOffset_x, paraWallOffset_y;
	int paraWallTileOffset_x, paraWallTileOffset_y;
	int paraWallFineOffset_x, paraWallFineOffset_y;
	GameObject_Map* m_GoMap2;
	float treePos;
	float orignalTreePos;

	// Transition
	LEVEL m_LevelLoaded;

	//UI
	float rotateUI;
	float rotateUI2;
	float uiPos;
	float originalUIPos;

	//Health bar
	int m_lives;
};

#endif