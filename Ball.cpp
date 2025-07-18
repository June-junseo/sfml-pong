#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"
#include "SceneGame.h"
#include "SceneDuoGame.h"

Ball::Ball(const std::string& name)
	: GameObject(name)
{
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(pos);
}

void Ball::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Ball::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Ball::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
}

void Ball::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

void Ball::Init()
{
	if (!isDuo)
	{
		SetOrigin(Origins::BC);
	}
	else
	{
		SetOrigin(Origins::ML);
	}
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::White);
}

void Ball::Release()
{
}

void Ball::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	if (!isDuo)
	{
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });
	}
	else
	{
		SetPosition({ bounds.left + 20.f, bounds.height * 0.5f });
	}
	float radius = shape.getRadius();
	minX = !isDuo ? bounds.left + radius : bounds.left - 100.f;
	maxX = !isDuo ? (bounds.left + bounds.width) - radius : bounds.left + bounds.width + 100.f;

	minY = bounds.top + radius * 2.f;
	maxY = !isDuo ? bounds.top + bounds.height + 200.f : bounds.top + bounds.height + radius * 2.f;

	direction = { 0.f, 0.f };
	speed = 0.f;
}

void Ball::Update(float dt)
{
	sf::Vector2f pos = GetPosition() + direction * speed * dt;

	if (!isDuo)
	{
		if (pos.x < minX)
		{
			pos.x = minX;
			direction.x *= -1.f;
		}
		else if (pos.x > maxX)
		{
			pos.x = maxX;
			direction.x *= -1.f;
		}

		if (pos.y < minY)
		{
			pos.y = minY;
			direction.y *= -1.f;
		}
		else if (pos.y > maxY)
		{
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
			{
				SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();
				scene->SetGameOver();
			}
		}
		//bat충돌

		if (bat != nullptr)
		{

			const sf::FloatRect& batBounds = bat->GetGlobalBounds();
			//충돌검사 함수
			if (shape.getGlobalBounds().intersects(batBounds))
			{
				pos.y = batBounds.top;
				direction.y *= -1.f;
			}
		}
	}
	else
	{
		if (pos.x < minX)
		{
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::DuoGame)
			{
				SceneDuoGame* scene = (SceneDuoGame*)SCENE_MGR.GetCurrentScene();
				scene->SetGameOver();
			}
		}
		else if (pos.x > maxX)
		{
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::DuoGame)
			{
				SceneDuoGame* scene = (SceneDuoGame*)SCENE_MGR.GetCurrentScene();
				scene->SetGameOver();
			}
		}

		if (pos.y < minY)
		{
			pos.y = minY;
			direction.y *= -1.f;
		}
		else if (pos.y > maxY)
		{
			pos.y = maxY;
			direction.y *= -1.f;
		}
		//bat충돌

		if (bat1 != nullptr)
		{

			const sf::FloatRect& batBounds = bat1->GetGlobalBounds();
			//충돌검사 함수
			if (shape.getGlobalBounds().intersects(batBounds))
			{
				pos.x = batBounds.left + batBounds.width +  shape.getRadius();
				direction.x *= -1.f;
			}
		}
		if (bat2 != nullptr)
		{

			const sf::FloatRect& batBounds = bat2->GetGlobalBounds();
			//충돌검사 함수
			if (shape.getGlobalBounds().intersects(batBounds))
			{
				pos.x = batBounds.left - 20.f;
				direction.x *= -1.f;
			}
		}
	}
	

	SetPosition(pos);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ball::Fire(const sf::Vector2f& d, float s)
{
	direction = d;
	speed = s;
}

void Ball::SetDuo(bool duo)
{
	isDuo = duo;
}
