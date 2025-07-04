#pragma once

enum class Axis
{
	Horizontal,
	Vertical,
};


struct AxisInfo
{
	Axis axis;
	std::list<sf::Keyboard::Key>positives; //1.f
	std::list<sf::Keyboard::Key>negatives; //-1.f

	float sensi = 10.f; //�ӵ� �������� õõ�� �ӵ� ����
	float value = 0.f; //�� ���� ��ȯ
};

class InputMgr
{
private:
	static std::list<sf::Keyboard::Key> downKeys;
	static std::list<sf::Keyboard::Key> heldKeys;
	static std::list<sf::Keyboard::Key> upKeys;

	static std::list<sf::Mouse::Button> downMouseButtons;
	static std::list<sf::Mouse::Button> heldMouseButtons;
	static std::list<sf::Mouse::Button> upMouseButtons;

	static std::unordered_map<Axis, AxisInfo> axisInfoMap;

public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

	static bool Contains(const std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key);
	static bool Contains(const std::list<sf::Mouse::Button>& list, sf::Mouse::Button button);

	static void Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key);
	static void Remove(std::list<sf::Mouse::Button>& list, sf::Mouse::Button button);


	static float GetAxisRaw(Axis axis);
	static float GetAxis(Axis axis);
	static float AxisRaw(Axis axis); //.������ �ð���ŭ �־��ִ� (v)

	static bool GetMouseButtonDown(sf::Mouse::Button key);
	static bool GetMouseButtonUp(sf::Mouse::Button key);
	static bool GetMouseButton(sf::Mouse::Button key);

};

