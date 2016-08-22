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
	: paraWallOffset_x(0)
	, paraWallOffset_y(0)
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

	rotateUI = 0;
	rotateUI2 = 0;
	treePos = 100 ;
	orignalTreePos = 100;

	meshList[GEO_HEALTH_BAR] = MeshBuilder::GenerateQuad("player", Color(0, 1, 0), 1.f);


	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;

	// --------------------------- Background --------------------------- //
	// ---------------------------------------------------------- // 

	// ------------------------------ Map ------------------------------- //
	m_Map = new Map();
	m_Map->Init(Application::GetWindowHeight(), Application::GetWindowWidth(), 24, 32, 600, 1600);
	m_Map->LoadMap("Image//Maps//test.csv");

	m_GoMap = new GameObject_Map();
	m_GoMap->Init(m_Map);

	// ----------------- Player ----------------- // 
	meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation("player", 1, 2);
	SpriteAnimation* sa = static_cast<SpriteAnimation*>(meshList[GEO_PLAYER]);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 1, 1, 0.8f, true);
	}
	m_Player = dynamic_cast<Player*>(GameObjectManager::SpawnGameObject(PLAYER, GO_PLAYER, Vector3(20, 50, 1), Vector3(m_GoMap->GetTileSize(), m_GoMap->GetTileSize(), 1), true, true, meshList[GEO_PLAYER], "Image//player.tga", true, sa));
	m_Player->Init();

	m_Player->Attacks->Init(m_Player->GetEntityDamage(), 5.0f);
	// ------------------------------------------ // 

	// ------------------- Set Level ------------------ // 

	m_LevelLoaded = m_Player->GetCurrentLevel();

	// ------------------------------------------------ // 

	// ------------------- Cam ------------------ // 
	OrignialCamPos = camera.position;
	OrignialCamTarget = camera.target;
	// ------------------------------------------ // 

	// ------------------ Enemy ----------------- // 
	Enemy * temp = new Enemy();
	meshList[GEO_ENEMY] = MeshBuilder::GenerateSpriteAnimation("enemy", 1, 4);
	SpriteAnimation* sa2 = static_cast<SpriteAnimation*>(meshList[GEO_ENEMY]);
	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(0, 3, 1, 0.8f, true);

	}
	temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Vector3(m_Player->GetPosition().x - 10, m_Player->GetPosition().y, 1), Vector3(m_GoMap->GetTileSize(), m_GoMap->GetTileSize(), 1), true, true, meshList[GEO_ENEMY], "Image//blue Running.tga", true, sa2));
	temp->EnemyInit(m_Player->GetPosition(), 20, EARTH, 10,50);
	// ------------------------------------------ // 

}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);
	m_Player->Attacks->UpdateAttack(dt, m_Player->GetElement(), m_Player->GetPosition(), m_Player->GetLeftRight());

	if (Application::IsKeyPressed('A') && m_Player->GetControlLock() == false)
	{
		m_Player->SetMoving_Left(true);
		m_Player->SetMove_Right(false);
	}

    if (Application::IsKeyPressed('D') && m_Player->GetControlLock() == false)
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
    if (Application::IsKeyPressed('W') && m_Player->GetMoveState() == ON_GROUND && m_Player->GetControlLock() == false)
	{
		m_Player->UpdateJump(dt);
	}
	if (m_Player->GetMoveState() != ON_GROUND)
	{
		m_Player->EntityJumpUpdate(dt);
	}

	// ----------------- Basic Element Selection ------------------ //
	if (Application::IsKeyPressed('Q'))
	{
		if (m_CanChangeElement)
		{
			if (m_Player->GetElement() == MISC)
				m_Player->SetElement(WATER);
			else if (m_Player->GetElement() == WATER)
				m_Player->SetElement(FIRE);
			else if (m_Player->GetElement() == FIRE)
				m_Player->SetElement(EARTH);
			else if (m_Player->GetElement() == EARTH)
				m_Player->SetElement(MISC);
			m_CanChangeElement = false;
		}
	}

	// ----------------- Charged Elements Selection ------------------ //
	static bool bEButtonState = false;
	if (!bEButtonState && Application::IsKeyPressed('E'))
	{
		bEButtonState = true;
	}
	else if (bEButtonState && !Application::IsKeyPressed('E'))
	{
		bEButtonState = false;
	}

	// ----------------- Element Combining ------------------ //
	static bool bQButtonState = false;
	if (!bQButtonState && Application::IsKeyPressed('Q'))
	{
		bQButtonState = true;
	}
	else if (bQButtonState && !Application::IsKeyPressed('Q'))
	{
		bQButtonState = false;
	}

	// ----------------- Sort Map ------------------ //
	m_GoMap->SortMap();
	// --------------------------------------------- //

	// ----------------- Main Loop ----------------- //
	for (std::vector<GameObject*>::size_type i = 0; i < GameObjectManager::m_goList.size(); ++i)
	{
		GameObject* go = GameObjectManager::m_goList[i];
		if (!go->GetActive())
			continue;

		if (go->GetType() == GO_BLOCK)
			continue;

		// Sprite Animation Update
		if (go->GetSpriteAnimation() != NULL)
		{
			go->GetSpriteAnimation()->Update(dt);
		}

		if (go->GetType() == GO_PLAYER)
		{
			m_Player->Update(dt, m_GoMap, camera);
		}

		if (go->GetType() == GO_ATTACK)
		{
			go->Update(dt);
		}

		if (go->GetType() == GO_ENEMY)
		{
			Enemy* temp = dynamic_cast<Enemy*>(go);
			temp->Update(dt, m_Player->GetPosition(), m_GoMap, camera);
		}

		if (go->GetObjectType() == ENVIRONMENT)
		{
			Environment* temp = dynamic_cast<Environment*>(go);
			temp->Update(dt, m_GoMap);
		}

        if (go->GetType() == GO_SHEILD)
        {
            Environment* temp = dynamic_cast<Environment*>(go);
            temp->Update_Sheild(m_Player->GetPosition());
        }

		for (std::vector<GameObject*>::size_type i2 = 0; i2 < GameObjectManager::m_goList.size(); ++i2)
		{
			GameObject *go2 = GameObjectManager::m_goList[i2];

			if (!go2->GetActive())
				continue;

			if (go->GetObjectType() == PROJECTILE && go2->GetObjectType() == ENVIRONMENT)
			{
				if (go->EmpricalCheckCollisionWith(go2, dt))
				{
					go2->CollisionResponse(go);
					go->CollisionResponse(go2);
				}
			}
            if ((go->GetObjectType() == PROJECTILE) && (go2->GetObjectType() == PLAYER || go2->GetObjectType() == ENEMY) )
            {
                if (go->EmpricalCheckCollisionWith(go2, dt))
                {
                    go2->CollisionResponse(go);
                }
            }

			if (go2->GetType() == GO_BLOCK)
				continue;

			if (go->GetObjectType() == PLAYER && go2->GetObjectType() == ENVIRONMENT)
			{
				if (go->EmpricalCheckCollisionWith(go2, dt))
				{
					go->CollisionResponse(go2);
				}
			}

			if (go->GetObjectType() == PLAYER && go2->GetObjectType() == TRANSITION)
			{
				if (go->EmpricalCheckCollisionWith(go2, dt))
				{
					Transition* temp = dynamic_cast<Transition*>(go2);
					SwitchLevel(temp->GetNextTransition());
					break;
				}
			}
			if (go->GetObjectType() == PROJECTILE &&( go2->GetObjectType() == ENEMY||go2->GetObjectType()==PLAYER))
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

	// ----------------- Update Camera ------------------ //
	if (camera.position.x < OrignialCamPos.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x())
	{

		camera.position.x += dt * 8;
	}
	else if (camera.position.x > OrignialCamPos.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x() + 5)
	{
		camera.position.x -= dt * 8;
	}

	if (camera.target.x < OrignialCamTarget.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x())
	{
		camera.target.x += dt * 8;
	}
	else if (camera.target.x > OrignialCamTarget.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x() + 5)
	{
		camera.target.x -= dt * 8;

	}
	//camera.position.x = OrignialCamPos.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x();
	//camera.target.x = OrignialCamTarget.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x();
	// -------------------------------------------------- //



	////419 same time
	//if (treePos >  (orignalTreePos - (m_Player->GetMapOffset_x() * 0.5) - (m_Player->GetMapFineOffset_x() * 0.5) )  )
	//{
	//	treePos -= (dt * 4);
	//}

	//Stalagmite
	if (treePos >  (orignalTreePos - (m_Player->GetMapOffset_x() * 0.06) - (m_Player->GetMapFineOffset_x() * 0.06) )  )
	{
		treePos -= (dt * 0.5);
	}
	else if (treePos < (orignalTreePos - (m_Player->GetMapOffset_x() * 0.06) - (m_Player->GetMapFineOffset_x() * 0.06)))
	{
		treePos += (dt * 0.5);
	}

	UpdateUI(dt);
}

void SP3::UpdateUI(double dt)
{
	// -------------------------------------- Element indicator ---------------------------------------- //

	if (Application::IsKeyPressed('F'))
	{
		m_Player->SetElement(EARTH);
	}


	if (Application::IsKeyPressed('G'))
	{
		m_Player->SetElement(FIRE);
	}

	if (Application::IsKeyPressed('H'))
	{
		m_Player->SetElement(WATER);
	}

	if (rotateUI > 360.f)
	{
		rotateUI -= 360.f;
	}


	//std::cout << rotateUI << std::endl;

	switch (m_Player->GetElement())
	{
	case 1:
	{
		// Fire
		if (rotateUI < 270.f)
		{
			rotateUI += dt * 120;
		}

		break;
	}
	case 2:
	{
		// Earth
		if (rotateUI < 40.f)
		{
			rotateUI += dt * 120;
		}
		else if (rotateUI >= 271.f || rotateUI >= 260.f)
		{
			//std::cout << "HEYYYAYYAYAYAAYAYAYAYAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAYYYYYHUE";
			rotateUI += dt * 120;
		}

		break;
	}
	case 3:
	{
		// Water
		if (rotateUI < 140)
		{
			rotateUI += dt * 120;
		}

		break;
	}
	default:
		break;
	}



	// ------------------------------------- Charge ----------------------------------------- //
	//std::cout << m_Player->GetFirstElementArray()[0]; 

	rotateUI2 += dt;
}

void SP3::RenderGO(GameObject *go)
{
	modelStack.PushMatrix();
	modelStack.Translate(go->GetPosition().x, go->GetPosition().y, go->GetPosition().z);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(go->GetScale().x, go->GetScale().y, go->GetScale().z);
	RenderMesh(go->GetMesh(), false);
	modelStack.PopMatrix();

	if (go->GetObjectType() == ENEMY)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->GetPosition().x, go->GetPosition().y + 5, go->GetPosition().z);
		modelStack.Scale(dynamic_cast<Entity*>(go)->GetEntityHealth(), 3, 1);
		RenderMesh(meshList[GEO_HEALTH_BAR], false);
		modelStack.PopMatrix();
	}
}

