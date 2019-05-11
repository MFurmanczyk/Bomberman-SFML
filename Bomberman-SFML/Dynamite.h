#pragma once
#include "Actor.h"
#include "Game.h"

class ADynamite : public AActor
{
public:
	ADynamite();
	~ADynamite() = default;

	virtual void Update(const float & DeltaTime) override;
	virtual void Draw() override;

private:
	sf::Texture Texture;
	void Explode(const float & DeltaTime);
	float ExplodeTime = 0;
};