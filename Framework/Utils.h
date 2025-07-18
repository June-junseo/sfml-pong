#pragma once
#include <random>

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static void Init();

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);

	//math

	static float Clamp(float value, float min, float max); //InputMgr used 
	static float Clamp02(float value);
	
	static float Magnitude(const sf::Vector2f& vec);
	static float SqrMagnitude(const sf::Vector2f& vec); //백터 길이 계산

	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
	static void Normalize(sf::Vector2f& vec);

	//두 포지션 사이의 길이
	static float Distance(const sf::Vector2f p1, const sf::Vector2f p2);
	 //선형보간?
	static float Lerp(float min, float max, float t, bool clamp = true); //t 0=min 1 = max 0.5 = 중간
	static sf::Vector2f Lerp(const sf::Vector2f& min,const sf::Vector2f& max, float t, bool clamp = true); //t 0=min 1 = max 0.5 = 중간
	//static sf::Color Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp = true); //t 0=min 1 = max 0.5 = 중간

};


