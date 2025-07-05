#pragma once
#include "stdafx.h"
#include "GameObject.h"
class Bat : public GameObject
{

protected:
    sf::RectangleShape shape;
    sf::Vector2f direction;
    float speed = 500.f;

    float minX = 0.f;
    float maxX = 0.f;

    float minY = 0.f;
    float maxY = 0.f;

    bool isDuo = false;
public:
    Bat(const std::string& name = "");
    ~Bat() = default;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;
    //�ϸ� ���� ����?: class �� ����Ҷ� �� �����ϰ� ����ϱ����ؼ� override ���ָ� ���� 

    // GameObject��(��) ���� ��ӵ�
    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void SetDuo(bool duo);

    sf::FloatRect GetGlobalBounds() { return shape.getGlobalBounds(); }
};

