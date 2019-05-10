#pragma once
#include "EngineCore.h"

class AActor
{
public:
	AActor() {};
	virtual ~AActor() = default;

	virtual void Draw() = 0;
	virtual void Update(const float &DeltaTime) = 0;

	inline virtual void SetLocation(const sf::Vector2f &_Location) { this->Sprite.setPosition(_Location); };
	inline virtual void SetLocation(const float _X, const float _Y) { this->Sprite.setPosition(_X, _Y); };
	inline virtual sf::Vector2f GetLocation() const { return this->Sprite.getPosition(); };

protected:
	sf::Sprite Sprite;
};