#include "stdafx.h"
#include "SceneTitle.h"
#include "TextGo.h"
#include "SpriteGo.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/Pong.png");

	AddGameObject(new SpriteGo("graphics/Pong.png"));

	Scene::Init();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}
