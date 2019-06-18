#pragma once
#include "Actor.h"
#include "TextureManager.h"
#include "Game.h"

class ASpeedUp : public AActor
{
public:
	ASpeedUp();
	virtual ~ASpeedUp();
	virtual void Update(const float& DeltaTime) override;
	virtual void Draw() override;
	inline sf::FloatRect GetCollider() const { return this->Collider; };
private:
	sf::FloatRect Collider;
};