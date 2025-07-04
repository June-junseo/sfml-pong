#include "stdafx.h"
#include "InputMgr.h"

std::list<sf::Keyboard::Key> InputMgr::downKeys;
std::list<sf::Keyboard::Key> InputMgr::heldKeys;
std::list<sf::Keyboard::Key> InputMgr::upKeys;

std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

std::list<sf::Mouse::Button> InputMgr::downMouseButtons;
std::list<sf::Mouse::Button> InputMgr::heldMouseButtons;
std::list<sf::Mouse::Button> InputMgr::upMouseButtons;

void InputMgr::Init()
{
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positives.push_back(sf::Keyboard::D);
	infoH.positives.push_back(sf::Keyboard::Right);
	infoH.negatives.push_back(sf::Keyboard::A);
	infoH.negatives.push_back(sf::Keyboard::Left);
	axisInfoMap.insert({ Axis::Horizontal, infoH });

	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positives.push_back(sf::Keyboard::S);
	infoV.positives.push_back(sf::Keyboard::Down);
	infoV.negatives.push_back(sf::Keyboard::W);
	infoV.negatives.push_back(sf::Keyboard::Up);
	axisInfoMap.insert({ Axis::Vertical, infoV });

}

void InputMgr::Clear() 
{
	downKeys.clear();
	upKeys.clear();
	downMouseButtons.clear();
	upMouseButtons.clear();
}

void InputMgr::UpdateEvent(const sf::Event& ev) 
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (!Contains(heldKeys, ev.key.code))
		{
			downKeys.push_back(ev.key.code);
			heldKeys.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		Remove(heldKeys, ev.key.code);
		upKeys.push_back(ev.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		if (!Contains(heldMouseButtons, ev.mouseButton.button))
		{
			downMouseButtons.push_back(ev.mouseButton.button);
			heldMouseButtons.push_back(ev.mouseButton.button);
		}
		break;

	case sf::Event::MouseButtonReleased:
		Remove(heldMouseButtons, ev.mouseButton.button);
		upMouseButtons.push_back(ev.mouseButton.button);
		break;
	}
}

void InputMgr::Update(float dt) 
{
	for (auto& pair : axisInfoMap) //std::pair
	{
		AxisInfo& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw; //왜 복사하지??
		if (raw == 0.f && axisInfo.value != 0.f) 
		{
			dir = axisInfo.value > 0.f ? -1.f : 1.f; //0으로 되돌림
		}
		axisInfo.value += dir *axisInfo.sensi *  dt;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		float stopThreshold = std::abs(dir * axisInfo.sensi * dt); //절대값?
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
		//dir = row값을 받아서 계산하는 
	}
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return Contains(downKeys, key);
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return Contains(upKeys, key);
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return Contains(heldKeys, key);
}

bool InputMgr::Contains(const std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	return std::find(list.begin(), list.end(), key) != list.end();
}

bool InputMgr::Contains(const std::list<sf::Mouse::Button>& list, sf::Mouse::Button button)
{
	return std::find(list.begin(), list.end(), button) != list.end();
}

void InputMgr::Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	list.remove(key);
}

void InputMgr::Remove(std::list<sf::Mouse::Button>& list, sf::Mouse::Button button)
{
	list.remove(button);
}

float InputMgr::GetAxisRaw(Axis axis)
{
	auto findIt = axisInfoMap.find(axis); 
	if (findIt == axisInfoMap. end ())
		return 0.f;

	const AxisInfo& axisInfo = findIt->second;

	auto it = heldKeys.rbegin(); //역방향 이터레이터 순회 역방향의 시작 현재 내가 누른거
	while (it != heldKeys.rend()) //역방향을 끝 (첫번째)
	{
		sf::Keyboard::Key code = *it;
		if (Contains(axisInfo.positives, code))
		{
			return 1.f;
		}
		if (Contains(axisInfo.negatives, code))
		{
			return -1.f;
		}
		++it;
	}
	
	return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
	{
		return 0.0f;
	}
	return findIt->second.value;
}

float InputMgr::AxisRaw(Axis axis)
{
	return 0.0f;
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	return Contains(downMouseButtons, button);
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	return Contains(upMouseButtons, button);
}

bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	return Contains(heldMouseButtons, button);
}


//sf::Mouse::GetPosition(FRAMEWORK.GetWindow())


