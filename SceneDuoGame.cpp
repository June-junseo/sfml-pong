#include "stdafx.h"
#include "SceneDuoGame.h"
#include "Ball.h"
#include "Bat.h"

SceneDuoGame::SceneDuoGame()
	:Scene(SceneIds::DuoGame)
{
}

void SceneDuoGame::Init()
{
	texIds.push_back("graphics/Option.png");
	texIds.push_back("graphics/Pong.png");
	ball = (Ball*)AddGameObject(new Ball("Ball"));
	bat1 = (Bat*)AddGameObject(new Bat("Bat1"));
	bat2 = (Bat*)AddGameObject(new Bat("Bat2"));
	ball->SetBat1(bat1);
	ball->SetBat2(bat2);
	ball->SetDuo(true);
	bat1->SetDuo(true);
	bat2->SetDuo(true);
	Scene::Init();
}

void SceneDuoGame::Enter()
{
	ballActive = false;

	Scene::Enter();
}

void SceneDuoGame::Update(float dt)
{
	Scene::Update(dt);

	if (!ballActive)
	{
		ball->SetPosition(bat1->GetPosition());
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ballActive = true;
			sf::Vector2f dir(1.f, -1.f);
			Utils::Normalize(dir);
			ball->Fire(dir, 500.f);
		}
	}
}

void SceneDuoGame::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::DuoGame);
}