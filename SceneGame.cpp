#include "stdafx.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"
#include "SpriteGo.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/Pong.png");

	//AddGameObject(new SpriteGo("graphics/Pong.png"));


	ball = (Ball*)AddGameObject(new Ball("Ball"));
	bat = (Bat*)AddGameObject(new Bat("Bat"));
	ball->SetBat(bat);
	Scene::Init();
}

void SceneGame::Enter()
{
	ballActive = false;

	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (!ballActive)
	{
		ball->SetPosition(bat->GetPosition());
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
 			ballActive = true;
			sf::Vector2f dir(1.f, -1.f);
			Utils::Normalize(dir);
			ball->Fire(dir, 500.f);
		}
	}
}

void SceneGame::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::Game);
}