void SP3::RenderParallaxMap()
{
	paraWallOffset_x = (int)(m_Player->GetMapOffset_x() / 2);
	paraWallOffset_y = 0;
	paraWallTileOffset_y = 0;
	paraWallTileOffset_x = (int)(paraWallOffset_x / m_ParallaxMap->GetTileSize());

	if (paraWallTileOffset_x + m_ParallaxMap->GetNumOfTiles_ScreenWidth() > m_ParallaxMap->GetNumOfTiles_MapWidth())
		paraWallTileOffset_x = m_ParallaxMap->GetNumOfTiles_MapWidth() - m_ParallaxMap->GetNumOfTiles_ScreenWidth();

	paraWallFineOffset_x = paraWallOffset_x % m_ParallaxMap->GetTileSize();

	int m = 0;
	for (int i = 0; i < m_ParallaxMap->GetNumOfTiles_ScreenHeight(); i++)
	{
		for (int k = 0; k < m_ParallaxMap->GetNumOfTiles_ScreenWidth() + 1; k++)
		{
			m = paraWallTileOffset_x + k;
			if ((paraWallTileOffset_x + k) >= m_ParallaxMap->GetNumOfTiles_MapWidth())
				break;

			switch (m_ParallaxMap->m_ScreenMap[i][m])
			{
			case 3:
			{
				//modelStack.PushMatrix();
				//modelStack.Translate(m_worldWidth * 0.5 + m_Player->GetMapOffset_x() * 0.8, m_worldHeight * 0.5, -1);
				//modelStack.Scale(20, 20, 1);
				//RenderMesh(meshList[GEO_BACKGROUND], false);
				//modelStack.PopMatrix();
				break;
			}
			default:
				break;
			}

		}
	}

}

