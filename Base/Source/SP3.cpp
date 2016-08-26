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

	meshList[GEO_HEALTH_BAR] = MeshBuilder::GenerateQuad("player", Color(0, 1, 0), 1.f);
	meshList[GEO_HEALTH_BAR_WEAKENED] = MeshBuilder::GenerateQuad("Weakened State", Color(1, 0, 0), 1.f);
	meshList[GEO_SHIELD_BAR] = MeshBuilder::GenerateQuad("player", Color(1, 0.4, 0.3), 1.f);
	meshList[GEO_FIRE_EXP_BAR] = MeshBuilder::GenerateQuad("player", Color(1, 0, 0), 1.f);
	meshList[GEO_WATER_EXP_BAR] = MeshBuilder::GenerateQuad("player", Color(0, 0.4, 1), 1.f);
	meshList[GEO_EARTH_EXP_BAR] = MeshBuilder::GenerateQuad("player", Color(0.7, 0.5, 0.3), 1.f);

	meshList[GEO_TARGET] = MeshBuilder::GenerateQuad("earth target", Color(0.7, 0.5, 0.3), 1.f);
	meshList[GEO_TARGET]->textureID = LoadTGA("Image//UI//target.tga");

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// UI stuff
	UIPos_x = 0;			
	originalUIPos_x = 0;
	UIPos_y = 0;
	originalUIPos_y = 0;

	// Health Bar starting position x
	healthbarpos_x = m_worldWidth * 0.5 - 85;

	rotateUI = 0;
	rotateUI2 = 0;
	treePos_x = 30;
	orignalTreePos_x = 30;
	treePos_y = 60;
	orignalTreePos_y = 60;

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


	if (Application::IsKeyPressed('A') && m_Player->Attacks->GetControlLock() == false)
	{
		m_Player->SetMoving_Left(true);
		m_Player->SetMove_Right(false);
	}

    if (Application::IsKeyPressed('D') && m_Player->Attacks->GetControlLock() == false)
	{
		m_Player->SetMoving_Left(false);
		m_Player->SetMove_Right(true);
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		m_Player->Attacks->Attack_Basic(m_Player->GetElement(),m_Player->GetElementLevel(m_Player->GetElement()));

		if (m_Player->GetElement() != FIRE && m_Player->GetElement() != WATER && m_Player->GetElement() != EARTH && m_Player->GetElement() != MISC)
		{
			m_Player->SetElement(currentSelectedEle);
		}
	}
    if (Application::IsKeyPressed('R'))
    {
        m_Player->Attacks->Attack_Ability(m_Player->GetElement(), m_Player->GetElementLevel(m_Player->GetElement()));

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
        m_Player->MoveLeft((float)dt);
	}
	if (m_Player->GetMoving_Right() == true)
	{
		m_Player->setRotate(false);
        m_Player->MoveRight((float)dt);
		m_Player->SetMesh(m_Player->getMeshVector()[1]);
		m_Player->SetSpriteAnimation(m_Player->getSpriteVector()[1]);
	}
    if (Application::IsKeyPressed('W') && m_Player->GetMoveState() == ON_GROUND && m_Player->Attacks->GetControlLock() == false)
	{
		m_Player->UpdateJump(dt);
	}
	if (m_Player->GetMoveState() != ON_GROUND)
	{
		m_Player->EntityJumpUpdate(dt);
	}

	// ------------------------ Vacuum --------------------------- //
	static bool fButtonState = false;
	if (Application::IsKeyPressed('F') )
	{
		ELEMENT tempElement = m_Player->GetElement();
		m_Player->SetElement(MISC);
		if (m_Player->GetLeftRight() == true)
		{
			m_Player->Attacks->Attack_Suck(m_Player->GetElement(),true);
		}
		else 
		{
			m_Player->Attacks->Attack_Suck(m_Player->GetElement(), false);
		}
		m_Player->SetElement(tempElement);
		fButtonState = true;
	}
	if (!Application::IsKeyPressed('F'))
	{
		fButtonState = false;
	}
	//std::cout << fButtonState << std::endl;
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
		m_Player->Attacks->Attack_Ability(m_Player->GetElement(), m_Player->GetElementLevel(m_Player->GetElement()));
		bEButtonState = false;
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
			if (temp->GetMoveState() == EDIBLE)
			{
				if (temp->EmpricalCheckCollisionWith(m_Player, dt, 75))
				{
					ELEMENT tempElement;
					if (temp->GetElement() == FIRE_2 || temp->GetElement() == FIRE)
					{
						tempElement = FIRE;
					}
					else if (temp->GetElement() == WATER || temp->GetElement() == WATER_2)
					{
						tempElement = WATER;
					}
					else if (temp->GetElement() == EARTH || temp->GetElement() == EARTH_2)
					{
						tempElement = EARTH;
					}
					m_Player->GainExp(tempElement, temp->GetElementPercentage(tempElement));
					temp->SetActive(false);
				}
			}
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

		if (go->GetObjectType() == COLLECTIBLE)
		{
			if (go->EmpricalCheckCollisionWith(m_Player, dt))
			{
				go->CollisionResponse(m_Player);
			}
		}

		for (std::vector<GameObject*>::size_type i2 = 0; i2 < GameObjectManager::m_goList.size(); ++i2)
		{
			GameObject *go2 = GameObjectManager::m_goList[i2];

			if (!go2->GetActive())
				continue;

			if (go->GetObjectType() == PROJECTILE && go2->GetObjectType() == ENVIRONMENT)
			{
				float offset = 25;
				if (dynamic_cast<ElementalObject*>(go)->GetElement() == EARTH || dynamic_cast<ElementalObject*>(go)->GetElement() == EARTH_2)
					offset = 35;

				if (go->EmpricalCheckCollisionWith(go2, dt, offset))
				{
					dynamic_cast<Environment*>(go2)->CollisionResponse(go, m_GoMap);
					go->CollisionResponse(go2);
				}
			}

			if (go2->GetType() == GO_BLOCK)
				continue;

            if ((go->GetObjectType() == PROJECTILE) && (go2->GetObjectType() == PLAYER || go2->GetObjectType() == ENEMY) )
            {
				Entity* temp = dynamic_cast<Entity*>(go2);
                if (go->EmpricalCheckCollisionWith(go2, dt))
                {
					temp->CollisionResponse(go);
                }				
			/*	else if (!go->EmpricalCheckCollisionWith(go2, dt) && go2->GetObjectType() == ENEMY)
				{
					Entity* temp = dynamic_cast<Entity*>(go2);
					temp->SetMoveState(NO_STATE);
				}*/
            }

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
		camera.position.x += (float)dt * 8;
	}
	else if (camera.position.x > OrignialCamPos.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x() + 5)
	{
        camera.position.x -= (float)dt * 8;
	}

	if (camera.target.x < OrignialCamTarget.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x())
	{
        camera.target.x += (float)dt * 8;
	}
	else if (camera.target.x > OrignialCamTarget.x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x() + 5)
	{
		camera.target.x -= (float)dt * 8;
	}

	if (camera.position.y < OrignialCamPos.y + m_Player->GetMapOffset_y() + m_Player->GetMapFineOffset_y())
	{
        camera.position.y += (float)dt * 8;
	}
	else if (camera.position.y > OrignialCamPos.y + m_Player->GetMapOffset_y() + m_Player->GetMapFineOffset_y() + 5)
	{
        camera.position.y -= (float)dt * 8;
	}

	if (camera.target.y < OrignialCamTarget.y + m_Player->GetMapOffset_y() + m_Player->GetMapFineOffset_y())
	{
        camera.target.y += (float)dt * 8;
	}
	else if (camera.target.y > OrignialCamTarget.y + m_Player->GetMapOffset_y() + m_Player->GetMapFineOffset_y() + 5)
	{
        camera.target.y -= (float)dt * 8;
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
	m_Player->Attacks->UpdateAttack(dt,  m_Player->GetPosition(), m_Player->GetLeftRight());

	// ------------------- Earth Attack Estimated Landing ------------------------ //
	if (m_Player->GetElement() == EARTH || m_Player->GetElement() == EARTH_2)
	{
		// Eqn: -4.9t^2 + bulletspeed * sin(theta) * t 

		float bulletspeed = 20;
		float theta = 60;

		float a = -4.9f;
		float b = bulletspeed * sin(Math::DegreeToRadian(theta));
		float c = 0;

		float TimeToLand_1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		float TimeToLand_2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

		if (TimeToLand_1 > TimeToLand_2)
			Distance_X = bulletspeed * cos(Math::DegreeToRadian(theta)) * TimeToLand_1;
		else
			Distance_X = bulletspeed * cos(Math::DegreeToRadian(theta)) * TimeToLand_2;
	}

	//std::cout << "Curr shield " << m_Player->GetCurrShield() << std::endl;
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
            rotateUI += (float)dt * 200;
		}

		break;
	}
	case FIRE:
	{
		// Earth
		if (rotateUI < 40.f)
		{
            rotateUI += (float)dt * 200;
		}
		else if (rotateUI >= 271.f || rotateUI >= 260.f)
		{
			//std::cout << "HEYYYAYYAYAYAAYAYAYAYAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAYYYYYHUE";
            rotateUI += (float)dt * 200;
		}

		break;
	}
	case EARTH:
	{
		// Water
		if (rotateUI < 140)
		{
			rotateUI += dt * 200;
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
	// X
	if (treePos_x >  (orignalTreePos_x - (m_Player->GetMapOffset_x() * 0.06) - (m_Player->GetMapFineOffset_x() * 0.06)))
	{
		treePos_x -= (dt * 0.5);
	}
	else if (treePos_x < (orignalTreePos_x - (m_Player->GetMapOffset_x() * 0.06) - (m_Player->GetMapFineOffset_x() * 0.06)))
	{
		treePos_x += (dt * 0.5);
	}


	// Move UI with screen
	// X
	if (UIPos_x  < originalUIPos_x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x())
	{
		UIPos_x += (float)dt * 8;
	}
	else if (UIPos_x  > originalUIPos_x + m_Player->GetMapOffset_x() + m_Player->GetMapFineOffset_x() + 5)
	{
		UIPos_x -= (float)dt * 8;
	}

	// Y
	if (UIPos_y < originalUIPos_y + m_Player->GetMapOffset_y() + m_Player->GetMapFineOffset_y())
	{
		UIPos_y += (float)dt * 8;
	}
	else if (UIPos_y > originalUIPos_y + m_Player->GetMapOffset_y() + m_Player->GetMapFineOffset_y() + 5)
	{
		UIPos_y -= (float)dt * 8;
	}

	//std::cout << m_Player->GetElement() << std::endl;
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

		modelStack.PushMatrix();
		modelStack.Translate(-dynamic_cast<Entity*>(go)->GetEntityHealth() * 1.25 , 0, 0);
		modelStack.Scale(5, 5, 5);
		switch (dynamic_cast<ElementalObject*>(go)->GetElement())
		{
		case FIRE: RenderMesh(meshList[GEO_FIRE_ICON], false); break;
		case WATER: RenderMesh(meshList[GEO_WATER_ICON], false); break;
		case EARTH: RenderMesh(meshList[GEO_EARTH_ICON], false); break;
		}

		modelStack.PopMatrix();

		modelStack.Scale(dynamic_cast<Entity*>(go)->GetEntityHealth() * 2, 3, 1);
		if (dynamic_cast<Entity*>(go)->GetMoveState() == WEAKENED || dynamic_cast<Entity*>(go)->GetMoveState() == EDIBLE)
		{
			RenderMesh(meshList[GEO_HEALTH_BAR_WEAKENED], false);
		}
		else
		{
			RenderMesh(meshList[GEO_HEALTH_BAR], false);
		}
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
	// ------------------------------ UI ------------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate(UIPos_x,UIPos_y, 6);

	// Background
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5 - 18, m_worldHeight * 0.5 - 8.5, -9);
	modelStack.Scale(150, 77.5, 1);
	RenderMesh(meshList[GEO_BACKGROUND], false);
	modelStack.PopMatrix();

	// Shield Bar
	for (int i = 0; i < m_Player->GetCurrShield(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x + 5) + (i * 1.2), 75, 1);
		modelStack.Scale(1, 3, 1);
		RenderMesh(meshList[GEO_SHIELD_BAR], false);
		modelStack.PopMatrix();
	}

	// Health Bar
	for (int i = 0; i < m_Player->GetEntityHealth(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x + 5) + (i * 1.2), 70, 1);
		modelStack.Scale(1, 3, 1);
		RenderMesh(meshList[GEO_HEALTH_BAR], false);
		modelStack.PopMatrix();
	}

	// Fire Element Exp Percentage Bar
	for (int i = 0; i < (m_Player->GetElementPercentage(FIRE)); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x + 5) + (i * 1.2), 65, 1);
		modelStack.Scale(1, 3, 1);
		RenderMesh(meshList[GEO_FIRE_EXP_BAR], false);
		modelStack.PopMatrix();
	}

	// Water Element Exp Percentage Bar
	for (int i = 0; i < (m_Player->GetElementPercentage(WATER)); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x + 5)+(i * 1.2), 60, 1);
		modelStack.Scale(1, 3, 1);
		RenderMesh(meshList[GEO_WATER_EXP_BAR], false);
		modelStack.PopMatrix();
	}

	// Earth Element Exp Percentage Bar
	for (int i = 0; i <( m_Player->GetElementPercentage(EARTH)); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x + 5)+(i * 1.2), 55, 1);
		modelStack.Scale(1, 3, 1);
		RenderMesh(meshList[GEO_EARTH_EXP_BAR], false);
		modelStack.PopMatrix();
	}

	switch (m_Player->GetElement())
	{
	case 3:
	{
		// Arrow
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x - 2.3), 65, 1);
		modelStack.Scale(2.5, 2.5, 1);
		modelStack.Rotate(180, 0, 0, 1);
		RenderMesh(meshList[GEO_ARROW], false);
		modelStack.PopMatrix();

		break;
	}
	case 4:
	{
		// Arrow
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x - 2.3), 55, 1);
		modelStack.Scale(2.5, 2.5, 1);
		modelStack.Rotate(180, 0, 0, 1);
		RenderMesh(meshList[GEO_ARROW], false);
		modelStack.PopMatrix();
		break; 
	}
	case 5:
	{
		// Arrow
		modelStack.PushMatrix();
		modelStack.Translate((healthbarpos_x - 2.3), 60, 1);
		modelStack.Scale(2.5, 2.5, 1);
		modelStack.Rotate(180, 0, 0, 1);
		RenderMesh(meshList[GEO_ARROW], false);
		modelStack.PopMatrix();
		break;
	}
	default:
		break;
	}


	// Shield icon
	modelStack.PushMatrix();
	modelStack.Translate((healthbarpos_x + 1), 75, 1);
	modelStack.Scale(4, 4, 1);
	RenderMesh(meshList[GEO_SHIELD_ICON], false);
	modelStack.PopMatrix();

	// Heart icon
	modelStack.PushMatrix();
	modelStack.Translate((healthbarpos_x + 1), 69.9, 1);
	modelStack.Scale(4.5, 4.5, 1);
	RenderMesh(meshList[GEO_HEART_ICON], false);
	modelStack.PopMatrix();

	// Fire icon
	modelStack.PushMatrix();
	modelStack.Translate((healthbarpos_x + 1), 65, 1);
	modelStack.Scale(5, 5, 1);
	RenderMesh(meshList[GEO_FIRE_ICON], false);
	modelStack.PopMatrix();

	// Water icon
	modelStack.PushMatrix();
	modelStack.Translate((healthbarpos_x + 1), 60, 1);
	modelStack.Scale(5, 5, 1);
	RenderMesh(meshList[GEO_WATER_ICON], false);
	modelStack.PopMatrix();

	// Earth icon
	modelStack.PushMatrix();
	modelStack.Translate((healthbarpos_x + 1), 55, 1);
	modelStack.Scale(5, 5, 1);
	RenderMesh(meshList[GEO_EARTH_ICON], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix(); // Do not delete this line
}

