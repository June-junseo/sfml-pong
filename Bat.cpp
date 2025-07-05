#include "stdafx.h"
#include "Bat.h"

Bat::Bat(const std::string& name)
	: GameObject(name)
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(pos);
}

void Bat::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);

}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

void Bat::Init()
{
	if (!isDuo)
	{
		shape.setSize({ 100.f, 5.f });
		shape.setFillColor(sf::Color::White);
		SetOrigin(Origins::TC);
	}
	else
	{
		shape.setSize({ 5.f, 100.f });
		shape.setFillColor(sf::Color::White);
		SetOrigin(Origins::MR);
	}
}

void Bat::Release()
{
}

void Bat::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	if (!isDuo)
	{
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });

		sf::Vector2f size = shape.getSize();
		minX = bounds.left + size.x * 0.5f;
		maxX = (bounds.left + bounds.width) - size.x * 0.5f;
	}
	else
	{
		if (GetName() == "Bat1")
		{
			SetPosition({ bounds.left + 20.f, bounds.height * 0.5f });
		}
		if (GetName() == "Bat2")
		{
			SetPosition({ bounds.left + bounds.width - 20.f, bounds.height * 0.5f });
		}
		sf::Vector2f size = shape.getSize();
		minY = bounds.top + size.y* 0.5f;
		maxY = (bounds.top + bounds.height) - size.y* 0.5f;
	}
}

void Bat::Update(float dt)
{
	if (isDuo == false)
	{
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.x = Utils::Clamp(pos.x, minX, maxX);
		SetPosition(pos);
	}
	else
	{
		direction.y = InputMgr::GetAxis(Axis::Vertical); //존재하는 것에 조건문을 걸기위해서 
		if((GetName() == "Bat1" && InputMgr::GetKey(sf::Keyboard::W) && direction.y < 0.f) || 
			(GetName() == "Bat1" && InputMgr::GetKey(sf::Keyboard::S) && direction.y > 0.f) ||
			(GetName() == "Bat2" && InputMgr::GetKey(sf::Keyboard::Up) && direction.y < 0.f) ||
			(GetName() == "Bat2" && InputMgr::GetKey(sf::Keyboard::Down) && direction.y > 0.f)
			)
		{
			sf::Vector2f pos = GetPosition() + direction * speed * dt;
			pos.y = Utils::Clamp(pos.y, minY, maxY);
			SetPosition(pos);
		}
	}
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Bat::SetDuo(bool duo)
{
	isDuo = duo; //싱글게임은 isDuo를 호출 안함 DuoGame은 isDuo게임을 호출
}
