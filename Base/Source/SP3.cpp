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

	uiPos = 0;
	originalUIPos = 0;

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;

	// --------------------------- Background --------------------------- //
	// ---------------------------------------------------------- // 

	// ------------------------------ Map ------------------------------- //
	m_Map = new Map();
	m_Map->Init(Application::GetWindowHeight(), Application::GetWindowWidth(), 24, 32, 600, 1600);
	m_Map->LoadMap("Image//Maps//Tutorial.csv");

	m_GoMap = new GameObject_Map();
	m_GoMap->Init(m_Map);

	// ----------------- Player ----------------- // 
	//meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation("player", 1, 2);
	//SpriteAnimation* sa = static_cast<SpriteAnimation*>(meshList[GEO_PLAYER]);
	//if (sa)
	//{
	//	sa->m_anim = new Animation();
	//	sa->m_anim->Set(0, 1, 1, 0.8f, true);
	//}
	m_Player = dynamic_cast<Player*>(GameObjectManager::SpawnGameObject(PLAYER, GO_PLAYER, Vector3(20, 50, 1), Vector3(m_GoMap->GetTileSize(), m_GoMap->GetTileSize(), 1), true, true, meshList[GEO_PLAYER]));
	m_Player->Init();
	m_Player->setMeshVector(meshList[GEO_PLAYER], "player ", "Image//player.tga", 1, 2); 
	m_Player->SetMesh(m_Player->getMeshVector()[0]);
	m_Player->setSpriteVector(m_Player->getMeshVector()[0], 0, 1, 1, 0.8f, true);
	m_Player->SetSpriteAnimation(m_Player->getSpriteVector()[0]);

	m_Player->setMeshVector(meshList[GEO_PLAYER_RUNNING], "player Running", "Image//blue Running.tga", 1, 4);
	m_Player->setSpriteVector(m_Player->getMeshVector()[1], 0, 3, 1, 0.8f, true);


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
	/*Enemy * temp = new Enemy();
	meshList[GEO_ENEMY] = MeshBuilder::GenerateSpriteAnimation("enemy", 1, 4);
	SpriteAnimation* sa2 = static_cast<SpriteAnimation*>(meshList[GEO_ENEMY]);
	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(0, 3, 1, 0.8f, true);

	}
	temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Vector3(m_Player->GetPosition().x - 10, m_Player->GetPosition().y, 1), Vector3(m_GoMap->GetTileSize(), m_GoMap->GetTileSize(), 1), true, true, meshList[GEO_ENEMY], "Image//blue Running.tga", true, sa2));
	*/

	//Enemy* temp = new Enemy();
	//
	//temp = dynamic_cast<Enemy*>(GameObjectManager::SpawnGameObject(ENEMY, GO_ENEMY, Vector3(m_Player->GetPosition().x - 10, m_Player->GetPosition().y, 1), Vector3(m_GoMap->GetTileSize(), m_GoMap->GetTileSize(), 1), /*Vector3(m_GoMap->GetTileSize(), m_GoMap->GetTileSize(), 1)*/ true, true, meshList[GEO_ENEMY], "Image//blue Running.tga"));
	////temp = dynamic_cast<GameObject*>(temp);
	//temp->setRotate(true);
	//temp->setMeshVector(meshList[GEO_ENEMY], "enemy","Image//wood_enemy3.tga", 2, 5);
	//temp->SetMesh(temp->getMeshVector()[0]);
	//temp->setSpriteVector(temp->GetMesh(), 2 , 6, 1, 0.8f, true);
	//temp->SetSpriteAnimation(temp->getSpriteVector()[0]);
	//temp->EnemyInit( 100, EARTH, 10,200);


	




	currentSelectedEle = m_Player->GetElement();

}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);


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

		if (m_Player->GetElement() != FIRE && m_Player->GetElement() != WATER && m_Player->GetElement() != EARTH && m_Player->GetElement() != MISC)
		{
			m_Player->SetElement(currentSelectedEle);
		}
	}

	if (!Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
	{
		m_Player->SetMoving_Left(false);
		m_Player->SetMove_Right(false);
		m_Player->SetMesh(m_Player->getMeshVector()[0]);
		m_Player->SetSpriteAnimation(m_Player->getSpriteVector()[0]);
	}
	if (m_Player->GetMoving_Left() == true)
	{
		m_Player->setRotate(true);
		m_Player->SetMesh(m_Player->getMeshVector()[1]);
		m_Player->SetSpriteAnimation(m_Player->getSpriteVector()[1]);
		m_Player->MoveLeft(dt);
	}
	if (m_Player->GetMoving_Right() == true)
	{
		m_Player->setRotate(false);
		m_Player->MoveRight(dt);
		m_Player->SetMesh(m_Player->getMeshVector()[1]);
		m_Player->SetSpriteAnimation(m_Player->getSpriteVector()[1]);
	}
    if (Application::IsKeyPressed('W') && m_Player->GetMoveState() == ON_GROUND && m_Player->GetControlLock() == false)
	{
		m_Player->UpdateJump(dt);
	}
	if (m_Player->GetMoveState() != ON_GROUND)
	{
		m_Player->EntityJumpUpdate(dt);
	}

	//--------------------Vacuum------------------------------------//
	static bool fButtonState = false;
	if (Application::IsKeyPressed('F') && fButtonState == false)
	{
		ELEMENT tempElement = m_Player->GetElement();
		m_Player->SetElement(MISC);
		m_Player->Attacks->SetAttackElement(MISC);
		m_Player->Attacks->LaunchAttack();
		m_Player->SetElement(tempElement);
		fButtonState = true;
	}
	if (!Application::IsKeyPressed('F'))
	{
		fButtonState = false;
	}
	// ----------------- Basic Element Selection ------------------ //
	if (Application::IsKeyPressed('Q'))
	{
		if (m_CanChangeElement)
		{
			if (m_Player->GetElement() == FIRE)
			{
				m_Player->SetElement(EARTH);
				currentSelectedEle = EARTH;
			}
			else if (m_Player->GetElement() == EARTH)
			{
				m_Player->SetElement(WATER);
				currentSelectedEle = WATER;
			}
			else if (m_Player->GetElement() == WATER)
			{
				m_Player->SetElement(FIRE);
				currentSelectedEle = FIRE;
			}
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
		m_Player->ReorderElements();
		bEButtonState = false;
	}

	// ----------------- Element Combining ------------------ //
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsKeyPressed('R'))
	{
		bRButtonState = true;
	}
	else if (bRButtonState && !Application::IsKeyPressed('R'))
	{
		if (m_Player->GetElement() == FIRE || m_Player->GetElement() == WATER || m_Player->GetElement() == EARTH)
		{
			switch (m_Player->GetElement())
			{
			case FIRE:
			{
						 switch (m_Player->GetElementArray()[0])
						 {
						 case FIRE:
						 {
									  m_Player->SetElement(FIRE_2);
									  break;
						 }
						 case WATER:
						 {
									   m_Player->SetElement(STEAM);
									   break;
						 }
						 case EARTH:
						 {
									   m_Player->SetElement(SAND);
									   break;
						 }
						 }
						 break;
			}

			case WATER:
			{
						  switch (m_Player->GetElementArray()[0])
						  {
						  case FIRE:
						  {
									   m_Player->SetElement(STEAM);
									   break;
						  }
						  case WATER:
						 { 
										m_Player->SetElement(WATER_2);
										break;
						  }
						  case EARTH:
						  {
										m_Player->SetElement(WOOD);
										break;
						  }
						  }
						  break;
			}

			case EARTH:
			{
						  switch (m_Player->GetElementArray()[0])
						  {
						  case FIRE:
						  {
									   m_Player->SetElement(SAND);
									   break;
						  }
						  case WATER:
						  {
										m_Player->SetElement(WOOD);
										break;
						  }
						  case EARTH:
						  {
										m_Player->SetElement(EARTH_2);
										break;
						  }
						  }
						  break;
			}
			}
			m_Player->RemoveElementCharge();
		}
		bRButtonState = false;
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
			if (temp->EmpricalCheckCollisionWith(m_Player, dt, 60))
			{
				if (temp->GetMoveState() == EDIBLE)
				{
					ELEMENT tempElement;
					tempElement = temp->GetElement();
					temp->SetActive(false);
					m_Player->AddElementCharge(tempElement);
				}
			}
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

	UpdateUI(dt);
	UpdateUI2(dt);
	m_Player->Attacks->UpdateAttack(dt, m_Player->GetElement(), m_Player->GetPosition(), m_Player->GetLeftRight());
}

void SP3::UpdateUI(double dt)
{
	// -------------------------------------- Element indicator ---------------------------------------- //

	

	if (rotateUI > 360.f)
	{
		rotateUI -= 360.f;
	}
	switch (m_Player->GetElement())
	{
	case WATER:
	{
		// Fire
		if (rotateUI < 270.f)
		{
			rotateUI += dt * 120;
		}

		break;
	}
	case FIRE:
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
	case EARTH:
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

}

void SP3::UpdateUI2(double dt)
{

	// Stalagmite
	if (treePos >  (orignalTreePos - (m_Player->GetMapOffset_x() * 0.06) - (m_Player->GetMapFineOffset_x() * 0.06)))
	{
		treePos -= (dt * 0.5);
	}
	else if (treePos < (orignalTreePos - (m_Player->GetMapOffset_x() * 0.06) - (m_Player->GetMapFineOffset_x() * 0.06)))
	{
		treePos += (dt * 0.5);
	}


	// UI Move with screen
	if (uiPos < (originalUIPos + (m_Player->GetMapOffset_x() * 1) + (m_Player->GetMapFineOffset_x() * 1)))
	{

		uiPos += (dt * 8);

		//if (rotateUI2 > -45)
		{
			//std::cout << rotateUI2 << std::endl;
			rotateUI2 -= dt * 50;
		}

	}

//	std::cout << m_Player->GetEntityHealth() << std::endl;

}

void SP3::RenderGO(GameObject *go)
{
	if (go->getRotate() == true)
	{
		glDisable(GL_CULL_FACE);
		modelStack.PushMatrix();
		modelStack.Translate(go->GetPosition().x, go->GetPosition().y, go->GetPosition().z);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(go->GetScale().x, go->GetScale().y, go->GetScale().z);
		RenderMesh(go->GetMesh(), false);
		modelStack.PopMatrix();
		glEnable(GL_CULL_FACE);
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->GetPosition().x, go->GetPosition().y, go->GetPosition().z);
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(go->GetScale().x, go->GetScale().y, go->GetScale().z);
		RenderMesh(go->GetMesh(), false);
		modelStack.PopMatrix();
	}
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

void SP3::RenderUI()
{
	// -------------------- UI --------------------- //


	modelStack.PushMatrix();
	modelStack.Translate(uiPos, 0, 0);

	// Health Bar
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 - 60,15 , 1);
	modelStack.Scale(m_Player->GetEntityHealth(), 3, 1);
	RenderMesh(meshList[GEO_HEALTH_BAR], false);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 - 64.5, 10, 1);
	modelStack.Scale(1, 3, 1);
	RenderMesh(meshList[GEO_HEALTH_BAR], false);
	modelStack.PopMatrix();


	// 


	// Element indicator
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 - 30, 15, 0);
	modelStack.Rotate(rotateUI, 0, 0, 1);

	// Water
	modelStack.PushMatrix();
	modelStack.Translate(0, 5, 1);
	//modelStack.Translate(0, 3.5, 1);
	modelStack.Scale(8, 8, 1);
	modelStack.Rotate(-rotateUI, 0, 0, 1);
	RenderMesh(meshList[GEO_WATER_ICON], false);
	modelStack.PopMatrix();

	// Earth
	modelStack.PushMatrix();
	modelStack.Rotate(120, 0, 0, 1);
	modelStack.Translate(0, 5, 1);
	//modelStack.Translate(4.5, -4.5, 1);
	modelStack.Scale(8, 8, 1);
	modelStack.Rotate(240 - rotateUI, 0, 0, 1);
	RenderMesh(meshList[GEO_EARTH_ICON], false);
	modelStack.PopMatrix();

	// Fire
	modelStack.PushMatrix();
	modelStack.Rotate(240, 0, 0, 1);
	modelStack.Translate(0, 5, 1);
	//modelStack.Translate(-4.5, -4.5, 1);
	modelStack.Scale(8, 8, 1);
	modelStack.Rotate(120 - rotateUI, 0, 0, 1);
	RenderMesh(meshList[GEO_FIRE_ICON], false);
	modelStack.PopMatrix();

	// Ring (parent)
	modelStack.Scale(6, 6, 1);
	modelStack.Translate(0, 0, 2);
	RenderMesh(meshList[GEO_RING], false);
	modelStack.PopMatrix();

	// --------------------------------- Charge --------------------------------------- // 
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 + 20, 15, 2);
	modelStack.Scale(15, 15, 1);
	modelStack.Rotate(rotateUI2, 0, 0, 1);
	//RenderMesh(meshList[GEO_CHARGE_WHEEL], false);
	modelStack.PopMatrix();

	for (int i = 0; i < 5; i++)
	{
		switch (m_Player->GetElementArray()[i])
		{
		case FIRE:
		{
			// Fire
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth * 0.5 + (i * 10), 15, 2);
			modelStack.Scale(6, 6, 1);
			RenderMesh(meshList[GEO_FIRE_ICON], false);
			modelStack.PopMatrix();
			break;
		}
		case EARTH:
		{
			// Earth
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth * 0.5 + (i * 10), 15, 2);
			modelStack.Scale(6, 6, 1);
			RenderMesh(meshList[GEO_EARTH_ICON], false);
			modelStack.PopMatrix();
			break;
		}
		case WATER:
		{
			// Water
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth * 0.5 + (i * 10), 15, 2);
			modelStack.Scale(6, 6, 1);
			RenderMesh(meshList[GEO_WATER_ICON], false);
			modelStack.PopMatrix();
			break;
		}
		default:
			break;
		}
	}

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
	
	RenderUI();

}

void SP3::SwitchLevel(LEVEL NextLevel)
{
	// Delete old maps
	delete m_Map;
	m_Map = NULL;

	delete m_GoMap;
	m_GoMap = NULL;

	// Clear m_GoList of unwanted stuff
	while (GameObjectManager::m_goList.size() > 1)
	{
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
	}

	// Load New Maps
	// ------------------------------ Map ------------------------------- //
	m_Map = new Map();
	m_Map->Init(Application::GetWindowHeight(), Application::GetWindowWidth(), 24, 32, 600, 1600);

	switch (NextLevel)
	{
	case TEST: m_Map->LoadMap("Image//Maps//Official_Test.csv"); break;
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

	if (m_Player->GetPosition().x > (0.5 * m_GoMap->GetNumOfTiles_ScreenWidth() * m_GoMap->GetTileSize()))
		m_Player->SetMapOffset_x(m_Player->GetPosition().x - (0.5 * m_GoMap->GetNumOfTiles_ScreenWidth() * m_GoMap->GetTileSize()));
	else
		m_Player->SetMapOffset_x(0);
	
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