void SP3::RenderUIText()
{
	modelStack.PushMatrix();
	modelStack.Translate(UIPos_x, UIPos_y, 6);

	// Fire Element Level
	std::ostringstream ss;
	ss.precision(5);
	ss << m_Player->GetElementLevel(FIRE);
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 2.5, 15, 47.8);

	// Water Element Level
	std::ostringstream ss1;
	ss1.precision(5);
	ss1 << m_Player->GetElementLevel(WATER);
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 2.5, 15, 43.7);

	// Earth Element Level
	std::ostringstream ss2;
	ss2.precision(5);
	ss2 << m_Player->GetElementLevel(EARTH);
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 2.5, 15, 39.8);

	// Health Charges
	for (int i = 0; i < 5; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(10 + (i * 4.3), 14, 1);
		modelStack.Scale(4.5, 4.5, 1);
		RenderMesh(meshList[GEO_HEART2_ICON], false);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < m_Player->GetHealthCharges(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(10 + (i * 4.3), 14, 2);
		modelStack.Scale(3.5, 3.5, 1);
		RenderMesh(meshList[GEO_HEART_ICON], false);
		modelStack.PopMatrix();
	}

	modelStack.PopMatrix(); // Do not delete this line
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
	projection.SetToOrtho(0, m_worldWidth * 0.8, 0, m_worldHeight * 0.8, -10, 10);
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

	//RenderMesh(meshList[GEO_AXES], false);

	RenderUI();

	// ------------------ Background ------------------- //


	// ------------------------------------------------- //

	////stalagmite
	//modelStack.PushMatrix();
	//modelStack.Translate(treePos_x , 60 ,-1);
	//modelStack.Scale(120, 80, 1);
	//RenderMesh(meshList[GEO_TREE], false);
	//modelStack.PopMatrix();

	for (int i = 0; i < 3; i++)
	{
		// Maple Tree
		modelStack.PushMatrix();
		modelStack.Translate(treePos_x + (i * 60), 32, -2);
		modelStack.Scale(35, 35, 1);
		RenderMesh(meshList[GEO_TREE], false);
		modelStack.PopMatrix();
	}


	for (std::vector<GameObject *>::iterator it = GameObjectManager::m_goList.begin(); it != GameObjectManager::m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->GetActive() && go->GetVisible())
		{
			RenderGO(go);
		}	
	}



	if (m_Player->GetElement() == EARTH || m_Player->GetElement() == EARTH_2)
	{
		if (m_Player->GetLeftRight())
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_Player->GetPosition().x + Distance_X, m_Player->GetPosition().y, 2);
			modelStack.Scale(5, 5, 1);
			RenderMesh(meshList[GEO_TARGET], false);
			modelStack.PopMatrix();
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_Player->GetPosition().x - Distance_X, m_Player->GetPosition().y, 2);
			modelStack.Scale(5, 5, 1);
			RenderMesh(meshList[GEO_TARGET], false);
			modelStack.PopMatrix();
		}
	}


	RenderUIText();
}

