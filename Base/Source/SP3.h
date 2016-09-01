#ifndef SP3_H_
#define SP3_H_

#include "Debugging.h"

#include "Environment.h"
#include <vector>
#include "SceneBase.h"
#include <map>
#include "Map.h"
#include "GameObject_Map.h"
#include "GameObject.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "Sound.h"


class SP3 : public SceneBase
{

public:
	SP3();
	~SP3();

	enum MENU_OPTIONS
	{
		OP_START_GAME,
		OP_INGAME,
		OP_INSTRUCTIONS,
		OP_QUIT,
	};

	enum GAMESTATE
	{
		GS_MENU,
		GS_GAME,
		GS_VICTORY,
		GS_INSTRUCTIONS,
		GS_QUIT,
	};




	virtual void Init();
	virtual void Update(double dt);
	virtual void UpdateMenu(double dt);
	virtual void UpdateGame(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go, float offset);
	void RenderParallaxMap();

	void SwitchLevel(LEVEL NextLevel);
	void UpdateUI(double dt);
	void UpdateUI2(double dt);
	void RenderUI();
	void RenderUIText();
	void RenderGame();
	void RenderMenu();
	void RenderOptions();
	void RenderInstructions();

protected:
	// Music
	Sound music;
	float keyCD;
	

	// Game State
	GAMESTATE GameState;
	MENU_OPTIONS Options;

	LEVEL Level;
	float cdMenu;

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

	// Parallax 
	float treePos_x;
	float orignalTreePos_x;
	float treePos_y;
	float orignalTreePos_y;

	// Transition
	LEVEL m_LevelLoaded;

	//UI
	float rotateUI;
	float rotateUI2;
	float UIPos_x;
	float originalUIPos_x;
	float UIPos_y;
	float originalUIPos_y;

	//Health bar
	float healthbarpos_x;

	// Test Earth
	float Distance_X;

	bool playonce;
	bool playonce2;
	bool playonce3;
};

#endif