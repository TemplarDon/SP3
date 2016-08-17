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
    m_ChangeElementDebounce = 0.f;
    m_CanChangeElement = true;
}

SP3::~SP3()
{
}

std::vector<GameObject*> GameObjectManager::m_goList;

void SP3::Init()
{
	SceneBase::Init();
    m_Player->Attacks->Init(m_Player->GetEntityDamage(), 5.0f);
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;

	// ----------------- Example of Spawning Objects ------------ // 
	// SpawnGameObject(OBJECT_TYPE (Eg. Environment, Projectile etc.), GAMEOBJECT_TYPE (Eg. GO_BALL, etc.), Position, Scale, Collidable, Visible)
	// GameObjectManager::SpawnGameObject(ENVIRONMENT, GO_PILLAR, Vector3(0,50, 0), Vector3(1, 1, 1), true, true, meshList[GEO_BALL]);
	// ---------------------------------------------------------- // 

	m_Map = new Map();
	m_Map->Init(Application::GetWindowHeight(), Application::GetWindowWidth(), 24, 32, 600, 1600);
	m_Map->LoadMap("Image//Maps//test.csv");
	
	// ------------ Add Possible Function that reads m_Map and fills new vector with GameObjects ------------ // 
	m_GoMap = new GameObject_Map();
	m_GoMap->Init(m_Map);

	// ----------------- Player ----------------- // 
	m_Player = dynamic_cast<Player*>(GameObjectManager::SpawnGameObject(PLAYER, GO_PLAYER, Vector3(50, 0, 1), Vector3(m_GoMap->GetTileSize(), m_GoMap->GetTileSize(), 1), true, true, meshList[GEO_PLAYER], "Image//player.tga"));
	m_Player->Init();
	// ------------------------------------------ // 

}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);
    m_Player->Attacks->UpdateAttack(dt,m_Player->GetElement(),m_Player->GetPosition(), m_Player->GetLeftRight());

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
    if (Application::IsKeyPressed(VK_SPACE))
    {
        m_Player->Attacks->LaunchAttack();
    }
	
	if (!Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
	{
		m_Player->SetMoving_Left(false);
		m_Player->SetMove_Right(false);
	}
	if (m_Player->GetMoving_Left() == true)
	{
		m_Player->MoveLeft(dt);	
	}
	if (m_Player->GetMoving_Right() == true)
	{
		m_Player->MoveRight(dt);
	}
	if (Application::IsKeyPressed('W') && m_Player->GetMoveState() == ON_GROUND)
	{
		m_Player->UpdateJump(dt);
	}
	if (m_Player->GetMoveState() != ON_GROUND)
	{ 
		m_Player->EntityJumpUpdate(dt);
	}
    if (Application::IsKeyPressed('Q'))
    {
        if (m_CanChangeElement)
        {
            if (m_Player->GetElement() == EARTH)
                m_Player->SetElement(WATER);
            else if (m_Player->GetElement() == WATER)
                m_Player->SetElement(FIRE);
            else if (m_Player->GetElement() == FIRE)
                m_Player->SetElement(EARTH);
            m_CanChangeElement = false;
        }
    }

	// ----------------- Main Loop ----------------- //

	for (std::vector<GameObject *>::iterator it = GameObjectManager::m_goList.begin(); it != GameObjectManager::m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;

		if (!go->GetActive())
			continue;

		if (go->GetType() == GO_BLOCK)
			continue;

		if (go->GetType() == GO_PLAYER)
		{
			m_Player->Update(dt, m_GoMap, camera);
		}

        if (go->GetType() == GO_EARTHMELEE_PROJECTILE)
        {
            go->Update(dt);
        }

		for (std::vector<GameObject *>::iterator it2 = GameObjectManager::m_goList.begin()/*it + 1*/; it2 != GameObjectManager::m_goList.end(); ++it2)
		{
			GameObject *go2 = (GameObject *)*it2;

			if (!go2->GetActive())
				continue;

			if (go2->GetType() == GO_BLOCK)
				continue;

			if (go->GetObjectType() == PROJECTILE && go2->GetObjectType() == ENVIRONMENT)
			{
				if (go->EmpricalCheckCollisionWith(go2, dt))
				{
					go2->CollisionResponse(go);
				}
			}
			
			
		}

	}

	// --------------------------------------------- //

    //Update the debouncer
    if (!m_CanChangeElement)
    {
        m_ChangeElementDebounce += 5 * float(dt);
        if (m_ChangeElementDebounce >= 5.f)
        {
            m_CanChangeElement = true;
            m_ChangeElementDebounce = 0.f;
        }
    }
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
	//projection.SetToOrtho(m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x(), m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x() + m_worldWidth, 0, m_worldHeight, -20, 20);
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -20, 20);
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

	//Mtx44 perspective;
	//perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	////perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	//projectionStack.LoadMatrix(perspective);

	//// Camera matrix
	//viewStack.LoadIdentity();
	//viewStack.LookAt(
	//	camera.position.x, camera.position.y, camera.position.z,
	//	camera.target.x, camera.target.y, camera.target.z,
	//	camera.up.x, camera.up.y, camera.up.z
	//	);
	//// Model matrix : an identity matrix (model will be at the origin)
	//modelStack.LoadIdentity();

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
