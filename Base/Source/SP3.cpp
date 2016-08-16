#include "SP3.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"

#include <fstream>
#include <sstream>

#include "GameObjectManager.h"

SP3::SP3()
{
}

SP3::~SP3()
{
}

std::vector<GameObject*> GameObjectManager::m_goList;

void SP3::Init()
{
	SceneBase::Init();


	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;

	// ----------------- Example of Spawning Objects ------------ // 
	// SpawnGameObject(OBJECT_TYPE (Eg. Environment, Projectile etc.), GAMEOBJECT_TYPE (Eg. GO_BALL, etc.), Position, Scale, Collidable, Visible)
	GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_PILLAR, Vector3(0,50, 0), Vector3(1, 1, 1), true, true, meshList[GEO_BALL]);
	// ---------------------------------------------------------- // 

	m_Map = new Map();
	m_Map->Init(Application::GetWindowHeight(), Application::GetWindowWidth(), 24, 32, 600, 1600);
	m_Map->LoadMap("Image//Maps//test.csv");
	
	// ------------ Add Possible Function that reads m_Map and fills new vector with GameObjects ------------ // 
	m_GoMap = new GameObject_Map();
	m_GoMap->Init(m_Map);

	// ----------------- Player ----------------- // 
	//m_Player = GameObjectManager::SpawnPlayerObject(PLAYER, GO_PLAYER, Vector3(m_worldWidth * 0.5, m_worldHeight * 0.5, 1), Vector3(0.5, 0.5, 0.5), true, true, meshList[GEO_PLAYER], "Image//player.tga");
	m_Player = GameObjectManager::SpawnPlayerObject(PLAYER, GO_PLAYER, Vector3(0, 0 , 1), Vector3(0.5, 0.5, 0.5), true, true, meshList[GEO_PLAYER], "Image//Tiles//testground.tga");
	m_Player->Init();
	// ------------------------------------------ // 
}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);


	if (Application::IsKeyPressed('A'))
	{
		m_Player->SetMoving_Left(true);
		m_Player->SetMove_Right(false);
	}
	
	if (Application::IsKeyPressed('D'))
	{
		m_Player->SetMoving_Left(false);
		m_Player->SetMove_Right(true);
	}
	
	if (!Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
	{
		m_Player->SetMoving_Left(false);
		m_Player->SetMove_Right(false);
	}
	if (m_Player->GetMoving_Left() == true)
	{
		m_Player->MoveLeft(0.3f);	
	}
	if (m_Player->GetMoving_Right() == true)
	{
		m_Player->MoveRight(0.3f);
	}
	if (Application::IsKeyPressed('W') )
	{
		/*m_Player->EntityJumpUpdate(dt);*/
		m_Player->UpdateJump(dt);
	}
	if (m_Player->GetJump())
	{ 
		m_Player->EntityJumpUpdate(dt);
	}
	// ----------------- Main Loop ----------------- //

	for (std::vector<GameObject *>::iterator it = GameObjectManager::m_goList.begin(); it != GameObjectManager::m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;

		if (!go->GetActive())
			continue;
		if (go->GetType() == GO_PLAYER)
		{
			m_Player->PlayerUpdate(m_GoMap);
			
		}



	}

	// --------------------------------------------- //
}

void SP3::RenderGO(GameObject *go)
{
	modelStack.PushMatrix();
	modelStack.Translate(go->GetPosition().x, go->GetPosition().y, go->GetPosition().z);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(go->GetScale().x, go->GetScale().y, go->GetScale().z);
	RenderMesh(go->GetMesh(), false);
	modelStack.PopMatrix();
}

void SP3::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderMesh(meshList[GEO_AXES], false);

	for (std::vector<GameObject *>::iterator it = GameObjectManager::m_goList.begin(); it != GameObjectManager::m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->GetActive() && go->GetVisible())
		{
			RenderGO(go);
		}

		if (m_Player->GetActive())
		{
			RenderGO(m_Player);
		}
	}
}

void SP3::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (GameObjectManager::m_goList.size() > 0)
	{
		GameObject *go = GameObjectManager::m_goList.back();
		delete go;
		GameObjectManager::m_goList.pop_back();
	}

	if (m_Map)
	{
		delete m_Map;
		m_Map = NULL;
	}
}
