#pragma once
#include "Pawn.h"
#include "Game.h"

class APlayerController : public APawnController
{
public:
	APlayerController() : APawnController() {};
	virtual void Update(const float& DeltaTime) override;
private:
	void Move();
};

class APlayer final : public APawn
{
public:
	APlayer();
	virtual void Draw() override;

protected:
	sf::Texture Texture;
};