void SP3::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	//projection.SetToOrtho(m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x(), m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x() + m_worldWidth, 0, m_worldHeight, -10, 10);
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


	// ------------------ Background ------------------- //

	//modelStack.PushMatrix();
	//modelStack.Translate(10, 60, -2);
	//modelStack.Scale(190, 80, 1);
	//RenderMesh(meshList[GEO_FIRE_BACKGROUND], false);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////modelStack.Translate(((m_worldWidth * 0.2) + m_Player->GetMapFineOffset_x()), 35, -1);
	//modelStack.Translate(m_worldWidth * 0.7, 60, -2);
	//modelStack.Scale(300, 80, 1);
	//RenderMesh(meshList[GEO_BACKGROUND], false);
	//modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.7, 61, -2);
	modelStack.Scale(300, 78, 1);
	RenderMesh(meshList[GEO_FIRE_BACKGROUND], false);
	modelStack.PopMatrix();

	// ------------------------------------------------- //

	//stalagmite
	modelStack.PushMatrix();
	modelStack.Translate(treePos , 60, -1);
	modelStack.Scale(120, 80, 1);
	RenderMesh(meshList[GEO_TREE], false);
	modelStack.PopMatrix();

	for (std::vector<GameObject *>::iterator it = GameObjectManager::m_goList.begin(); it != GameObjectManager::m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->GetActive() && go->GetVisible())
		{
			RenderGO(go);
		}	
	}

	// -------------------- UI --------------------- //

	// Health Bar
	modelStack.PushMatrix();
	modelStack.Translate(10 + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x(), 95, 1);
	modelStack.Scale(m_Player->GetEntityHealth(), 3, 1);
	RenderMesh(meshList[GEO_HEALTH_BAR], false);
	modelStack.PopMatrix();

	// Element indicator
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 - 30, 15, 0);
	modelStack.Rotate(rotateUI, 0, 0, 1);

	// Fire
	modelStack.PushMatrix();
	modelStack.Translate(0, 5, 1);
	//modelStack.Translate(0, 3.5, 1);
	modelStack.Scale(8, 8, 1);
	modelStack.Rotate(-rotateUI, 0, 0, 1);
	RenderMesh(meshList[GEO_FIRE_ICON], false);
	modelStack.PopMatrix();

	// Earth
	modelStack.PushMatrix();
	modelStack.Rotate(120, 0, 0, 1);
	modelStack.Translate(0, 5, 1);
	//modelStack.Translate(4.5, -4.5, 1);
	modelStack.Scale(8, 8, 1);
	modelStack.Rotate(240-rotateUI, 0, 0, 1);
	RenderMesh(meshList[GEO_WATER_ICON], false);
	modelStack.PopMatrix();

	// Water
	modelStack.PushMatrix();
	modelStack.Rotate(240, 0, 0, 1);
	modelStack.Translate(0, 5, 1);
	//modelStack.Translate(-4.5, -4.5, 1);
	modelStack.Scale(8, 8, 1);
	modelStack.Rotate(120 -rotateUI, 0, 0, 1);
	RenderMesh(meshList[GEO_EARTH_ICON], false);
	modelStack.PopMatrix();

	// Ring (parent)
	modelStack.Scale(6, 6, 1);
	modelStack.Translate(0, 0, 2);
	RenderMesh(meshList[GEO_RING], false);
	modelStack.PopMatrix();


	// Charge 
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 , 15, 2);
	modelStack.Scale(15, 15, 1);
	modelStack.Rotate(rotateUI2, 0, 0, 1);
	RenderMesh(meshList[GEO_CHARGE_WHEEL], false);
	modelStack.PopMatrix();

	// Arrow
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 + 20, 15, 2);
	modelStack.Scale(10, 10, 1);
	modelStack.Rotate(180, 0, 0, 1);
	RenderMesh(meshList[GEO_ARROW], false);
	modelStack.PopMatrix();

	// --------------------------------------------- //

	//std::cout << fps << std::endl;
}