void SP3::SwitchLevel(LEVEL NextLevel)
{
	// Delete old maps
	delete m_Map;
	m_Map = NULL;

	delete m_GoMap;
	m_GoMap = NULL;

	// Clear m_GoList of unwanted stuff
	int i = 0;
	while (GameObjectManager::m_goList.size() > 1)
	{
		if (i > GameObjectManager::m_goList.size() - 1)
		{
			i = 0;
		}

		GameObject* go = GameObjectManager::m_goList[i];

		if (go->GetObjectType() != PLAYER)
		{
			GameObjectManager::m_goList.erase(GameObjectManager::m_goList.begin() + i);
		}
		++i;
	}

	// Load New Maps
	// ------------------------------ Map ------------------------------- //
	m_Map = new Map();
	m_Map->Init(Application::GetWindowHeight(), Application::GetWindowWidth(), 24, 32, 600, 1600);

	switch (NextLevel)
	{
	case TEST:
	{
		m_Map->LoadMap("Image//Maps//Official_Test.csv");
		break;
	}
	case TUTORIAL_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Tutorial.csv");
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//tutorial_background.tga");
		break;
	}
	case HUB_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Hub.csv");
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//hub_background.tga");
		break;
	}
	case WATER_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Water.csv");
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//water_background.tga");
		break;
	}
	case FIRE_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Fire.csv");
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//fire_background.tga");
		break;
	}
	case EARTH_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Earth.csv"); 
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//earth_background.tga");
		break;
	}
	case WATER_BOSS_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Water_Boss.csv");
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//water_boss_background.tga");
		break;
	}
	case EARTH_BOSS_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Earth_Boss.csv");
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//earth_boss_background.tga");
		break;
	}
	case FIRE_BOSS_LEVEL:
	{
		m_Map->LoadMap("Image//Maps//Fire_Boss.csv");
		meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background//fire_boss_background.tga");
		break;
	}
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
	
	if (m_Player->GetPosition().y > (0.5 * m_GoMap->GetNumOfTiles_ScreenHeight() * m_GoMap->GetTileSize()))
		m_Player->SetMapOffset_x(m_Player->GetPosition().y - (0.5 * m_GoMap->GetNumOfTiles_ScreenHeight() * m_GoMap->GetTileSize()));
	else
		m_Player->SetMapOffset_y(0);

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

	camera.position.y = m_Player->GetMapOffset_y();
	camera.target.y = m_Player->GetMapOffset_y();
	// ------------------------------------------ // 

	treePos_x = orignalTreePos_x;
	treePos_y = orignalTreePos_y;

	UIPos_x = m_Player->GetMapOffset_x();
	UIPos_y = m_Player->GetMapOffset_y();
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

	if (m_GoMap)
	{
		delete m_GoMap;
		m_GoMap = NULL;
	}

	//if (m_ParallaxMap)
	//{
	//	delete m_Map;
	//	m_ParallaxMap = NULL;
	//}
}
