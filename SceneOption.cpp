#include "stdafx.h"
#include "SceneOption.h"
#include "TextGo.h"
#include "SpriteGo.h"

SceneOption::SceneOption()
	: Scene(SceneIds::title)
{
}

void SceneOption::Init()
{
	texIds.push_back("graphics/Option.png");

	AddGameObject(new SpriteGo("graphics/Option.png"));

	Scene::Init();
}

void SceneOption::Exit()
{
	Scene::Exit();
}

void SceneOption::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.ChangeScene(SceneIds::DuoGame);
	}
}