void SP3::SwitchLevel(LEVEL NextLevel)
{
	// Delete old maps
	delete m_Map;
	m_Map = NULL;

	delete m_GoMap;
	m_GoMap = NULL;

	// Clear m_GoList of unwanted stuff
	for (std::vector<GameObject*>::size_type i = 0; i < GameObjectManager::m_goList.size(); ++i)
	{
		GameObject* go = GameObjectManager::m_goList[i];

		if (go->GetObjectType() != PLAYER)
		{
			GameObjectManager::m_goList.erase(GameObjectManager::m_goList.begin() + i);
		}
		else
		{
			i = 0;
		}
	}

	// Load New Maps
	// ------------------------------ Map ------------------------------- //
	m_Map = new Map();
	m_Map->Init(Application::GetWindowHeight(), Application::GetWindowWidth(), 24, 32, 600, 1600);

	switch (NextLevel)
	{
	case TUTORIAL: m_Map->LoadMap("Image//Maps//Tutorial.csv"); break;
	case LEVEL_1: m_Map->LoadMap("Image//Maps//Level_1.csv"); break;
	case LEVEL_2: m_Map->LoadMap("Image//Maps//Level_2.csv"); break;
	case LEVEL_3: m_Map->LoadMap("Image//Maps//Level_3.csv"); break;
	case LEVEL_4: m_Map->LoadMap("Image//Maps//Level_4.csv"); break;
	default:
		break;
	}
	
	// ------------------------- GoMap ------------------------- // 
	m_GoMap = new GameObject_Map();
	m_GoMap->Init(m_Map);

	// ----------------- Player ----------------- // 
	m_Player->SetPosition(m_GoMap->GetLevel()->GetStartPos());
	m_Player->SetMapOffset_x(m_Player->GetPosition().x - (0.5 * m_GoMap->GetNumOfTiles_ScreenWidth() * m_GoMap->GetTileSize()));
	m_Player->SetMapFineOffset_x(0);
	m_Player->SetRespawnPos(m_Player->GetPosition());
	m_Player->SetCurrentLevel(NextLevel);

	// ------------------------------------------ // 

	// ------------------- Set Level ------------------ // 

	m_LevelLoaded = m_Player->GetCurrentLevel();

	// ------------------------------------------------ // 

	// ------------------- Cam ------------------ // 
	camera.position.x = m_Player->GetMapOffset_x();
	camera.target.x = m_Player->GetMapOffset_x();
	// ------------------------------------------ // 

	treePos = orignalTreePos;
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

	//if (m_ParallaxMap)
	//{
	//	delete m_Map;
	//	m_ParallaxMap = NULL;
	//}
}
